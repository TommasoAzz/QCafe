#include "QCafe_Barista.h"
#include "QCafe_Controller.h"
#include "widgets/OrderList.h"
#include "widgets/EditQueuedOrderDialog.h"
#include <QLabel>

using std::list;
using std::string;

const QString QCafe_Barista::ordersQueueLabel = "Orders queue";
const QString QCafe_Barista::searchLabel = "Search order";
const QString QCafe_Barista::searchBoxDefaultValue = "-";

QCafe_Barista::QCafe_Barista(QCafe_Controller* c, QWidget* parent):
QCafe_View(c, parent), ordersTab(new OrdersTabPanel(this)), ordersLog(new QTextEdit(this)),
popOrder(new QPushButton("Order completed", this)), cancelOrders(new QPushButton("Cancel selected orders", this)),
cancelAllOrders(new QPushButton("Cancel all orders", this)), productNames(new QComboBox(this)),
productCategories(new QComboBox(this)), searchButton(new QPushButton("Search", this)) {
    QVBoxLayout* contentLayout = new QVBoxLayout(this);
    QGridLayout* buttonLayout = new QGridLayout(this);
    QGridLayout* searchLayout = new QGridLayout(this);

    // OrdersTabPanel
    addOrderTabs();
    contentLayout->addWidget(ordersTab);
    // pulsanti di rimozione degli elementi
    addDeleteButtons(buttonLayout);
    contentLayout->addLayout(buttonLayout);
    // area di ricerca nel contenitore
    addSearchArea(searchLayout);
    contentLayout->addLayout(searchLayout);
    // log degli ordini
    addOrdersLog(contentLayout);

    contentLayout->setContentsMargins(5, 5, 5, 5);
    mainLayout->addLayout(contentLayout);

    setWindowTitle("QCafe - Barista");
}

void QCafe_Barista::addOrderTabs() {
    ordersTab->addSingleTab(new OrderList(this), ordersQueueLabel); // tab position 0
    ordersTab->addSingleTab(new OrderList(this), searchLabel); // tab position 1

    // selezione contigua solo nel primo tab perché quello di ricerca potrebbe avere elementi contigui non consecutivi nel container
    ordersTab->tab(ordersQueueLabel)->setSelectionMode(OrderList::ContiguousSelection);

    connect(ordersTab, SIGNAL(currentChanged(int)), this, SLOT(enable_disable_search_tab(int)));
    connect(ordersTab->tab(ordersQueueLabel), SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(edit_queued_order(QListWidgetItem*)));
    connect(ordersTab->tab(searchLabel), SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(edit_queued_order(QListWidgetItem*)));

    // disabilitazione iniziale del tab di ricerca (attivabile in base ai segnali generati dalle combobox)
    emit ordersTab->currentChanged(0);
}

void QCafe_Barista::addOrdersLog(QVBoxLayout* layout) {
    QLabel* lbl_ordersLog = new QLabel("Orders log", this);

    ordersLog->setReadOnly(true);

    layout->addWidget(lbl_ordersLog);
    layout->addWidget(ordersLog);
}

void QCafe_Barista::addDeleteButtons(QGridLayout* layout) {
    popOrder->setToolTip("The first item in the \"Orders queue\" tab will be removed (no item needs to be selected)");
    cancelOrders->setToolTip("Selected item/items will be removed");

    connect(popOrder, SIGNAL(clicked()), this, SLOT(pop_order()));
    connect(cancelAllOrders, SIGNAL(clicked()), this, SLOT(clear_all_orders()));
    connect(cancelOrders, SIGNAL(clicked()), this, SLOT(collect_index_selected_items()));

    layout->addWidget(popOrder, 1, 1);
    layout->addWidget(cancelOrders, 1, 2);
    layout->addWidget(cancelAllOrders, 2, 1, 1, 2);
}

void QCafe_Barista::addSearchArea(QGridLayout* layout) {
    QList<QString> prodList = convertSTLStringListToQtStringList(controller->productList()); // non ci sono duplicati, va bene
    QSet<QString> set_prodCat; // ci saranno sicuramente duplicati nell'inserimento, QSet permette di non averli
    QList<QString> list_prodCat; // per passarlo alla QComboBox
    QCafe_Controller*& c = controller; // per poterlo utilizzare nella lambda

    // inserisco le categorie (ovvero le classi) dei prodotti presenti in prodList
    std::for_each(prodList.begin(), prodList.end(), [&set_prodCat, &c](const QString& p) {
        set_prodCat.insert(QString::fromStdString(c->productType(p.toStdString())));
    });

    // aggiungo un primo valore (searchBoxDefaultValue) che non permette l'attivazione del tasto Search
    // (messo come primo anche perché così la sua posizione è 0 e posso usarla come valore false booleano)
    prodList.push_front(searchBoxDefaultValue);
    (list_prodCat = set_prodCat.toList()).push_front(searchBoxDefaultValue);
    productNames->addItems(prodList);
    productCategories->addItems(list_prodCat);

    connect(productNames, SIGNAL(currentIndexChanged(int)), this, SLOT(setSearchButtonCheckable(int)));
    connect(productCategories, SIGNAL(currentIndexChanged(int)), this, SLOT(setSearchButtonCheckable(int)));
    connect(searchButton, SIGNAL(clicked()), this, SLOT(set_search_mode()));

    layout->addWidget(new QLabel("Product category", this), 0, 0, 1, 1);
    layout->addWidget(productCategories, 0, 1, 1, 1);
    layout->addWidget(new QLabel("Product name", this), 1, 0, 1, 1);
    layout->addWidget(productNames, 1, 1, 1, 1);
    layout->addWidget(searchButton, 0, 2, 2, 2);

    // disabilito il pulsante di ricerca inizialmente
    emit productNames->currentIndexChanged(productNames->currentIndex());
}

