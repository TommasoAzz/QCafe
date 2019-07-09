#ifndef QCAFE_TEA_H
#define QCAFE_TEA_H
#include "Beverage.h"
#include <vector>

class QCafe::Tea: public QCafe::Beverage {
public:
    static const std::vector<std::string> Tea_List; // valori per Order::product

    Tea(const std::string&, cup_size, sweetener_type, const std::string&, bool, double=0.0);

    // metodi "get"
    std::string type() const;

    virtual double price() const override;

    virtual Tea* clone() const override;
    virtual QCafe_type className() const override;
protected:
    virtual std::string orderDetails() const override;
};

#endif
