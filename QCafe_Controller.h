#ifndef QCAFE_CONTROLLER_H
#define QCAFE_CONTROLLER_H

#include <map>
#include "QCafe_Model.h"
#include "QCafe_Barista.h"
#include "QCafe_Cashier.h"
#include "XMLFileIO.h"

class QCafe_Controller {
public:
    QCafe_Controller(QCafe_Model*);
    ~QCafe_Controller();
    // INTERAZIONE CONTROLLER-MODELLO
    // ATTENZIONE: i seguenti metodi "pushOrder" ricalcano i costruttori dei tipi della gerarchia in modo da non accedere direttamente al modello da parte della view (omessi Order, Beverage, Food perché non istanziabili)
    void pushOrder(const std::string& coffee_name, const std::string& cup_size, const std::string& coffee_variety, const std::string& sweetener_type, const std::string& customer_name, bool take_away, double discount=0.0) const; // Coffee
    void pushOrder(const std::string& coffee_name, const std::string& cup_size, const std::string& coffee_variety, const std::string& sweetener_type, bool whipped_cream, const std::string& customer_name, bool take_away, double discount=0.0) const; // Coffee_Milk
    void pushOrder(const std::string& tea_name, const std::string& cup_size, const std::string& sweetener_type, const std::string& customer_name, bool take_away, double discount=0.0) const; // Tea
    void pushOrder(const std::string& bread_type, const std::string& main_ingredient, const std::string& sauce, bool cheese, bool lettuce, bool needs_heating, const std::string& customer_name, bool take_away, double discount=0.0) const; // Sandwich
    void pushOrder(const std::string& sweet_name, bool whipped_cream, const std::string& chosen_flavour, bool needs_heating, const std::string& customer_name, bool take_away, double discount=0.0) const; // Sweet
    void popOrder() const; // rimuove il primo ordine
    void clearAllOrders() const; // rimuove tutti gli ordini
    void openLog(const std::string&) const; // apre un file di log xml
    void saveLog(const std::string&) const; // salva il contenuto del modello in xml
    static std::string logFileExtension();

    // INTERAZIONE CONTROLLER - MAIN
    void showView() const; // mostra le finestre Cashier e Barista

    // INTERAZIONE CONTROLLER-VISTA (CASHIER)
    std::string productType(const std::string&) const; // ritorna il nome della classe di cui fa parte il prodotto passato per parametro
    std::list<std::string> productList() const; // restituisce la lista dei prodotti base, presi dalle classi della gerarchia del modello
    static std::map< QCafe_Cashier::ComboBoxName, std::list<std::string> > editOrderSettings(); // popola i widget di cashier con i dati del modello
    int numberOfOrders() const; // numero di ordini presenti nel modello

    // INTERAZIONE CONTROLLER-VISTA (BARISTA)
    struct orderInfo { // struttura per la restituzione dei dati per la ricerca e per la modifica
        int orderNumber; // numero dell'ordine nel container
        std::list<std::string> productLabels; // etichette (nomi dei campi dati) (dipendono dal tipo dell'ordine)
        std::list<std::string> productValues; // valori dei campi dati dell'ordine (dipendono dalle scelte dell'utente)
    };
    std::list<orderInfo> findByProductName(const std::string&) const; // ricerca di ordini con il nome del prodotto passato per parametro
    std::list<orderInfo> findByProductCategory(const std::string&) const; // ricerca di ordini del tipo del prodotto passato per parametro (il tipo corrisponde al nome della classe)
    static std::list<std::string> editQueuedOrderSettings(); // popola i widget del dialog di barista per la modifica di un ordine con i dati del modello
    orderInfo editOrderAt(int, bool, bool); // permette la modifica di ordini di classi derivate da Food
    orderInfo editOrderAt(int, bool, const std::string&); // permette la modifica di ordini di classi derivate da Beverage
    void removeOrders(int, int=-1) const; // permette la rimozione di elementi dal modello e dalla vista
private:
    QCafe_Model* model;
    QCafe_Barista* barista;
    QCafe_Cashier* cashier;
    XMLFileIO* fileIO;

    // INTERAZIONE CONTROLLER-VISTA (BARISTA)
    void insertOrder(const std::string&, const std::list<std::string>&, const std::list<std::string>&) const; // inserisce un ordine all'interno della vista
    static std::list<std::string> orderLabels(const QCafe::Order*); // dato un ordine, restituisce i nomi dei campi dati della classe e dei suoi super tipi
    static std::list<std::string> orderValues(const QCafe::Order*); // dato un ordine, restituisce i valori dei campi dati della classe e dei suoi super tipi (segue l'ordine di orderLabels)
    std::list<orderInfo> prepareFind(const Qontainer<QCafe::Order*>&) const; // converte i dati ottenuti dalla ricerca mediante il modello in dati comprensibili dalla vista
};

#endif // QCAFE_CONTROLLER_H
