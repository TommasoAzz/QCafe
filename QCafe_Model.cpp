#include "QCafe_Model.h"
#include "data_types/Tea.h"
#include "data_types/Sandwich.h"
#include "data_types/Sweet.h"

using std::string;
using QCafe::Order;
using QCafe::Beverage;
using QCafe::Coffee;
using QCafe::Coffee_Milk;
using QCafe::Tea;
using QCafe::Food;
using QCafe::Sandwich;
using QCafe::Sweet;
using QCafe::QCafe_type;

QCafe_Model::QCafe_Model():
Coffee_List(&Coffee::Coffee_List),
Coffee_Milk_List(&Coffee_Milk::Coffee_Milk_List),
Tea_List(&Tea::Tea_List),
Sweet_List(&Sweet::Sweet_List),
Sandwich_List(&Sandwich::Sandwich_List) {}

Qontainer<DeepPtr<QCafe::Order> > QCafe_Model::getOrders() const {
    return orders;
}

void QCafe_Model::pushOrder(Order* o) {
    orders.push(DeepPtr<Order>(o)); //o => DeepPtr(o)
}

void QCafe_Model::popOrder() {
    orders.pop();
}

void QCafe_Model::clearAllOrders() {
    orders.clear();
}

Qontainer< DeepPtr<Order> >::iterator QCafe_Model::removeItem(Qontainer< DeepPtr<Order> >::iterator it) {
    return orders.erase(it);
}

Qontainer< DeepPtr<Order> >::iterator QCafe_Model::removeItems(Qontainer< DeepPtr<Order> >::iterator it1, Qontainer< DeepPtr<Order> >::iterator it2) {
    return orders.erase(it1, it2);
}

Qontainer< DeepPtr<Order> >::iterator QCafe_Model::firstItem() {
    return orders.begin();
}

Qontainer< DeepPtr<Order> >::iterator QCafe_Model::lastItem() {
    Qontainer< DeepPtr<Order> >::iterator it = orders.begin();
    while(it+1 != orders.end()) it++;
    return it;
}

Qontainer< DeepPtr<Order> >::iterator QCafe_Model::pastTheEnd() {
    return orders.end();
}

int QCafe_Model::numberOfOrders() const {
    return static_cast<int>(orders.size());
}

Qontainer<Order*> QCafe_Model::findByProductName(const string& product_name) const {
    Qontainer<Order*> output;

    for(auto cit = orders.cbegin(); cit != orders.cend(); ++cit)
        if((*cit)->productName() == product_name)
            output.push(&(*(*cit)));

    return output;
}

Qontainer<Order*> QCafe_Model::findByCategory(QCafe_type cat) const {
    Qontainer<Order*> output;

    switch(cat) {
    case QCafe::COFFEE:
        for(auto cit = orders.cbegin(); cit != orders.cend(); ++cit) {
            if((*cit)->className() == QCafe::COFFEE) {
                output.push(&(*(*cit)));
            }
        }
        break;
    case QCafe::COFFEE_MILK:
        for(auto cit = orders.cbegin(); cit != orders.cend(); ++cit) {
            if((*cit)->className() == QCafe::COFFEE_MILK) {
                output.push(&(*(*cit)));
            }
        }
        break;
    case QCafe::TEA:
        for(auto cit = orders.cbegin(); cit != orders.cend(); ++cit) {
            if((*cit)->className() == QCafe::TEA) {
                output.push(&(*(*cit)));
            }
        }
        break;
    case QCafe::SWEET:
        for(auto cit = orders.cbegin(); cit != orders.cend(); ++cit) {
            if((*cit)->className() == QCafe::SWEET) {
                output.push(&(*(*cit)));
            }
        }
        break;
    case QCafe::SANDWICH:
        for(auto cit = orders.cbegin(); cit != orders.cend(); ++cit) {
            if((*cit)->className() == QCafe::SANDWICH) {
                output.push(&(*(*cit)));
            }
        }
        break;
    }

    return output;
}
