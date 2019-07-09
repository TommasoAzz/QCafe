#ifndef QCAFE_QCAFE_H
#define QCAFE_QCAFE_H

namespace QCafe {
    // dichiarazioni incomplete delle classi della gerarchia
    class Order;
    class Beverage;
    class Tea;
    class Coffee;
    class Coffee_Milk;
    class Food;
    class Sweet;
    class Sandwich;
    // tipi degli oggetti istanziabili
    enum QCafe_type: unsigned int {TEA, COFFEE, COFFEE_MILK, SWEET, SANDWICH };
}

#endif
