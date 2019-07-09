#ifndef ORDERSTABPANEL_H
#define ORDERSTABPANEL_H

#include <QTabWidget>
#include <QVBoxLayout>
#include <QMap>
#include "widgets/OrderList.h"

class OrdersTabPanel : public QTabWidget {
    Q_OBJECT
public:
    explicit OrdersTabPanel(QWidget* =nullptr);
    void addSingleTab(OrderList*, const QString&);
    OrderList* tab(const QString&) const;
private:
    QMap<QString, OrderList*> tabs;
};

#endif // ORDERSTABPANEL_H
