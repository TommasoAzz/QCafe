#include "Coffee.h"
using std::string;
using QCafe::Coffee;
using QCafe::QCafe_type;

const std::vector<string> Coffee::Coffee_List = {"Espresso", "Lungo", "Americano", "Black", "French Press", "Cold Brew"};

Coffee::Coffee(const string& coffee_name, cup_size cs, coffee_variety cv, sweetener_type st, const string& customer_name, bool take_away, double discount):
Beverage(coffee_name, cs, st, customer_name, take_away, discount), _variety(cv) {}

Coffee::coffee_variety Coffee::variety() const {
    return _variety;
}

void Coffee::setVariety(coffee_variety cv) {
    _variety = cv;
}

string Coffee::grinding() const {
    if(productName() == Coffee_List[5]) return "Extra coarse";
    else if(productName() == Coffee_List[4]) return "Coarse";
    else if(productName() == Coffee_List[3]) return "Medium";
    else return "Fine";
}

string Coffee::brewingDevice() const {
    if(productName() == Coffee_List[5] || productName() == Coffee_List[4]) return "French Press";
    if(productName() == Coffee_List[3]) return "Coffee Maker";
    else return "Espresso Machine";
}

double Coffee::price() const {
    double price = 0.0;
    
    if(cupSize() == SMALL) price += 1.0;
    else if(cupSize() == MEDIUM) price += 2.0;
    else if(cupSize() == LARGE) price += 3.0;

    if(_variety == ROBUSTA) price -= 0.1;

    if(productName() == Coffee_List[5] || productName() == Coffee_List[4]) price += 1.0;
    else if(productName() == Coffee_List[2]) price += 0.5;
    
    return price;
}

Coffee* Coffee::clone() const {
    return new Coffee(*this);
}

QCafe_type Coffee::className() const {
    return COFFEE;
}

string Coffee::to_string(coffee_variety va) {
    return va == ROBUSTA ? "Robusta" : "Arabica";
}

Coffee::coffee_variety Coffee::to_coffee_variety(const string& va) {
    return va == "Robusta" ? ROBUSTA : ARABICA;
}

string Coffee::orderDetails() const {
    string det = "VARIETY: " + to_string(_variety) + "\nGRINDING: " + grinding() + "\nBREWING DEVICE: " + brewingDevice();
    return Beverage::orderDetails() + det + "\n" ;
}
