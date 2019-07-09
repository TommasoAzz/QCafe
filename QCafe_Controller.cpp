#include "QCafe_Controller.h"
using std::string;
using std::find;
using std::vector;
using std::list;
using std::map;
using QCafe::Order;
using QCafe::Beverage;
using QCafe::Food;
using QCafe::Coffee;
using QCafe::Coffee_Milk;
using QCafe::Tea;
using QCafe::Sandwich;
using QCafe::Sweet;
using QCafe::QCafe_type;

QCafe_Controller::QCafe_Controller(QCafe_Model* m): model(m), barista(new QCafe_Barista(this)), cashier(new QCafe_Cashier(this)), fileIO(new XMLFileIO()) {}

QCafe_Controller::~QCafe_Controller() {
    // il modello mi e' passato come parametro in costruzione: e' compito del chiamante deallocarlo
    if(barista) delete barista;
    if(cashier) delete cashier;
    if(fileIO) delete fileIO;
}

// -- Coffee
void QCafe_Controller::pushOrder(const string& coffee_name, const string& cup_size, const string& coffee_variety, const string& sweetener_type, const string& customer_name, bool take_away, double discount) const {
    model->pushOrder(new Coffee(coffee_name, Beverage::to_cup_size(cup_size), Coffee::to_coffee_variety(coffee_variety), Beverage::to_sweetener_type(sweetener_type), customer_name, take_away, discount));
    Coffee* c = static_cast<Coffee*>(&(*(*(model->lastItem()))));

    // verranno inseriti solo i campi dati utili a chi prepara il prodotto
    insertOrder(c->printOrder(), orderLabels(c), orderValues(c));
}

// -- Coffee_Milk
void QCafe_Controller::pushOrder(const string& coffee_name, const string& cup_size, const std::string& coffee_variety, const string& sweetener_type, bool whipped_cream, const string& customer_name, bool take_away, double discount) const {
    model->pushOrder(new Coffee_Milk(coffee_name, Beverage::to_cup_size(cup_size), Coffee::to_coffee_variety(coffee_variety), Beverage::to_sweetener_type(sweetener_type), whipped_cream, customer_name, take_away, discount));
    Coffee_Milk* c = static_cast<Coffee_Milk*>(&(*(*(model->lastItem()))));

    // verranno inseriti solo i campi dati utili a chi prepara il prodotto
    insertOrder(c->printOrder(), orderLabels(c), orderValues(c));
}

// -- Tea
void QCafe_Controller::pushOrder(const string& tea_name, const string& cup_size, const string& sweetener_type, const string& customer_name, bool take_away, double discount) const {
    model->pushOrder(new Tea(tea_name, Beverage::to_cup_size(cup_size), Beverage::to_sweetener_type(sweetener_type), customer_name, take_away, discount));
    Tea* t = static_cast<Tea*>(&(*(*(model->lastItem()))));

    // verranno inseriti solo i campi dati utili a chi prepara il prodotto
    insertOrder(t->printOrder(), orderLabels(t), orderValues(t));
}

// -- Sandwich
void QCafe_Controller::pushOrder(const string& bread_type, const string& main_ingredient, const string& sauce, bool cheese, bool lettuce, bool needs_heating, const string& customer_name, bool take_away, double discount) const {
    model->pushOrder(new Sandwich(Sandwich::to_bread_type(bread_type), Sandwich::to_main_ingredient(main_ingredient), Sandwich::to_sauce_type(sauce), cheese, lettuce, needs_heating, customer_name, take_away, discount));
    Sandwich* s = static_cast<Sandwich*>(&(*(*(model->lastItem()))));

    // verranno inseriti solo i campi dati utili a chi prepara il prodotto
    insertOrder(s->printOrder(), orderLabels(s), orderValues(s));
}

