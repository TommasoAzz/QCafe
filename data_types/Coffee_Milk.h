#ifndef QCAFE_COFFEEMILK_H
#define QCAFE_COFFEEMILK_H
#include "Coffee.h"

class QCafe::Coffee_Milk: public QCafe::Coffee {
public:
    static const bool WHIPPED_CREAM; // valori per whipped_cream
    static const bool NO_WHIPPED_CREAM; // valori per whipped_cream
    static const std::vector<std::string> Coffee_Milk_List; // valori per Order::product

    Coffee_Milk(const std::string&, cup_size, coffee_variety, sweetener_type, bool, const std::string&, bool, double=0.0);

    // metodi "get"
    bool milkFoam() const;
    bool steamedMilk() const;
    bool whippedCream() const;
    void setWhippedCream(bool);

    virtual double price() const override;

    virtual Coffee_Milk* clone() const override;
    virtual QCafe_type className() const override;
protected:
    virtual std::string orderDetails() const override;
private:
    bool whipped_cream; // richiesto all'utente

    void setMilkProperties(); // se viene cambiato il nome del prodotto mediante setProductName() devono potenzialmente cambiare anche i tre campi dati della classe
};

#endif
