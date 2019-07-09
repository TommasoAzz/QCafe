#include "Coffee_Milk.h"
using std::string;
using QCafe::Coffee_Milk;
using QCafe::QCafe_type;

const bool Coffee_Milk::WHIPPED_CREAM = true;
const bool Coffee_Milk::NO_WHIPPED_CREAM = false;
const std::vector<string> Coffee_Milk::Coffee_Milk_List = {"Caffe Latte", "Cappuccino", "Macchiato"};

Coffee_Milk::Coffee_Milk(const string& coffee_name, cup_size cs, coffee_variety cv, sweetener_type st, bool whipped_cream, const string& customer_name, bool take_away, double discount):
Coffee(coffee_name, cs, cv, st, customer_name, take_away, discount), whipped_cream(whipped_cream) {}

bool Coffee_Milk::milkFoam() const {
    return (productName() == Coffee_Milk_List[1] || productName() == Coffee_Milk_List[2]);
}

bool Coffee_Milk::steamedMilk() const {
    return (productName() == Coffee_Milk_List[0] || productName() == Coffee_Milk_List[1] || productName() == Coffee_Milk_List[3]);
}

bool Coffee_Milk::whippedCream() const {
    return whipped_cream;
}

void Coffee_Milk::setWhippedCream(bool c) {
    whipped_cream = c;
}

double Coffee_Milk::price() const {
    double price = Coffee::price();

    if(steamedMilk()) price += 0.3;
    if(milkFoam()) price += 0.2;
    if(whipped_cream) price += 0.5;

    return price;
}

Coffee_Milk* Coffee_Milk::clone() const {
    return new Coffee_Milk(*this);
}

QCafe_type Coffee_Milk::className() const {
    return COFFEE_MILK;
}

string Coffee_Milk::orderDetails() const {
    string det = "ADD: " + string(milkFoam() ? "Milk foam " : "") + string(steamedMilk() ? "Steamed milk " : "") + string(whipped_cream ? " Whipped cream " : "");
    return Coffee::orderDetails() + det + "\n";
}

