#include "QCafe_View.h"
#include "QCafe_Controller.h"
#include <QFileDialog>
#include <QMessageBox>
#include "FileException.h"

QCafe_View::QCafe_View(QCafe_Controller* c, QWidget* parent) : QWidget(parent),
controller(c), mainLayout(new QVBoxLayout(this)), mainMenu(new MainMenu(this)) {
    // "Main menu" menu
    connectMainMenu();
    mainLayout->addWidget(mainMenu);

    mainLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(mainLayout);
}

void QCafe_View::connectMainMenu() {
    // signals and slots - menu file
    connect(mainMenu->openLog, SIGNAL(triggered()), this, SLOT(open_log()));
    connect(mainMenu->saveLog, SIGNAL(triggered()), this, SLOT(save_log()));
    connect(mainMenu->closeLog, SIGNAL(triggered()), this, SLOT(close_log()));
    connect(mainMenu->closeProgram, SIGNAL(triggered()), this, SLOT(close()));

    // signals and slots - menu help
    connect(mainMenu->about, SIGNAL(triggered()), this, SLOT(about_popup()));
}

QList<QString> QCafe_View::convertSTLStringListToQtStringList(const std::list<std::string>& stl_string_list) {
    QList<QString> qt_string_list;

    std::for_each(stl_string_list.begin(), stl_string_list.end(), [&qt_string_list](std::string p) {
        qt_string_list.push_back(QString::fromStdString(p));
    });

    return qt_string_list;
}

void QCafe_View::open_log() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open save file", "", "QCafe save file (*" + QString::fromStdString(controller->logFileExtension()) + ")");
    if(fileName == "") return;
    if(!fileName.endsWith(".xml")) fileName += ".xml"; // controllare Windows

    try {
        controller->openLog(fileName.toStdString());
    } catch(FileException e) {
        QMessageBox::critical(
            this,
            "I/O Error: " + QString((e.io_mode() ? "INPUT" : "OUTPUT")),
            QString(e.what())
        );
    }
}

void QCafe_View::save_log() {
    QString fileName = QFileDialog::getSaveFileName(this, "Choose save file", "", "QCafe save files (*" + QString::fromStdString(controller->logFileExtension()) + ")");
    if(fileName == "") return;
    if(!fileName.endsWith(".xml")) fileName += ".xml"; // controllare Windows

    try {
        controller->saveLog(fileName.toStdString());
    } catch(FileException e) {
        QMessageBox::critical(
            this,
            "I/O Error: " + QString((e.io_mode() ? "INPUT" : "OUTPUT")),
            QString(e.what())
        );
    }
}

void QCafe_View::close_log() {
    controller->clearAllOrders();
}

void QCafe_View::about_popup() {
    QMessageBox::information(
        this,
        "About QCafe",
        "<p><strong>QCafe</strong> is a small project created by Tommaso Azzalin.</p><p>Developed in <strong>C++</strong> and <strong>Qt</strong> for the Object Oriented Programming course of the Degree in Computer Science of the University of Padova.</p>"
    );
}
