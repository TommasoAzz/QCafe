#include "Sandwich.h"
using std::string;
using QCafe::Sandwich;
using QCafe::QCafe_type;

// valori per _cheese, _lettuce
const bool Sandwich::CHEESE = true;
const bool Sandwich::NO_CHEESE = false;

// valori per _lettuce
const bool Sandwich::LETTUCE = true;
const bool Sandwich::NO_LETTUCE = false;

const std::vector<string> Sandwich::Sandwich_List = {"Sandwich"};

Sandwich::Sandwich(bread_type bt, main_ingredient mi, sauce_type s, bool cheese, bool lettuce, bool needs_heating, const string& customer_name, bool take_away, double discount):
Food("Sandwich", needs_heating, customer_name, take_away, discount), _bread(bt), _ingredient(mi), _sauce(s), _cheese(cheese), _lettuce(lettuce) {}

Sandwich::bread_type Sandwich::bread() const {
    return _bread;
}

Sandwich::main_ingredient Sandwich::mainIngredient() const {
    return _ingredient;
}

Sandwich::sauce_type Sandwich::sauce() const {
    return _sauce;
}

bool Sandwich::cheese() const {
    return _cheese;
}

bool Sandwich::lettuce() const {
    return _lettuce;
}

void Sandwich::setBread(bread_type bt) {
    _bread = bt;
}

void Sandwich::setMainIngredient(main_ingredient mi) {
    _ingredient = mi;
}

void Sandwich::setSauce(sauce_type s) {
    _sauce = s;
}

void Sandwich::setCheese(bool c) {
    _cheese = c;
}

void Sandwich::setLettuce(bool l) {
    _lettuce = l;
}

bool Sandwich::isVegan() const {
    return (_ingredient == SEITAN || _ingredient == AUBERGINES) && _sauce != MAYONNAISE && !_cheese;
}

bool Sandwich::isVegetarian() const {
    return (_ingredient == SEITAN || _ingredient == AUBERGINES);
}

bool Sandwich::isGlutenFree() const {
    return _bread == GLUTEN_FREE;
}

double Sandwich::price() const {
    double price = 0.0;

    if(_bread != WHITE) price += 0.1;

    if(_ingredient == HAM) price += 3.0;
    else if(_ingredient == BEEF || _ingredient == CHICKEN || _ingredient == AUBERGINES) price += 4.0;
    else if(_ingredient == SEITAN) price += 4.5;

    if(_cheese) price += 0.2;

    if(_sauce != NO_SAUCE) price += 0.2;

    return price;
}

Sandwich* Sandwich::clone() const {
    return new Sandwich(*this);
}

QCafe_type Sandwich::className() const {
    return SANDWICH;
}

string Sandwich::to_string(bread_type bt) {
    return bt == WHOLE_GRAIN ? "Whole grain" : (bt == GLUTEN_FREE ? "Gluten free" : "White");
}

string Sandwich::to_string(main_ingredient mi) {
    string s;

    switch(mi) {
    case HAM:
        s = "Ham";
        break;
    case BEEF:
        s = "Beef";
        break;
    case CHICKEN:
        s = "Chicken";
        break;
    case SEITAN:
        s = "Seitan";
        break;
    case AUBERGINES:
        s = "Aubergines";
        break;
    }

    return s;
}

string Sandwich::to_string(sauce_type st) {
    string s;
    switch(st) {
    case KETCHUP:
        s = "Ketchup";
        break;
    case MAYONNAISE:
        s = "Mayonnaise";
        break;
    case MUSTARD:
        s = "Mustard";
        break;
    case NO_SAUCE:
        s = "None";
        break;
    }
    return s;
}

Sandwich::bread_type Sandwich::to_bread_type(const string& bt) {
    return bt == "Whole grain" ? WHOLE_GRAIN : (bt == "Gluten free" ? GLUTEN_FREE : WHITE);
}

Sandwich::main_ingredient Sandwich::to_main_ingredient(const string& mi) {
    if(mi == "Beef")
        return BEEF;
    else if(mi == "Chicken")
        return CHICKEN;
    else if(mi == "Seitan")
        return SEITAN;
    else if(mi == "Aubergines")
        return AUBERGINES;
    else return HAM; // default fallback
}

Sandwich::sauce_type Sandwich::to_sauce_type(const string& st) {
    if(st == "Ketchup")
        return KETCHUP;
    else if(st == "Mayonnaise")
        return MAYONNAISE;
    else if(st == "Mustard")
        return MUSTARD;
    else return NO_SAUCE; // default fallback
}

string Sandwich::orderDetails() const {
    return Food::orderDetails() +
            "BREAD: " + to_string(_bread) +
            "\nMAIN INGREDIENT: " + to_string(_ingredient) +
            (_sauce != NO_SAUCE ? "\nADD: " + to_string(_sauce) : "") +
            (_cheese ? "\nADD: Cheese" : "") +
            (_lettuce ? "\nADD: Lettuce" : "") + "\n";
}
