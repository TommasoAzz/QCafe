#ifndef QCAFE_VIEW_H
#define QCAFE_VIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include "widgets/MainMenu.h"
class QCafe_Controller;

class QCafe_View : public QWidget {
    Q_OBJECT
public:
    QCafe_View(QCafe_Controller*, QWidget* = nullptr);
    virtual ~QCafe_View() = default;
protected:
    QCafe_Controller* controller; // controller che gestisce l'interazione vista-modello
    QVBoxLayout* mainLayout; // layout principale della vista
    MainMenu* mainMenu; // menu principale

    void connectMainMenu(); // connette i signal e slot del mainMenu il menu principale (File, Help) alla vista
    static QList<QString> convertSTLStringListToQtStringList(const std::list<std::string>&);
private slots:
    void open_log();
    void save_log();
    void close_log();
    void about_popup();
};

#endif // QCAFE_VIEW_H
