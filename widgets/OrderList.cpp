#include "OrderList.h"
#include <QLabel>

OrderListItem::OrderListItem(OrderList* parent): QListWidgetItem(parent), item_index(-1) {}

OrderListItem::OrderListItem(int itemIndex, OrderList* parent): QListWidgetItem(parent), item_index(itemIndex) {}

OrderListItem::OrderListItem(const QList<QString>& propertyLabels, const QList<QString>& propertyValues, int itemIndex, OrderList* parent):
QListWidgetItem(parent), item_index(itemIndex), property_labels(propertyLabels), property_values(propertyValues) {
    refreshData();
}

OrderList* OrderListItem::listWidget() const {
    return static_cast<OrderList*>(QListWidgetItem::listWidget());
}

void OrderListItem::setItemIndex(int index) {
    item_index = index > 0 ? index : -1;
}

int OrderListItem::itemIndex() const {
    return item_index;
}

void OrderListItem::refreshData() {
    QListIterator<QString> pl(property_labels);
    QListIterator<QString> pv(property_values);

    QString item_text = "Order #" + QString::number(item_index);
    while(pl.hasNext() && pv.hasNext()) {
        item_text.append("\n" + pl.next() + ": " + pv.next());
    }

    QListWidgetItem::setText(item_text);
}

QList<QString> OrderListItem::propertyLabels() const {
    return property_labels;
}

void OrderListItem::replacePropertyValues(const QList<QString>& newPropertyValues) {
    property_values = newPropertyValues;
    refreshData();
}

QList<QString> OrderListItem::propertyValues() const {
    return property_values;
}

OrderList::OrderList(QWidget* parent): QListWidget(parent) {}

void OrderList::addItem(const QList<QString>& propertyLabels, const QList<QString>& propertyValues) {
    addItem(new OrderListItem(propertyLabels, propertyValues, count()+1, this));
}

void OrderList::addItem(const QList<QString>& propertyLabels, const QList<QString>& propertyValues, int item_index) {
    addItem(new OrderListItem(propertyLabels, propertyValues, item_index, this));
}

void OrderList::addItem(OrderListItem* item) {
    QListWidget::addItem(item);
}

OrderListItem* OrderList::currentItem() const {
    return static_cast<OrderListItem*>(QListWidget::currentItem());
}

OrderListItem* OrderList::item(int row) const {
    return static_cast<OrderListItem*>(QListWidget::item(row));
}

OrderListItem* OrderList::takeItem(int row) {
    return static_cast<OrderListItem*>(QListWidget::takeItem(row));
}

QList<OrderListItem*> OrderList::selectedItems() const {
    QList<QListWidgetItem*> toCast = QListWidget::selectedItems();
    QList<OrderListItem*> toReturn;

    QListIterator<QListWidgetItem*> it(toCast);

    while(it.hasNext())
        toReturn.push_back(static_cast<OrderListItem*>(it.next()));

    return toReturn;
}
