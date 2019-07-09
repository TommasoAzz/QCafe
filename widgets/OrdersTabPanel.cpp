#include "OrdersTabPanel.h"

OrdersTabPanel::OrdersTabPanel(QWidget *parent) : QTabWidget(parent) {}

void OrdersTabPanel::addSingleTab(OrderList* newTab, const QString& tabName) {
    tabs.insert(tabName, newTab);
    addTab(newTab, tabName);
}

OrderList* OrdersTabPanel::tab(const QString& tabName) const {
    if(tabs.find(tabName) == tabs.end()) return nullptr;

    return tabs[tabName];
}
