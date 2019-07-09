#ifndef QCAFE_COFFEE_H
#define QCAFE_COFFEE_H
#include "Beverage.h"
#include <vector>

class QCafe::Coffee: public QCafe::Beverage {
public:
    enum coffee_variety: unsigned int {ARABICA, ROBUSTA}; // valori per _variety
    static const std::vector<std::string> Coffee_List; // valori per Order::product

    Coffee(const std::string&, cup_size, coffee_variety, sweetener_type, const std::string&, bool, double=0.0);

    // metodi "get"
    coffee_variety variety() const;
    std::string grinding() const;
    std::string brewingDevice() const;

    // metodi "set"
    void setVariety(coffee_variety);

    virtual double price() const override;

    virtual Coffee* clone() const override;
    virtual QCafe_type className() const override;

    // metodi di conversione string <-> enum
    static std::string to_string(coffee_variety);
    static coffee_variety to_coffee_variety(const std::string&);
protected:
    virtual std::string orderDetails() const override;
private:
    coffee_variety _variety; //default: ARABICA
};

#endif