void QCafe_Barista::add_entry(const string& orderText, const list<string>& propertyLabels, const list<string>& propertyValues) {
    QList<QString> pl = convertSTLStringListToQtStringList(propertyLabels), pv = convertSTLStringListToQtStringList(propertyValues);

    ordersTab->tab(ordersQueueLabel)->addItem(pl, pv);

    ordersLog->append(QString::fromStdString(orderText) + "\n------ ORDER FINISHED\n");
}

void QCafe_Barista::pop_order() {
    controller->popOrder();
}

void QCafe_Barista::clear_all_orders() {
    controller->clearAllOrders();
}

void QCafe_Barista::edit_queued_order(QListWidgetItem* item) {
    // conversione da QListWidgetItem* a OrderListItem*
    OrderListItem* oli = static_cast<OrderListItem*>(item);

    // beverage o food? verifica con controller->productType
    string prodType;
    QList<QString> pl = oli->propertyLabels(), pv = oli->propertyValues();
    bool foundProdName = false;
    for(int i = 0; i < pl.length() && !foundProdName; ++i) {
        if(pl.at(i) == "Product name") {
            foundProdName = true;
            prodType = controller->productType(pv.at(i).toStdString());
        }
    }

    // generazione dialog per la modifica
    EditQueuedOrderDialog* dialog;
    if(prodType == "Coffee" || prodType == "Coffee_Milk" || prodType == "Tea") {
         dialog = new EditQueuedOrderDialog(EditQueuedOrderDialog::BEVERAGE, oli->text(), this);
         dialog->setQueuedOrderEditableSettings(convertSTLStringListToQtStringList(controller->editQueuedOrderSettings()));
    } else { // prodType == "Sweet" || prodType == "Sandwich"
        dialog = new EditQueuedOrderDialog(EditQueuedOrderDialog::FOOD, oli->text(), this);
    }

    QList<QVariant> values = dialog->execAndReturnValues(); // due elementi ritornati: primo è convertibile a bool, il secondo a bool o string

    if(values.isEmpty()) return;

    // conversione dei QVariant a bool e bool/string per passare i dati al controller
    QCafe_Controller::orderInfo new_info;
    if(values.back().canConvert(QMetaType::QString)) {
        new_info = controller->editOrderAt(oli->itemIndex()-1, values.first().toBool(), values.back().toString().toStdString());
    } else if(values.back().canConvert(QMetaType::Bool)) {
        new_info = controller->editOrderAt(oli->itemIndex()-1, values.first().toBool(), values.back().toBool());
    }

    QList<QString> new_pv = convertSTLStringListToQtStringList(new_info.productValues); // assegno a una variabile perché potrei riutilizzarla in seguito
    oli->replacePropertyValues(new_pv);

    // se la OrderList in cui ho fatto le modifiche è il tab etichettato da ordersQueueLabel allora sono a posto
    // altrimenti devo cercare il corrispondente OrderListItem in quel tab e modificarlo
    if(oli->listWidget() != ordersTab->tab(ordersQueueLabel)) {
        bool found = false;
        OrderList* ol = ordersTab->tab(ordersQueueLabel);
        for(int i = 0; i < ol->count() && !found; ++i) {
            if(ol->item(i)->itemIndex() == new_info.orderNumber) {
                ol->item(i)->replacePropertyValues(new_pv);
                found = true;
            }
        }
    }
}

void QCafe_Barista::clear_log() {
    if(ordersTab->tab(ordersQueueLabel)->count() == 0)
        ordersLog->clear();
}

void QCafe_Barista::remove_entries(int index1, int index2) {
    // index2 == -1 indica che devo rimuovere solo l'elemento con itemIndex() == index1
    if(index2 == -1) index2 = index1; // assegno un nuovo valore a index2 in modo che sia vero il controllo nell'if eseguito dentro al ciclo for

    OrderList* selected = static_cast<OrderList*>((ordersTab->currentWidget()));
    OrderList* ol = ordersTab->tab(ordersQueueLabel);
    int items_deleted = 0, items_to_delete = index2 - index1 + 1; // rimozione di uno (index1 == index2) o più (index1 < index2) elementi contigui nel contenitore e nella vista

    int i = 0;
    while(i < ol->count() && items_deleted < items_to_delete) {
        if(ol->item(i)->itemIndex() >= index1+1 && ol->item(i)->itemIndex() <= index2+1) {
            delete ol->takeItem(i);
            ++items_deleted;
            // non incremento i perché ol->count() è diminuito di 1
        } else ++i;
    }

    if(ol != selected) {
        // basta scorrere fino al primo elemento con itemIndex() == index1, perché l'area di ricerca non ha la selezione contigua
        i = 0;
        items_deleted = 0;
        while(i < selected->count() && items_deleted < items_to_delete) {
            if(selected->item(i)->itemIndex() == index1+1) {
                delete selected->takeItem(i);
                ++items_deleted;
            } else ++i;
        }
    }

    update_indexes(index2+1, items_to_delete);
}

