#include "QCafe_Cashier.h"
#include "QCafe_Controller.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QList>
#include <QPixmap>
#include <QMessageBox>
#include <QListWidgetItem>
#include "widgets/EditOrder.h"
#include "widgets/EditOrderTabPanel.h"
#include "widgets/EditOrderSingleTab.h"
using std::string;
using std::list;
using std::map;

const QString QCafe_Cashier::editOrderCoffeeLabel = "Coffee";
const QString QCafe_Cashier::editOrderTeaLabel = "Tea";
const QString QCafe_Cashier::editOrderSweetLabel = "Sweet";
const QString QCafe_Cashier::editOrderSandwichLabel = "Sandwich";

void QCafe_Cashier::addQuickOrderPanel(QHBoxLayout* layout) {
    QVBoxLayout* vLayout = new QVBoxLayout(this);
    QLabel* lbl_productList = new QLabel("Select a product", this);

    connect(quickOrderPanel, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)), this, SLOT(select_item(QListWidgetItem*, QListWidgetItem*)));

    vLayout->addWidget(lbl_productList);
    vLayout->addWidget(quickOrderPanel);

    layout->addLayout(vLayout);
}

void QCafe_Cashier::addEditOrderPanel(QHBoxLayout* layout) {
    // aggiunta tab ad editOrder e disabilitazione delle tab (attivabili tramite segnale dalla ProductList)
    editOrder->editOrderTabPanel->addSingleTab(new EditOrderCoffeeTab(editOrder->editOrderTabPanel), editOrderCoffeeLabel);
    editOrder->editOrderTabPanel->addSingleTab(new EditOrderTeaTab(editOrder->editOrderTabPanel), editOrderTeaLabel);
    editOrder->editOrderTabPanel->addSingleTab(new EditOrderSweetTab(editOrder->editOrderTabPanel), editOrderSweetLabel);
    editOrder->editOrderTabPanel->addSingleTab(new EditOrderSandwichTab(editOrder->editOrderTabPanel), editOrderSandwichLabel);

    for(int i = 0; i < editOrder->editOrderTabPanel->count(); ++i) editOrder->editOrderTabPanel->setTabEnabled(i, false);

    layout->addWidget(editOrder);
}

void QCafe_Cashier::addOrderImagePanel(QVBoxLayout* layout) {
    QLabel* lbl_orderRecap = new QLabel("Order preview image", this);

    layout->addWidget(lbl_orderRecap);
    layout->addWidget(orderPreviewImage);
}

void QCafe_Cashier::addDiscountPanel(QVBoxLayout* layout) {
    QHBoxLayout* discountPanel = new QHBoxLayout(this);
    QLabel* lbl_discountValue = new QLabel("Apply discount (in %) ", this);

    discount->setPlaceholderText("Type here the discount percentage...");

    discountPanel->addWidget(lbl_discountValue);
    discountPanel->addWidget(discount);

    layout->addLayout(discountPanel);
}

