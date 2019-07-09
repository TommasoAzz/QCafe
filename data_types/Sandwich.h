#ifndef QCAFE_SANDWICH_H
#define QCAFE_SANDWICH_H
#include "Food.h"
#include <vector>

class QCafe::Sandwich: public QCafe::Food {
public:
    enum bread_type: unsigned int {WHITE, WHOLE_GRAIN, GLUTEN_FREE}; // valori per _bread
    enum main_ingredient: unsigned int {HAM, BEEF, CHICKEN, SEITAN, AUBERGINES}; // valori per _ingredient
    enum sauce_type: unsigned int {KETCHUP, MAYONNAISE, MUSTARD, NO_SAUCE}; // valori per _sauce
    static const bool CHEESE, NO_CHEESE, LETTUCE, NO_LETTUCE; // valori per _cheese, _lettuce
    static const std::vector<std::string> Sandwich_List; // valori per Order::product

    Sandwich(bread_type, main_ingredient, sauce_type, bool, bool, bool, const std::string&, bool, double=0.0);

    // metodi "get"
    bread_type bread() const;
    main_ingredient mainIngredient() const;
    sauce_type sauce() const;
    bool cheese() const;
    bool lettuce() const;

    // metodi "set"
    void setBread(bread_type);
    void setMainIngredient(main_ingredient);
    void setSauce(sauce_type);
    void setCheese(bool);
    void setLettuce(bool);

    virtual bool isVegan() const override;
    virtual bool isVegetarian() const override;
    virtual bool isGlutenFree() const override;
    virtual double price() const override;

    virtual Sandwich* clone() const override;
    virtual QCafe_type className() const override;

    // metodi di conversione string <-> enum
    static std::string to_string(bread_type);
    static std::string to_string(main_ingredient);
    static std::string to_string(sauce_type);
    static bread_type to_bread_type(const std::string&);
    static main_ingredient to_main_ingredient(const std::string&);
    static sauce_type to_sauce_type(const std::string&);
protected:
    virtual std::string orderDetails() const override;
private:
    bread_type _bread; // default: WHITE
    main_ingredient _ingredient; // default: HAM
    sauce_type _sauce; // default: NONE
    bool _cheese;
    bool _lettuce;
};

#endif