// -- Sweet
void QCafe_Controller::pushOrder(const string& sweet_name, bool whipped_cream, const string& chosen_flavour, bool needs_heating, const string& customer_name, bool take_away, double discount) const {
    model->pushOrder(new Sweet(sweet_name, whipped_cream, Sweet::to_flavour(chosen_flavour), needs_heating, customer_name, take_away, discount));
    Sweet* s = static_cast<Sweet*>(&(*(*(model->lastItem()))));

    // verranno inseriti solo i campi dati utili a chi prepara il prodotto
    insertOrder(s->printOrder(), orderLabels(s), orderValues(s));
}

void QCafe_Controller::popOrder() const {
    barista->remove_entries(0);
    model->popOrder();
    barista->clear_log();
}

void QCafe_Controller::clearAllOrders() const {
    barista->remove_entries(0, model->numberOfOrders()-1);
    model->clearAllOrders();
    barista->clear_log();
}

std::string QCafe_Controller::logFileExtension() {
    return ".xml";
}

void QCafe_Controller::openLog(const string& filename) const {
    if(filename != fileIO->filename())
        fileIO->setFileName(filename);

    Qontainer< DeepPtr<Order> > q = fileIO->readFromFile();  // può lanciare eccezioni, le gestisce la view

    // set dei nuovi dati enum QCafe_type: unsigned int { ORDER, BEVERAGE, TEA, COFFEE, COFFEE_MILK, FOOD, SWEET, SANDWICH };
    clearAllOrders();
    for(auto it = q.cbegin(); it != q.cend(); ++it) {
        switch((*it)->className()) {
            case QCafe::COFFEE: {
                const Coffee* c = static_cast<const Coffee*>(&(*(*it)));
                pushOrder(c->productName(), Beverage::to_string(c->cupSize()), Coffee::to_string(c->variety()), Beverage::to_string(c->sweetenerType()), c->customerName(), c->takeAway(), c->discountAmount());
                break;
            }
            case QCafe::COFFEE_MILK: {
                const Coffee_Milk* c = static_cast<const Coffee_Milk*>(&(*(*it)));
                pushOrder(c->productName(), Beverage::to_string(c->cupSize()), Coffee::to_string(c->variety()), Beverage::to_string(c->sweetenerType()), c->whippedCream(), c->customerName(), c->takeAway(), c->discountAmount());
                break;
            }
            case QCafe::TEA: {
                const Tea* t = static_cast<const Tea*>(&(*(*it)));
                pushOrder(t->productName(), Beverage::to_string(t->cupSize()), Beverage::to_string(t->sweetenerType()), t->customerName(), t->takeAway(), t->discountAmount());
                break;
            }
            case QCafe::SWEET: {
                const Sweet* s = static_cast<const Sweet*>(&(*(*it)));
                pushOrder(s->productName(), s->whippedCream(), Sweet::to_string(s->flavouring()), s->heating(), s->customerName(), s->takeAway(), s->discountAmount());
                break;
            }
            case QCafe::SANDWICH: {
                const Sandwich* s = static_cast<const Sandwich*>(&(*(*it)));
                pushOrder(Sandwich::to_string(s->bread()), Sandwich::to_string(s->mainIngredient()), Sandwich::to_string(s->sauce()), s->cheese(), s->lettuce(), s->heating(), s->customerName(), s->takeAway(), s->discountAmount());
                break;
            }
        }
    }
}

void QCafe_Controller::saveLog(const string& filename) const {
    if(filename != fileIO->filename())
        fileIO->setFileName(filename);

    fileIO->writeOnFile(model->getOrders()); // può lanciare eccezioni, le gestisce la view
}

void QCafe_Controller::showView() const {
    cashier->show();
    barista->show();
}