void QCafe_Cashier::addConfirmationPanel(QVBoxLayout* layout) {
    QHBoxLayout* buttonsPanel = new QHBoxLayout(this);

    connect(confirm, SIGNAL(clicked()), this, SLOT(push_order()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(remove_last_order()));

    buttonsPanel->addWidget(confirm);
    buttonsPanel->addWidget(cancel);

    layout->addLayout(buttonsPanel);
}

void QCafe_Cashier::switch_tab(const QString& previous_tab, const QString& current_tab) {
    if(previous_tab != current_tab) {
        EditOrderTabPanel* tabPanel = editOrder->editOrderTabPanel;
        for(int i = 0, l = tabPanel->count(); i < l; ++i) {
            if(tabPanel->tabText(i) == previous_tab) tabPanel->setTabEnabled(i, false);
            else if(tabPanel->tabText(i) == current_tab) {
                tabPanel->setTabEnabled(i, true);
                tabPanel->setCurrentIndex(i); // setCurrentIndex è uno slot e riceve l'ordine di selezionare il tab
            }
        }
    }
}

void QCafe_Cashier::setComboBoxValues(ComboBoxName cw, const list<string>& values) {
    QComboBox* cbox1 = nullptr, *cbox2 = nullptr;

    switch(cw) {
        case CB_SWEETENER:
            cbox1 = static_cast<EditOrderBeverageTab*>(editOrder->editOrderTabPanel->tab(editOrderCoffeeLabel))->sweetener;
            cbox2 = static_cast<EditOrderBeverageTab*>(editOrder->editOrderTabPanel->tab(editOrderTeaLabel))->sweetener;
            break;
        case CB_CUP_SIZE:
            cbox1 = static_cast<EditOrderBeverageTab*>(editOrder->editOrderTabPanel->tab(editOrderCoffeeLabel))->cupSize;
            cbox2 = static_cast<EditOrderBeverageTab*>(editOrder->editOrderTabPanel->tab(editOrderTeaLabel))->cupSize;
            break;
        case CB_VARIETY:
            cbox1 = static_cast<EditOrderCoffeeTab*>(editOrder->editOrderTabPanel->tab(editOrderCoffeeLabel))->variety;
            break;
        case CB_FLAVOUR:
            cbox1 = static_cast<EditOrderSweetTab*>(editOrder->editOrderTabPanel->tab(editOrderSweetLabel))->flavour;
            break;
        case CB_BREAD_TYPE:
            cbox1 = static_cast<EditOrderSandwichTab*>(editOrder->editOrderTabPanel->tab(editOrderSandwichLabel))->breadType;
            break;
        case CB_MAIN_INGREDIENT:
            cbox1 = static_cast<EditOrderSandwichTab*>(editOrder->editOrderTabPanel->tab(editOrderSandwichLabel))->mainIngredient;
            break;
        case CB_SAUCE:
            cbox1 = static_cast<EditOrderSandwichTab*>(editOrder->editOrderTabPanel->tab(editOrderSandwichLabel))->sauce;
            break;
    }

    QList<QString> cbox_items = convertSTLStringListToQtStringList(values);
    if(cbox1) {
        cbox1->addItems(cbox_items);
    }
    if(cbox2) {
        cbox2->addItems(cbox_items);
    }
}

QString QCafe_Cashier::imageFileName(const QString& item_name) const {
    QString fileName, prodType = QString::fromStdString(controller->productType(item_name.toStdString()));

    if(prodType == "Coffee" || prodType == "Coffee_Milk" || prodType == "Sweet")
        fileName = item_name.simplified().replace(" ", ""); // simplified effettua il trim e gli spazi multipli all'interno (esempio \t, \n, ...) vengono ridotti a singoli spazi ' '
    else
        fileName = prodType;

    return fileName;
}

void QCafe_Cashier::setProductList(const list<string>& item_list) {
    quickOrderPanel->addItems(convertSTLStringListToQtStringList(item_list));
}

QCafe_Cashier::QCafe_Cashier(QCafe_Controller* c, QWidget* parent):
QCafe_View(c, parent), quickOrderPanel(new QListWidget(this)),
editOrder(new EditOrder(this)), orderPreviewImage(new QLabel(this)),
discount(new QLineEdit(this)), confirm(new QPushButton("Confirm order", this)),
cancel(new QPushButton("Cancel last order", this)) {
    QHBoxLayout* contentLayout = new QHBoxLayout(this);
    QVBoxLayout* confirmLayout = new QVBoxLayout(this);

    // pannello "Quick Order"
    addQuickOrderPanel(contentLayout);
    // pannello "Edit Order"
    addEditOrderPanel(contentLayout);
    // pannelli "Order Recap", "Add Discount", "Confirmation"
    addOrderImagePanel(confirmLayout);
    addDiscountPanel(confirmLayout);
    addConfirmationPanel(confirmLayout);

    // popolazione del pannello QuickOrder e delle combobox nel pannello EditOrder
    setProductList(controller->productList());
    auto eos = controller->editOrderSettings();
    for(auto it = eos.begin(); it != eos.end(); ++it)
        setComboBoxValues(it->first, it->second); // it->first e' di tipo ComboBoxName, it->second di tipo list<string>

    contentLayout->setContentsMargins(5, 5, 5, 5);
    contentLayout->addLayout(confirmLayout);
    mainLayout->addLayout(contentLayout);

    setWindowTitle("QCafe - Cashier");
}

QCafe_Cashier::~QCafe_Cashier() {}

void QCafe_Cashier::select_item(QListWidgetItem* current, QListWidgetItem* previous) {
    QString current_item = current ? current->text() : "", previous_item = previous ? previous->text() : "";
    QString current_tab, previous_tab;

    /* TAB:
     * "Coffee": Coffee e Coffee_Milk
     * "Tea": Tea
     * "Sweet": Sweet
     * "Sandwich": Sandwich
     * */

    // previous_tab
    if(controller->productType(previous_item.toStdString()) == "Coffee" || controller->productType(previous_item.toStdString()) == "Coffee_Milk") {
        previous_tab = editOrderCoffeeLabel;
    } else { // previous_tab = productType()
        previous_tab = QString::fromStdString(controller->productType(previous_item.toStdString()));
    }
    // current_tab
    if(controller->productType(current_item.toStdString()) == "Coffee" || controller->productType(current_item.toStdString()) == "Coffee_Milk") {
        current_tab = editOrderCoffeeLabel;
    } else { // previous_tab = productType()
        current_tab = QString::fromStdString(controller->productType(current_item.toStdString()));
    }

    switch_tab(previous_tab, current_tab);

    orderPreviewImage->setPixmap(QPixmap(":/images/" + imageFileName(current_item) + ".jpg"));
}

void QCafe_Cashier::push_order() {
    // Attributi di Order
    string productName = quickOrderPanel->currentItem()->text().toStdString();
    string customerName = editOrder->customerName->text().toStdString();
    bool ta = editOrder->takeAway->isChecked();
    double discountVal = discount->text().toDouble();
    // Attributi di Order

    // proseguo nella raccolta dei dati solo se e' stato inserito il nome del cliente, altrimenti non ha senso
    if(customerName == "") {
        QMessageBox::warning(
            this,
            "Warning",
            "<p>You can add a new order only if you type the customer's name in its correct input field.</p>"
        );
        return;
    };

    string prodType = controller->productType(productName);

    if(prodType == "Coffee" || prodType == "Coffee_Milk" || prodType == "Tea") {
        EditOrderBeverageTab* beverageTab = static_cast<EditOrderBeverageTab*>(editOrder->editOrderTabPanel->currentWidget());
        // Attributi di Beverage
        string sweetener = beverageTab->sweetener->currentText().toStdString();
        string cupSize = beverageTab->cupSize->currentText().toStdString();
        // Attributi di Beverage

        if(prodType == "Tea") {
            // Attributi di Tea
            /* non ce ne sono */
            // Attributi di Tea

            // RACCOLTA DATI Tea TERMINATA - INSERIMENTO NEL MODELLO
            controller->pushOrder(productName, cupSize, sweetener, customerName, ta, discountVal);
        } else {
            EditOrderCoffeeTab* coffeeTab = static_cast<EditOrderCoffeeTab*>(beverageTab);
            // Attributi di Coffee
            string variety = coffeeTab->variety->currentText().toStdString();
            // Attributi di Coffee
            // Attributi di Coffee_Milk
            bool whippedCream = coffeeTab->whippedCream->isChecked();
            // Attributi di Coffee_Milk

            // RACCOLTA DATI Coffee/Coffee_Milk TERMINATA - INSERIMENTO NEL MODELLO
            if(prodType == "Coffee_Milk" || (prodType == "Coffee" && whippedCream)) {  // Coffee_Milk
                controller->pushOrder(productName, cupSize, variety, sweetener, whippedCream, customerName, ta, discountVal);
            } else { // Coffee
                controller->pushOrder(productName, cupSize, variety, sweetener, customerName, ta, discountVal);
            }
        }
    } else { // isSandwich || isSweet
        EditOrderFoodTab* foodTab = static_cast<EditOrderFoodTab*>(editOrder->editOrderTabPanel->currentWidget());
        // Attributi di Food
        bool heatProduct = foodTab->heatProduct->isChecked();
        // Attributi di Food

        if(prodType == "Sweet") {
            EditOrderSweetTab* sweet_tab = static_cast<EditOrderSweetTab*>(foodTab);
            // Attributi di Sweet
            string flavour = sweet_tab->flavour->currentText().toStdString();
            bool whippedCream = sweet_tab->whippedCream->isChecked();
            // Attributi di Sweet

            // RACCOLTA DATI Sweet TERMINATA - INSERIMENTO NEL MODELLO
            controller->pushOrder(productName, whippedCream, flavour, heatProduct, customerName, ta, discountVal);
        } else { // isSandwich
            EditOrderSandwichTab* sandwichTab = static_cast<EditOrderSandwichTab*>(foodTab);
            // Attributi di Sandwich
            string bread = sandwichTab->breadType->currentText().toStdString();
            string mainIngredient = sandwichTab->mainIngredient->currentText().toStdString();
            string sauce = sandwichTab->sauce->currentText().toStdString();
            bool cheese = sandwichTab->cheese->isChecked();
            bool lettuce = sandwichTab->lettuce->isChecked();

            // RACCOLTA DATI Sandwich TERMINATA - INSERIMENTO NEL MODELLO
            controller->pushOrder(bread, mainIngredient, sauce, cheese, lettuce, heatProduct, customerName, ta, discountVal);
        }
    }

    // reset dei dati contenuti nelle QLineEdit
    editOrder->customerName->setText("");
    discount->setText("");
}

void QCafe_Cashier::remove_last_order() {
    controller->removeOrders(controller->numberOfOrders()-1);
}
