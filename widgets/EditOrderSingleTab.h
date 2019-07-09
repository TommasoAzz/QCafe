#ifndef EDITORDERSINGLETAB_H
#define EDITORDERSINGLETAB_H

#include <QWidget>
#include <QGridLayout>
#include <QComboBox>
#include <QCheckBox>

class EditOrderSingleTab: public QWidget {
    Q_OBJECT
public:
    explicit EditOrderSingleTab(QWidget* =nullptr);
    virtual ~EditOrderSingleTab() = default;
    QGridLayout* layout;
protected:
    int firstAvailableRowInLayout() const;
};

class EditOrderBeverageTab: public EditOrderSingleTab {
    Q_OBJECT
public:
    explicit EditOrderBeverageTab(QWidget* =nullptr);
    virtual ~EditOrderBeverageTab() = default;
    QComboBox* sweetener, *cupSize;
};

class EditOrderFoodTab: public EditOrderSingleTab {
    Q_OBJECT
public:
    explicit EditOrderFoodTab(QWidget* =nullptr);
    virtual ~EditOrderFoodTab() = default;
    QCheckBox* heatProduct;
};

class EditOrderTeaTab : public EditOrderBeverageTab {
    Q_OBJECT
public:
    explicit EditOrderTeaTab(QWidget* =nullptr);
};

class EditOrderCoffeeTab: public EditOrderBeverageTab {
    Q_OBJECT
public:
    explicit EditOrderCoffeeTab(QWidget* =nullptr);
    QComboBox* variety;
    QCheckBox* whippedCream;
};

class EditOrderSweetTab: public EditOrderFoodTab {
    Q_OBJECT
public:
    explicit EditOrderSweetTab(QWidget* =nullptr);
    QComboBox* flavour;
    QCheckBox* whippedCream;
};

class EditOrderSandwichTab: public EditOrderFoodTab {
    Q_OBJECT
public:
    explicit EditOrderSandwichTab(QWidget* =nullptr);
    QComboBox* breadType, *mainIngredient, *sauce;
    QCheckBox *cheese, *lettuce;
};

#endif // EDITORDERSINGLETAB_H
