#ifndef QCAFE_SWEET_H
#define QCAFE_SWEET_H
#include "Food.h"
#include <vector>

class QCafe::Sweet: public QCafe::Food {
public:
    static const bool WHIPPED_CREAM, NO_WHIPPED_CREAM; // valori per whipped_cream
    enum flavour: unsigned int {PLAIN, CHOCOLATE, APPLE_AND_CINNAMON}; // valori per _flavour
    static const std::vector<std::string> Sweet_List; // valori per Order::product

    Sweet(const std::string&, bool, enum flavour, bool, const std::string&, bool, double=0.0);

    // metodi "get"
    bool whippedCream() const;
    flavour flavouring() const;

    // metodi "set"
    void setWhippedCream(bool);
    void setFlavour(enum flavour);

    virtual bool isVegan() const override;
    virtual bool isVegetarian() const override;
    virtual bool isGlutenFree() const override;
    virtual double price() const override;

    virtual Sweet* clone() const override;
    virtual QCafe_type className() const override;

    // metodi di conversione string <-> enum
    static std::string to_string(flavour);
    static flavour to_flavour(const std::string&);
protected:
    virtual std::string orderDetails() const override;
private:
    bool whipped_cream;
    flavour _flavour; // default: PLAIN
};

#endif
