#ifndef QCAFE_CASHIER_H
#define QCAFE_CASHIER_H

#include "QCafe_View.h"
#include "QCafe_Model.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>
#include "widgets/MainMenu.h"
#include "widgets/EditOrder.h"
class QCafe_Controller;

class QCafe_Cashier: public QCafe_View {
    Q_OBJECT
public:
    enum ComboBoxName: unsigned int { CB_SWEETENER, CB_CUP_SIZE, CB_VARIETY, CB_FLAVOUR, CB_BREAD_TYPE, CB_MAIN_INGREDIENT, CB_SAUCE };
    QCafe_Cashier(QCafe_Controller*, QWidget* =nullptr);
    ~QCafe_Cashier();
private:
    QCafe_Model* model; // modello che gestisce i dati dell'applicazione

    QListWidget* quickOrderPanel; // pannello con la lista dei prodotti base selezionabili
    EditOrder* editOrder; // pannello con le componenti per modificare i prodotti base
    QLabel* orderPreviewImage; // area di testo in cui viene visualizzato sottoforma di testo il riepilogo dell'ordine
    QLineEdit* discount; // campo di testo in cui inserire il valore dello sconto (se presente, altrimenti di default è 0.0)
    QPushButton* confirm, *cancel; // pulsanti di conferma di aggiunta di un ordine al contenitore e reset dell'ordine
    QVBoxLayout* mainCashierLayout; // layout principale della vista Cashier

    void addQuickOrderPanel(QHBoxLayout*);
    void addEditOrderPanel(QHBoxLayout*);
    void addOrderImagePanel(QVBoxLayout*);
    void addDiscountPanel(QVBoxLayout*);
    void addConfirmationPanel(QVBoxLayout*);
    void setOrderPreviewImage(const QString&);

    void setProductList(const std::list<std::string>&);
    void setComboBoxValues(ComboBoxName, const std::list<std::string>&);
    QString imageFileName(const QString&) const;

    static const QString editOrderCoffeeLabel, editOrderTeaLabel, editOrderSweetLabel, editOrderSandwichLabel;
private slots:
    void push_order();
    void remove_last_order();
    void select_item(QListWidgetItem*, QListWidgetItem*); // in base alla selezione dell'item in quickOrderPanel cambia il pannello selezionato in editOrder
    void switch_tab(const QString& previous_tab, const QString& current_tab); // cambia il pannello selezionato in editOrder
};

#endif // QCAFE_CASHIER_H
