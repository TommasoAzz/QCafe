#ifndef ORDERLIST_H
#define ORDERLIST_H

#include <QListWidget>

class OrderList;

class OrderListItem: public QListWidgetItem {
public:
    explicit OrderListItem(OrderList* =nullptr);
    OrderListItem(int, OrderList* =nullptr);
    OrderListItem(const QList<QString>&, const QList<QString>&, int, OrderList* =nullptr);

    OrderList* listWidget() const;

    // relativi ai dati dell'ordine
    void setItemIndex(int);
    int itemIndex() const;
    void refreshData();
    QList<QString> propertyLabels() const;
    void replacePropertyValues(const QList<QString>&);
    QList<QString> propertyValues() const;
private:
    int item_index;
    QList<QString> property_labels, property_values;
};

class OrderList : public QListWidget {
    Q_OBJECT
public:
    explicit OrderList(QWidget* = nullptr);
    void addItem(OrderListItem*);
    void addItem(const QList<QString>&, const QList<QString>&);
    void addItem(const QList<QString>&, const QList<QString>&, int);
    OrderListItem* currentItem() const;
    OrderListItem* item(int) const;
    OrderListItem* takeItem(int);
    QList<OrderListItem*> selectedItems() const;
};

#endif // ORDERLIST_H
