#ifndef EDITORDER_H
#define EDITORDER_H

#include <QWidget>
#include <QCheckBox>
#include <QLineEdit>
#include "EditOrderTabPanel.h"

class EditOrder: public QWidget {
    Q_OBJECT
public:
    explicit EditOrder(QWidget* =nullptr);
    QCheckBox* takeAway;
    QLineEdit* customerName;
    EditOrderTabPanel* editOrderTabPanel;
};

#endif // EDITORDER_H
