#ifndef QCAFE_BEVERAGE_H
#define QCAFE_BEVERAGE_H
#include "Order.h"

class QCafe::Beverage: public QCafe::Order {
public:
    enum cup_size: unsigned int {SMALL, MEDIUM, LARGE}; // valori per _size
    enum sweetener_type: unsigned int {NO_SWEETENER, SUGAR, SWEETENER}; // valori per _sweetener

    Beverage(const std::string&, cup_size, sweetener_type, const std::string&, bool, double=0.0);

    // metodi "get"
    sweetener_type sweetenerType() const;
    cup_size cupSize() const;

    // metodi "set"
    void setSweetenerType(sweetener_type);
    void setCupSize(cup_size);

    virtual Beverage* clone() const override = 0;

    // metodi di conversione string <-> enum
    static std::string to_string(cup_size);
    static std::string to_string(sweetener_type);
    static cup_size to_cup_size(const std::string&);
    static sweetener_type to_sweetener_type(const std::string&);
protected:
    virtual std::string orderDetails() const override;
private:
    sweetener_type _sweetener; //default: NO_SWEETENER
    cup_size _size;  //default: SMALL
};

#endif