void QCafe_Barista::update_indexes(int removedIndex, int shifted_positions) {
    OrderList* selected = static_cast<OrderList*>(ordersTab->currentWidget());
    OrderList* ol = ordersTab->tab(ordersQueueLabel);

    for(int i = 0; i < ol->count(); ++i) {
        if(ol->item(i)->itemIndex() > removedIndex) {
            ol->item(i)->setItemIndex(ol->item(i)->itemIndex()-shifted_positions);
            ol->item(i)->refreshData();
        }
    }

    if(selected != ol) {
        for(int i = 0; i < selected->count(); ++i) {
            if(selected->item(i)->itemIndex() > removedIndex) {
                selected->item(i)->setItemIndex(selected->item(i)->itemIndex()-shifted_positions);
                selected->item(i)->refreshData();
            }
        }
    }
}

void QCafe_Barista::collect_index_selected_items() {
    OrderList* ol = static_cast<OrderList*>(ordersTab->currentWidget());

    // se ol corrisponde al tab "Orders queue" è abilitata la selezione di elementi contigui, altrimenti no

    if(ol->selectedItems().isEmpty()) return;

    int index1 = ol->selectedItems().front()->itemIndex() - 1; // itemIndex()-1 corrisponde all'indice dell'elemento nel container
    int index2 = ol->selectedItems().back()->itemIndex() - 1;

    if(index1 == index2) controller->removeOrders(index1);
    else controller->removeOrders(index1, index2);
}

void QCafe_Barista::set_search_mode() {
    // controllo quale combobox è compilata
    if(productNames->currentIndex() == 0 && productCategories->currentIndex() == 0) return;

    if(productNames->currentText() != searchBoxDefaultValue) { // se la combobox productNames è compilata, prevale sull'altra perché è più specifica
        search_by_product_name(productNames->currentText());
    } else {
        search_by_product_category(productCategories->currentText());
    }
}

void QCafe_Barista::search_by_product_name(const QString& pn) {
    list<QCafe_Controller::orderInfo> orders = controller->findByProductName(pn.toStdString());
    OrderList* searchList = ordersTab->tab(searchLabel);

    for(auto cit = orders.cbegin(); cit != orders.cend(); ++cit) {
        searchList->addItem(convertSTLStringListToQtStringList((*cit).productLabels), convertSTLStringListToQtStringList((*cit).productValues), (*cit).orderNumber);
    }

    // seleziono il tab di ricerca, il segnale generato chiamerà lo slot enable_disable_search_tab
    ordersTab->setCurrentIndex(1);
}

void QCafe_Barista::search_by_product_category(const QString& pc) {
    list<QCafe_Controller::orderInfo> orders = controller->findByProductCategory(pc.toStdString());
    OrderList* searchList = ordersTab->tab(searchLabel);

    for(auto cit = orders.cbegin(); cit != orders.cend(); ++cit) {
        searchList->addItem(convertSTLStringListToQtStringList((*cit).productLabels), convertSTLStringListToQtStringList((*cit).productValues), (*cit).orderNumber);
    }

    // seleziono il tab di ricerca, il segnale generato chiamerà lo slot enable_disable_search_tab
    ordersTab->setCurrentIndex(1);
}

void QCafe_Barista::setSearchButtonCheckable(int toCheck) {
    if((toCheck == 0 && productNames->currentIndex() == 0 && productCategories->currentIndex() == 0) || (toCheck > 0 && !searchButton->isEnabled()))
        searchButton->setEnabled(toCheck);
}

void QCafe_Barista::enable_disable_search_tab(int tab_index) {
    // tab_index == 0 => il tab è etichettato da ordersQueueLabel
    // tab_index == 1 => il tab è etichettato searchLabel
    if(tab_index == 0) {
        // disabilito il tab di ricerca
        ordersTab->setTabEnabled(1, false);
        // pulisco la lista degli elementi cercati
        ordersTab->tab(searchLabel)->clear();
        // riabilito i pulsanti di eliminazione elementi
        cancelAllOrders->setEnabled(true);
        popOrder->setEnabled(true);
        // emetto il segnale che fara' effettuare la verifica se abilitare search o meno
        emit productNames->currentIndexChanged(productNames->currentIndex());
    } else if(tab_index == 1) {
        // abilito il tab di ricerca
        ordersTab->setTabEnabled(1, true);
        // disabilito i pulsanti di eliminazione elementi
        cancelAllOrders->setEnabled(false);
        popOrder->setEnabled(false);
        // disabilito il pulsante di ricerca
        searchButton->setEnabled(false);
    }
}
