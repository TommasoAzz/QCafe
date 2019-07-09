#include "Food.h"
using std::string;
using QCafe::Food;
using QCafe::QCafe_type;

const bool Food::HEAT = true;
const bool Food::NO_HEAT = false;

Food::Food(const string& food_name, bool needs_heating, const string& customer_name, bool take_away, double discount):
Order(food_name, customer_name, take_away, discount), _heating(needs_heating) {}

bool Food::heating() const {
    return _heating;
}

void Food::setHeating(bool h) {
    _heating = h;
}

string Food::orderDetails() const {
    return string("HEAT: ") + (_heating ? "Yes" : "No")
            + "\nVEGAN/VEGETARIAN: " + (isVegan() ? "Vegan" : (isVegetarian() ? "Vegetarian" : "No"))
            + "\nGLUTEN FREE: " + (isGlutenFree() ? "Yes": "No") + "\n";
}
