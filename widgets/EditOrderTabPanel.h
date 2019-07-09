#ifndef EDITORDERTABPANEL_H
#define EDITORDERTABPANEL_H

#include <QTabWidget>
#include <QMap>
#include "EditOrderSingleTab.h"

class EditOrderTabPanel : public QTabWidget {
    Q_OBJECT
private:
    QMap<QString, EditOrderSingleTab*> tabs;
public:
    explicit EditOrderTabPanel(QWidget* =nullptr);
    void addSingleTab(EditOrderSingleTab*, const QString&);
    EditOrderSingleTab* tab(const QString&) const;
};

#endif // EDITORDERTABPANEL_H
