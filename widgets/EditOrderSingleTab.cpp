#include "EditOrderSingleTab.h"
#include <QGridLayout>
#include <QLabel>

EditOrderSingleTab::EditOrderSingleTab(QWidget *parent) : QWidget(parent), layout(new QGridLayout(this)) {
    setLayout(layout);
}

int EditOrderSingleTab::firstAvailableRowInLayout() const {
    return layout->rowCount();
}

EditOrderBeverageTab::EditOrderBeverageTab(QWidget* parent): EditOrderSingleTab(parent), sweetener(new QComboBox(this)), cupSize(new QComboBox(this)) {
    QLabel* lbl_sweetener = new QLabel("Sweetener", this);
    QLabel* lbl_cupSize = new QLabel("Cup size", this);

    int row = firstAvailableRowInLayout();

    layout->addWidget(lbl_sweetener, row, 0);
    layout->addWidget(sweetener, row, 1);
    layout->addWidget(lbl_cupSize, row + 1, 0);
    layout->addWidget(cupSize, row + 1, 1);
}

EditOrderTeaTab::EditOrderTeaTab(QWidget* parent): EditOrderBeverageTab(parent) {}

EditOrderCoffeeTab::EditOrderCoffeeTab(QWidget* parent): EditOrderBeverageTab(parent), variety(new QComboBox(this)), whippedCream(new QCheckBox("Whipped cream", this)) {
    QLabel* lbl_variety = new QLabel("Variety", this);

    int row = firstAvailableRowInLayout();

    layout->addWidget(lbl_variety, row, 0);
    layout->addWidget(variety, row, 1);
    layout->addWidget(whippedCream, row + 1, 0, 1, 2);
}

EditOrderFoodTab::EditOrderFoodTab(QWidget* parent): EditOrderSingleTab(parent), heatProduct(new QCheckBox("Heat product", this)) {
    layout->addWidget(heatProduct, firstAvailableRowInLayout(), 0, 1, 2);
}

EditOrderSweetTab::EditOrderSweetTab(QWidget* parent): EditOrderFoodTab(parent), flavour(new QComboBox(this)), whippedCream(new QCheckBox("Whipped cream")) {
    QLabel* lbl_flavour = new QLabel("Flavour", this);

    int row = firstAvailableRowInLayout();

    layout->addWidget(lbl_flavour, row, 0);
    layout->addWidget(flavour, row, 1);
    layout->addWidget(whippedCream, row + 1, 0, 1, 2);
}

EditOrderSandwichTab::EditOrderSandwichTab(QWidget* parent): EditOrderFoodTab(parent),
breadType(new QComboBox(this)), mainIngredient(new QComboBox(this)), sauce(new QComboBox(this)),
cheese(new QCheckBox("Cheese", this)), lettuce(new QCheckBox("Lettuce", this)) {
    QLabel* lbl_breadType = new QLabel("Bread type", this);
    QLabel* lbl_mainIngredient = new QLabel("Main ingredient", this);
    QLabel* lbl_sauce = new QLabel("Sauce", this);

    int row = firstAvailableRowInLayout();

    layout->addWidget(lbl_breadType, row, 0);
    layout->addWidget(breadType, row, 1);
    layout->addWidget(lbl_mainIngredient, row + 1, 0);
    layout->addWidget(mainIngredient, row + 1, 1);
    layout->addWidget(lbl_sauce, row + 2, 0);
    layout->addWidget(sauce, row + 2, 1);
    layout->addWidget(cheese, row + 3, 0);
    layout->addWidget(lettuce, row + 3, 1);
}
