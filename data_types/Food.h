#ifndef QCAFE_FOOD_H
#define QCAFE_FOOD_H
#include "Order.h"

class QCafe::Food: public QCafe::Order {
public:
    static const bool HEAT; // valore per _heating
    static const bool NO_HEAT; // valore per _heating

    Food(const std::string&, bool, const std::string&, bool, double=0.0);

    // metodi "get"
    bool heating() const;

    // metodi "set"
    void setHeating(bool);

    virtual bool isVegan() const = 0;
    virtual bool isVegetarian() const = 0;
    virtual bool isGlutenFree() const = 0;

    virtual Food* clone() const override = 0;
protected:
    virtual std::string orderDetails() const override;
private:
    bool _heating;
};

#endif
