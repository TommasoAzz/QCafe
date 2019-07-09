#include "Sweet.h"
using std::string;
using QCafe::Sweet;
using QCafe::QCafe_type;

const bool Sweet::WHIPPED_CREAM = true;
const bool Sweet::NO_WHIPPED_CREAM = false;

const std::vector<string> Sweet::Sweet_List = {"Cake", "Doughnut", "Muffin"};

Sweet::Sweet(const string& sweet_name, bool whipped_cream, enum flavour chosen_flavour, bool needs_heating, const string& customer_name, bool take_away, double discount):
Food(sweet_name, needs_heating, customer_name, take_away, discount), whipped_cream(whipped_cream), _flavour(chosen_flavour) {}

bool Sweet::whippedCream() const {
    return whipped_cream;
}

Sweet::flavour Sweet::flavouring() const {
    return _flavour;
}

void Sweet::setWhippedCream(bool c) {
    whipped_cream = c;
}

void Sweet::setFlavour(enum flavour f) {
    _flavour = f;
}

bool Sweet::isVegan() const {
    return false;
}

bool Sweet::isVegetarian() const {
    return true;
}

bool Sweet::isGlutenFree() const {
    return false; 
}

double Sweet::price() const {
    double price = 0.0;

    if(productName() == "Cake") price += 3.00;
    else if(productName() == "Doughnut") price += 2.50;
    else if(productName() == "Muffin") price += 2.00;

    if(_flavour != PLAIN) price += 0.30;

    if(whipped_cream) price += 0.50;

    return price;
}

Sweet* Sweet::clone() const {
    return new Sweet(*this);
}

QCafe_type Sweet::className() const {
    return SWEET;
}

string Sweet::to_string(flavour f) {
    return f == PLAIN ? "Plain" : (f == CHOCOLATE ? "Chocolate" : "Apple and cinnamon");
}

Sweet::flavour Sweet::to_flavour(const string& f) {
    return f == "Plain" ? PLAIN : (f == "Chocolate" ? CHOCOLATE : APPLE_AND_CINNAMON);
}

string Sweet::orderDetails() const {
    return Food::orderDetails() + (whipped_cream ? "ADD: Whipped cream" : "") + "\nFLAVOUR: " + to_string(_flavour) + "\n";
}
