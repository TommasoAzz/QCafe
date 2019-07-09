#ifndef QCAFE_ORDER_H
#define QCAFE_ORDER_H
#include "QCafe.h"
#include <iostream>
#include <string>

class QCafe::Order {
public:
    static const bool TAKE_AWAY; // valore per take_away
    static const bool TAKE_HERE; // valore per take_away

    Order(const std::string&, const std::string&, bool, double=0.0);
    virtual ~Order() = default;

    // metodi "get"
    bool takeAway() const;
    double discountAmount() const;
    std::string productName() const;
    std::string customerName() const;
    double discountedPrice() const;

    // metodi "set"
    void setTakeAway(bool);
    void setDiscountAmount(double);
    void setProductName(const std::string&);
    void setCustomerName(const std::string&);

    std::string printOrder() const;
    virtual double price() const = 0; // il prezzo viene calcolato in base agli ingredienti e al tipo di prodotto dell'ordine

    virtual Order* clone() const = 0;
    virtual QCafe_type className() const = 0;
protected:
    virtual std::string orderDetails() const = 0;
private:
    bool take_away;
    double discount_percentage;
    std::string _product;
    std::string _customer;
};

std::ostream& operator<<(std::ostream&, const QCafe::Order&);

#endif
