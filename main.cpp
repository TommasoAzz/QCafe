#include <QApplication>
#include "QCafe_Cashier.h"
#include "QCafe_Controller.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QCafe_Model model;
    QCafe_Controller* controller = new QCafe_Controller(&model);
    controller->showView();

    a.setWindowIcon(QIcon(":/icons/coffee.png"));

    return a.exec();
}
