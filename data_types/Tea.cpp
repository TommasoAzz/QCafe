#include "Tea.h"
using std::string;
using QCafe::Tea;
using QCafe::QCafe_type;

const std::vector<string> Tea::Tea_List = {"Ceylon", "Darjeeling", "Earl Grey", "English Breakfast", "Gunpowder", "Jasmine Green", "Lemon", "Matcha", "Peach", "Pure Green", "Pure White"};

Tea::Tea(const string& tea_name, cup_size cs, sweetener_type st, const string& customer_name, bool take_away, double discount):
Beverage(tea_name, cs, st, customer_name, take_away, discount) {
}

string Tea::orderDetails() const {
    return Beverage::orderDetails() + "TEA TYPE: " + type() + "\n";
}

string Tea::type() const {
    if(productName() == Tea_List[4] || productName() == Tea_List[5] || productName() == Tea_List[7] || productName() == Tea_List[8]) return "Green";
    else if(productName() == Tea_List[10]) return "White";
    else return "Black";
}

double Tea::price() const {
    double price = 0.0;
    
    if(type() == "Green") price += 0.2;
    else if(type() == "White") price += 0.4;

    if(cupSize() == SMALL) price = 1.5;
    else if(cupSize() == MEDIUM) price += 2.5;
    else if(cupSize() == LARGE) price += 3.5;

    if(productName() == Tea_List[1] || productName() == Tea_List[4] || productName() == Tea_List[7]) price += 0.5;

    return price;
}

Tea* Tea::clone() const {
    return new Tea(*this);
}

QCafe_type Tea::className() const {
    return TEA;
}

