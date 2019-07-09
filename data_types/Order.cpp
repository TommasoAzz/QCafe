#include "Order.h"
using std::string;
using std::ostream;
using QCafe::Order;
using QCafe::QCafe_type;

const bool Order::TAKE_AWAY = true;
const bool Order::TAKE_HERE = false;
    
Order::Order(const string& product_name, const string& customer_name, bool take_away, double discount):
take_away(take_away), discount_percentage(discount), _product(product_name), _customer(customer_name) {
}

bool Order::takeAway() const {
    return take_away;
}

double Order::discountAmount() const {
    return discount_percentage;
}

string Order::productName() const {
    return _product;
}

string Order::customerName() const {
    return _customer;
}

void Order::setTakeAway(bool ta) {
    take_away = ta;
}

void Order::setDiscountAmount(double da) {
    discount_percentage = da;
}

void Order::setProductName(const string& pn) {
    _product = pn;
}

void Order::setCustomerName(const string& cn) {
    _customer = cn;
}

string Order::printOrder() const {
    return "CUSTOMER: " + _customer
            + "\nPRODUCT: " + _product
            + "\n" + orderDetails()
            + (take_away ? "Take away" : "In place")
            + "\nPRICE: " + std::to_string((discount_percentage > 0.0 ? discountedPrice() : price()));
}

double Order::discountedPrice() const {
    return price() * (1-discount_percentage/100);
}

ostream& operator<<(ostream& stream, const Order& o) {
    // &o != nullptr
    return stream <<  o.printOrder();
}
