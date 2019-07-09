#include "EditOrderTabPanel.h"

EditOrderTabPanel::EditOrderTabPanel(QWidget* parent): QTabWidget(parent) {}

void EditOrderTabPanel::addSingleTab(EditOrderSingleTab* newTab, const QString& tabName) {
    tabs.insert(tabName, newTab);
    addTab(newTab, tabName);
}

EditOrderSingleTab* EditOrderTabPanel::tab(const QString& tabName) const {
    if(tabs.find(tabName) == tabs.end()) return nullptr;

    return tabs[tabName];
}
