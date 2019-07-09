#ifndef QCAFE_BARISTA_H
#define QCAFE_BARISTA_H

#include <list>
#include "QCafe_View.h"
#include <QTextEdit>
#include <QPushButton>
#include <QComboBox>
#include "widgets/OrdersTabPanel.h"

class QCafe_Controller; // dichiarazione incompleta

class QCafe_Barista: public QCafe_View {
    Q_OBJECT
public:
    QCafe_Barista(QCafe_Controller*, QWidget* =nullptr);
private:
    OrdersTabPanel* ordersTab; // contiene i tab (due) che visualizzano gli ordini
    QTextEdit* ordersLog; // contiene le informazioni sugli ordini aggiunti al contenitore
    QPushButton* popOrder; // rimuove il primo elemento disponibile
    QPushButton* cancelOrders; // rimuove gli elementi selezionati
    QPushButton* cancelAllOrders; // rimuove tutti gli elementi (con finestra di conferma)
    QComboBox* productNames; // menu a tendina contenente i nomi di tutti i possibili prodotti per la ricerca nel contenitore
    QComboBox* productCategories; // menu a tendina contenente tutte le possibili classi di prodotti
    QPushButton* searchButton; // pulsante di avvio ricerca

    void addOrderTabs(); // aggiunge i tab alla finestra
    void addOrdersLog(QVBoxLayout*); // aggiunge l'area di testo che visualizza gli ordini in formato testuale
    void addDeleteButtons(QGridLayout*); // aggiunge i pulsanti di rimozione degli ordini
    void addSearchArea(QGridLayout*); // aggiunge le funzionalità di ricerca

    static const QString ordersQueueLabel, searchLabel, searchBoxDefaultValue;
public slots:
    void add_entry(const std::string&, const std::list<std::string>&, const std::list<std::string>&); // aggiunge alla finestra gli OrderListItem che rappresentano ordini
    void remove_entries(int, int=-1); // rimuove dalla finestra gli OrderListItem che rappresentano gli ordini da rimuovere
    void clear_log(); // pulisce il log degli ordini se la lista di questi è diventata vuota
private slots:
    void pop_order();
    void clear_all_orders();
    void edit_queued_order(QListWidgetItem*);
    void set_search_mode();
    void setSearchButtonCheckable(int);
    void enable_disable_search_tab(int);
    void update_indexes(int, int);
    void collect_index_selected_items();
    void search_by_product_name(const QString&);
    void search_by_product_category(const QString&);
};

#endif // QCAFE_BARISTA_H
