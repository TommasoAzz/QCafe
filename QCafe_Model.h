#ifndef QCAFE_MODEL_H
#define QCAFE_MODEL_H
#include "container/Qontainer.h"
#include "container/DeepPtr.h"
#include "data_types/Coffee_Milk.h"
#include "data_types/Tea.h"
#include "data_types/Sandwich.h"
#include "data_types/Sweet.h"
#include <vector>

class QCafe_Model {
public:
    QCafe_Model();

    Qontainer< DeepPtr<QCafe::Order> > getOrders() const; // restituisce gli ordini presenti nel contenitore

    void pushOrder(QCafe::Order*); // inserisce un ordine nel contenitore - O(1)
    void popOrder(); // estrae il primo ordine presente nel contenitore - O(1)
    void clearAllOrders(); // rimuove tutti gli ordini presenti nel contenitore - O(n), n = orders.size()
    Qontainer< DeepPtr<QCafe::Order> >::iterator removeItem(Qontainer< DeepPtr<QCafe::Order> >::iterator it); // rimuove un elemento in posizione casuale - O(n)
    Qontainer< DeepPtr<QCafe::Order> >::iterator removeItems(Qontainer< DeepPtr<QCafe::Order> >::iterator it1, Qontainer< DeepPtr<QCafe::Order> >::iterator it2); // rimuove elementi contigui in posizione casuale - O(n)

    Qontainer< DeepPtr<QCafe::Order> >::iterator firstItem(); // restituisce un iteratore al primo elemento - O(1)
    Qontainer< DeepPtr<QCafe::Order> >::iterator lastItem(); // restituisce un iteratore all'ultimo elemento - O(n)
    Qontainer< DeepPtr<QCafe::Order> >::iterator pastTheEnd(); // restituisce un iteratore appena dopo l'ultimo elemento - O(1)

    int numberOfOrders() const; // restituisce il numero degli elementi nel contenitore

    // restituisco Qontainer<QCafe::Order*> perché voglio che gli elementi restituiti siano li stessi di quelli presenti nel container
    Qontainer<QCafe::Order*> findByProductName(const std::string&) const; // ricerca di elementi nel contenitore per nome del prodotto
    Qontainer<QCafe::Order*> findByCategory(QCafe::QCafe_type) const; // ricerca di elementi nel contenitore per tipo

    // puntatori ai vettori contenenti i prodotti inseribili come ordini nel modello
    const std::vector<std::string>* Coffee_List;
    const std::vector<std::string>* Coffee_Milk_List;
    const std::vector<std::string>* Tea_List;
    const std::vector<std::string>* Sweet_List;
    const std::vector<std::string>* Sandwich_List;
private:
    Qontainer< DeepPtr<QCafe::Order> > orders; // contenitore
};

#endif // QCAFE_H