string QCafe_Controller::productType(const string& product) const {
    string type;

    if(find(model->Coffee_List->begin(), model->Coffee_List->end(), product) != model->Coffee_List->end()) {
        type = "Coffee";
    } else if(find(model->Coffee_Milk_List->begin(), model->Coffee_Milk_List->end(), product) != model->Coffee_Milk_List->end()) {
        type = "Coffee_Milk";
    } else if(find(model->Tea_List->begin(), model->Tea_List->end(), product) != model->Tea_List->end()) {
        type = "Tea";
    } else if(find(model->Sandwich_List->begin(), model->Sandwich_List->end(), product) != model->Sandwich_List->end()) {
        type = "Sandwich";
    } else if(find(model->Sweet_List->begin(), model->Sweet_List->end(), product) != model->Sweet_List->end()) {
        type = "Sweet";
    }

    return type;
}

list<string> QCafe_Controller::productList() const {
    list<string> product_list;

    product_list.insert(product_list.begin(), model->Coffee_List->begin(), model->Coffee_List->end());
    product_list.insert(product_list.end(), model->Coffee_Milk_List->begin(), model->Coffee_Milk_List->end());
    product_list.insert(product_list.end(), model->Tea_List->begin(), model->Tea_List->end());
    product_list.insert(product_list.end(), model->Sweet_List->begin(), model->Sweet_List->end());
    product_list.insert(product_list.end(), model->Sandwich_List->begin(), model->Sandwich_List->end());

    return product_list;
}

map<QCafe_Cashier::ComboBoxName, list<string> > QCafe_Controller::editOrderSettings() {
    return {
        // per inizializzazione QComboBox - Coffee/Tea sweetener, cupSize
        {
            QCafe_Cashier::CB_SWEETENER, {
                Beverage::to_string(Beverage::NO_SWEETENER),
                Beverage::to_string(Beverage::SUGAR),
                Beverage::to_string(Beverage::SWEETENER)
            }
        },
        {
            QCafe_Cashier::CB_CUP_SIZE, {
                Beverage::to_string(Beverage::SMALL),
                Beverage::to_string(Beverage::MEDIUM),
                Beverage::to_string(Beverage::LARGE)
            }
        },
        // per inizializzazione QComboBox - Coffee variety
        {
            QCafe_Cashier::CB_VARIETY, {
                Coffee::to_string(Coffee::ARABICA),
                Coffee::to_string(Coffee::ROBUSTA)
            }
        },
        // per inizializzazione QComboBox - Sweet flavour
        {
            QCafe_Cashier::CB_FLAVOUR, {
                Sweet::to_string(Sweet::PLAIN),
                Sweet::to_string(Sweet::CHOCOLATE),
                Sweet::to_string(Sweet::APPLE_AND_CINNAMON),
            }
        },
        // per inizializzazione QComboBox - Sandwich breadType
        {
            QCafe_Cashier::CB_BREAD_TYPE, {
                Sandwich::to_string(Sandwich::WHITE),
                Sandwich::to_string(Sandwich::WHOLE_GRAIN),
                Sandwich::to_string(Sandwich::GLUTEN_FREE),
            }
        },
        // per inizializzazione QComboBox - Sandwich mainIngredient
        {
            QCafe_Cashier::CB_MAIN_INGREDIENT, {
                Sandwich::to_string(Sandwich::HAM),
                Sandwich::to_string(Sandwich::BEEF),
                Sandwich::to_string(Sandwich::CHICKEN),
                Sandwich::to_string(Sandwich::SEITAN),
                Sandwich::to_string(Sandwich::AUBERGINES),
            }
        },
        // per inizializzazione QComboBox - Sandwich sauce
        {
            QCafe_Cashier::CB_SAUCE, {
                Sandwich::to_string(Sandwich::NO_SAUCE),
                Sandwich::to_string(Sandwich::KETCHUP),
                Sandwich::to_string(Sandwich::MAYONNAISE),
                Sandwich::to_string(Sandwich::MUSTARD),
            }
        }
    };
}

int QCafe_Controller::numberOfOrders() const {
    return model->numberOfOrders();
}

