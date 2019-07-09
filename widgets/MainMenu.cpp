#include "MainMenu.h"
#include <QVBoxLayout>

MainMenu::MainMenu(QWidget* parent) : QMenuBar(parent),
File(new QMenu("File", this)), Help(new QMenu("Help", this)),
openLog(new QAction(QIcon(QPixmap(":/icons/box-open.png")), "Open log file", File)),
saveLog(new QAction(QIcon(QPixmap(":/icons/save.png")), "Save log file", File)),
closeLog(new QAction(QIcon(QPixmap(":/icons/window-close.png")), "Close log", File)),
closeProgram(new QAction(QIcon(QPixmap(":/icons/window-close.png")), "Close program", File)),
about(new QAction(QIcon(QPixmap(":/icons/info-circle.png")), "About QCafe", Help)) {
    QVBoxLayout* layout = new QVBoxLayout(this);

    // File menu tab
    File->addAction(openLog);
    File->addAction(saveLog);
    File->addAction(closeLog);
    File->addAction(closeProgram);

    // Help menu tab
    Help->addAction(about);

    addMenu(File);
    addMenu(Help);

    setLayout(layout);
}
