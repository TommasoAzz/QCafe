#ifndef EDITQUEUEDORDERDIALOG_H
#define EDITQUEUEDORDERDIALOG_H

#include <QDialog>
#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>

class EditQueuedOrderDialog : public QDialog {
    Q_OBJECT
public:
    enum order_type: unsigned int {BEVERAGE, FOOD}; // meglio di un bool, magari si vuole espandere la gerarchia
    explicit EditQueuedOrderDialog(order_type, const QString&, QWidget* =nullptr);
    QList<QVariant> execAndReturnValues();
    void setQueuedOrderEditableSettings(const QList<QString>&);
private:
    QCheckBox* take_away, *heating;
    QComboBox* sweetener;
    QPushButton* confirm, *cancel;
};

#endif // EDITQUEUEDORDERDIALOG_H