void QCafe_Controller::insertOrder(const string& orderText, const list<string>& productLabels, const list<string>& productValues) const {
    barista->add_entry(orderText, productLabels, productValues);
}

list<string> QCafe_Controller::orderLabels(const Order* o) {
    list<string> prodLabels = {"Product name", "Customer name", "Take away"}; // valide per tutti in quanto campi dati di Order
    QCafe_type class_name = o->className();

    if(class_name == QCafe::COFFEE || class_name == QCafe::COFFEE_MILK || class_name == QCafe::TEA) {
        prodLabels.push_back("Cup size");
        prodLabels.push_back("Sweetener");
        if(class_name == QCafe::COFFEE || class_name == QCafe::COFFEE_MILK) {
            prodLabels.push_back("Variety");
            prodLabels.push_back("Grinding");
            prodLabels.push_back("Brewing device");
            if(class_name == QCafe::COFFEE_MILK) {
                prodLabels.push_back("Milk");
            }
        } else if(class_name == QCafe::TEA) {
            prodLabels.push_back("Type");
        }
    } else if(class_name == QCafe::SANDWICH || class_name == QCafe::SWEET) {
        prodLabels.push_back("To heat");
        prodLabels.push_back("Vegan/Vegetarian");
        prodLabels.push_back("Gluten free");
        if(class_name == QCafe::SANDWICH) {
            prodLabels.push_back("Bread");
            prodLabels.push_back("Main ingredient");
            prodLabels.push_back("Cheese");
            prodLabels.push_back("Lettuce");
            prodLabels.push_back("Sauce");
        } else if(class_name == QCafe::SWEET) {
            prodLabels.push_back("Flavour");
            prodLabels.push_back("Whipped cream");
        }
    }

    return prodLabels;
}

list<string> QCafe_Controller::orderValues(const Order* o) {
    list<string> prodValues = {o->productName(), o->customerName(), o->takeAway() ? "Yes" : "No"}; // valide per tutti in quanto campi dati di Order
    QCafe_type class_name = o->className();

    if(class_name == QCafe::COFFEE || class_name == QCafe::COFFEE_MILK || class_name == QCafe::TEA) {
        const Beverage* b = static_cast<const Beverage*>(o);
        prodValues.push_back(Beverage::to_string(b->cupSize()));
        prodValues.push_back(Beverage::to_string(b->sweetenerType()));
        if(class_name == QCafe::COFFEE || class_name == QCafe::COFFEE_MILK) {
            const Coffee* c = static_cast<const Coffee*>(b);
            prodValues.push_back(Coffee::to_string(c->variety()));
            prodValues.push_back(c->grinding());
            prodValues.push_back(c->brewingDevice());
            if(class_name == QCafe::COFFEE_MILK) {
                const Coffee_Milk* cm = static_cast<const Coffee_Milk*>(c);
                string milk = string((cm->milkFoam() ? "Milk foam " : "")) + (cm->steamedMilk() ? "Steamed milk " : "") + (cm->whippedCream() ? "Whipped cream" : "");
                prodValues.push_back(milk);
            } else if(class_name == QCafe::TEA) {
                const Tea* t = static_cast<const Tea*>(b);
                prodValues.push_back(t->type());
            }
        }
    } else if(class_name == QCafe::SANDWICH || class_name == QCafe::SWEET) {
        const Food* f = static_cast<const Food*>(o);
        prodValues.push_back(f->heating() ? "Yes" : "No");
        prodValues.push_back(f->isVegan() ? "Vegan" : (f->isVegetarian() ? "Vegetarian" : "No"));
        prodValues.push_back(f->isGlutenFree() ? "Yes" : "No");
        if(class_name == QCafe::SANDWICH) {
            const Sandwich* s = static_cast<const Sandwich*>(f);
            prodValues.push_back(Sandwich::to_string(s->bread()));
            prodValues.push_back(Sandwich::to_string(s->mainIngredient()));
            prodValues.push_back(s->cheese() ? "Yes" : "No");
            prodValues.push_back(s->lettuce() ? "Yes" : "No");
            prodValues.push_back(Sandwich::to_string(s->sauce()));
        } else if(class_name == QCafe::SWEET) {
            const Sweet* s = static_cast<const Sweet*>(f);
            prodValues.push_back(Sweet::to_string(s->flavouring()));
            prodValues.push_back(s->whippedCream() ? "Yes" : "No");
        }
    }

    return prodValues;
}

