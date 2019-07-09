#-------------------------------------------------
#
# Project created by QtCreator 2019-02-08T20:44:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QCafe
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
    main.cpp \
    QCafe_Controller.cpp \
    QCafe_Model.cpp \
    QCafe_View.cpp \
    QCafe_Barista.cpp \
    QCafe_Cashier.cpp \
    XMLFileIO.cpp \
    FileException.cpp \
    widgets/EditQueuedOrderDialog.cpp \
    widgets/MainMenu.cpp \
    widgets/EditOrder.cpp \
    widgets/EditOrderSingleTab.cpp \
    widgets/EditOrderTabPanel.cpp \
    widgets/OrderList.cpp \
    widgets/OrdersTabPanel.cpp \
    data_types/Order.cpp \
    data_types/Beverage.cpp \
    data_types/Coffee.cpp \
    data_types/Coffee_Milk.cpp \
    data_types/Tea.cpp \
    data_types/Food.cpp \
    data_types/Sandwich.cpp \
    data_types/Sweet.cpp


HEADERS += \
    FileException.h \
    container/DeepPtr.h \
    QCafe_Controller.h \
    QCafe_Model.h \
    QCafe_View.h \
    QCafe_Barista.h \
    QCafe_Cashier.h \
    XMLFileIO.h \
    container/Qontainer.h \
    widgets/EditQueuedOrderDialog.h \
    widgets/MainMenu.h \
    widgets/EditOrder.h \
    widgets/EditOrderSingleTab.h \
    widgets/EditOrderTabPanel.h \
    widgets/OrderList.h \
    widgets/OrdersTabPanel.h \
    data_types/QCafe.h \
    data_types/Order.h \
    data_types/Beverage.h \
    data_types/Coffee.h \
    data_types/Coffee_Milk.h \
    data_types/Tea.h \
    data_types/Food.h \
    data_types/Sandwich.h \
    data_types/Sweet.h

SUBDIRS += \
    QCafe.pro

DISTFILES += \
    QCafe.pro.user

RESOURCES += \
    resources.qrc
