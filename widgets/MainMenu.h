#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMenuBar>

class MainMenu : public QMenuBar {
    Q_OBJECT
public:
    explicit MainMenu(QWidget* =nullptr);
    QMenu* File, *Help;
    QAction* openLog, *saveLog, *closeLog, *closeProgram; // File
    QAction* about; // Help
};

#endif // MAINMENU_H
