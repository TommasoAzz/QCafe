#include "EditOrder.h"
#include <QGridLayout>
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include "EditOrderTabPanel.h"

EditOrder::EditOrder(QWidget* parent): QWidget(parent), takeAway(new QCheckBox("Take away", this)), customerName(new QLineEdit(this)), editOrderTabPanel(new EditOrderTabPanel(this)) {
    QGridLayout* layout = new QGridLayout(this);
    QLabel* lbl_editOrder = new QLabel("Customer's requests", this);
    QLabel* lbl_customerName = new QLabel("Customer name", this);

    customerName->setPlaceholderText("Type the customer's name here...");

    layout->addWidget(lbl_editOrder, 0, 0, 1, 2);
    layout->addWidget(lbl_customerName, 1, 0);
    layout->addWidget(customerName, 1, 1);
    layout->addWidget(takeAway, 2, 0, 1, 2);
    layout->addWidget(editOrderTabPanel, 3, 0, 1, 2);

    setLayout(layout);
}