list<QCafe_Controller::orderInfo> QCafe_Controller::prepareFind(const Qontainer<Order*>& q) const {
    if(q.empty()) return {}; // ritorno una lista vuota se q è vuoto (ovvero non sono stati trovati elementi

    list<QCafe_Controller::orderInfo> found;
    int orderNumber = 1; // indice della posizione nel modello + 1 ( il primo ordine avrà orderNumber = 1)
    auto cit_q = q.cbegin();
    auto cit_m = model->firstItem();

    for(; cit_m != model->pastTheEnd(); ++cit_m) {
        if((*cit_q) == &(*(*cit_m))) {
            found.push_back(orderInfo {
                orderNumber,
                orderLabels(*cit_q),
                orderValues(*cit_q)
            });
            ++cit_q;
        }
        ++orderNumber;
    }

    return found;
}

void QCafe_Controller::removeOrders(int index1, int index2) const {
    if(index2 == -1) {
        barista->remove_entries(index1);
        model->removeItem(model->firstItem() + index1);
    } else {
        barista->remove_entries(index1, index2);
        model->removeItems(model->firstItem() + index1, model->firstItem() + index2 + 1); // index2 + 1 perché l'elemento con indice index2 lo voglio rimosso
    }
    barista->clear_log();
}

list<QCafe_Controller::orderInfo> QCafe_Controller::findByProductName(const string& pn) const {
    Qontainer<Order*> q = model->findByProductName(pn);
    list<QCafe_Controller::orderInfo> found = prepareFind(q);
    return found;
}

list<QCafe_Controller::orderInfo> QCafe_Controller::findByProductCategory(const string& pc) const {
    QCafe_type cat;
    if(pc == "Coffee") cat = QCafe::COFFEE;
    else if(pc == "Coffee_Milk") cat = QCafe::COFFEE_MILK;
    else if(pc == "Tea") cat = QCafe::TEA;
    else if(pc == "Sweet") cat = QCafe::SWEET;
    else if(pc == "Sandwich") cat = QCafe::SANDWICH;
    else return {}; // ritorno una lista vuota nel caso la categoria sia passata erroneamente

    Qontainer<Order*> q = model->findByCategory(cat);
    list<QCafe_Controller::orderInfo> found = prepareFind(q);
    return found;
}

list<string> QCafe_Controller::editQueuedOrderSettings() {
    return {
        Beverage::to_string(Beverage::NO_SWEETENER),
        Beverage::to_string(Beverage::SUGAR),
        Beverage::to_string(Beverage::SWEETENER)
    };
}

QCafe_Controller::orderInfo QCafe_Controller::editOrderAt(int index, bool take_away, bool heat_product) {
    auto it = model->firstItem() + index;
    (*it)->setTakeAway(take_away);
    static_cast<Food*>(&(*(*it)))->setHeating(heat_product);

    return {
        index+1,
        orderLabels(&(*(*it))),
        orderValues(&(*(*it)))
    };
}

QCafe_Controller::orderInfo QCafe_Controller::editOrderAt(int index, bool take_away, const string& sweetener) {
    auto it = model->firstItem() + index;
    (*it)->setTakeAway(take_away);
    static_cast<Beverage*>(&(*(*it)))->setSweetenerType(Beverage::to_sweetener_type(sweetener));

    return {
        index+1,
        orderLabels(&(*(*it))),
        orderValues(&(*(*it)))
    };
}
