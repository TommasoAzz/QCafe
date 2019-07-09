#include "Beverage.h"
using std::string;
using QCafe::Beverage;
using QCafe::QCafe_type;

Beverage::Beverage(const string& beverage_name, cup_size cs, sweetener_type st, const string& customer_name, bool take_away, double discount):
Order(beverage_name, customer_name, take_away, discount), _sweetener(st), _size(cs) {}

Beverage::sweetener_type Beverage::sweetenerType() const {
    return _sweetener;
}

Beverage::cup_size Beverage::cupSize() const {
    return _size;
}

void Beverage::setSweetenerType(sweetener_type st) {
    _sweetener = st;
}

void Beverage::setCupSize(cup_size cs) {
    _size = cs;
}

string Beverage::orderDetails() const {
    string det = "SIZE: " + to_string(_size);

    return (_sweetener == NO_SWEETENER ? det : (det + "\nSWEETENER: " + to_string(_sweetener))) + "\n";
}

string Beverage::to_string(cup_size cs) {
    return cs == SMALL ? "S" : (cs == MEDIUM ? "M" : "L");
}

string Beverage::to_string(sweetener_type st) {
    return st == SUGAR ? "Sugar" : (st == SWEETENER ? "Sweetener" : "None");
}

Beverage::cup_size Beverage::to_cup_size(const string& cs) {
    return cs == "S" ? SMALL : (cs == "M" ? MEDIUM : LARGE);
}

Beverage::sweetener_type Beverage::to_sweetener_type(const string& st) {
    return st == "Sugar" ? SUGAR : (st == "Sweetener" ? SWEETENER : NO_SWEETENER);
}
