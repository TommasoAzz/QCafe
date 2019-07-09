#ifndef QONTAINER_H
#define QONTAINER_H

/** Struttura dati FIFO (coda) implementata come una lista singolarmente concatenata */
template<class T> class Qontainer {
private:
    /** Rappresenta un singolo elemento nel Qontainer. Contiene informazioni sull'elemento stesso e un puntatore all'elemento successivo */
    class q_item {
        friend class Qontainer;
    private:
        T info;
        q_item* next;

        q_item(const T&, q_item* =nullptr);
        ~q_item();
    };

    /** Numero di elementi presenti nel Qontainer */
    unsigned int _size;
    /** Puntatore al primo elemento del Qontainer */
    q_item* head;
    /** Puntatore all'ultimo elemento del Qontainer */
    q_item* tail;

    /** Metodo di clonazione di una lista singolarmente concatenata di q_item */
    static q_item* clone_qontainer(const q_item*, q_item*&, unsigned int&); // O(n)
public:
    class const_iterator; // dichiarazione incompleta

    /** Rappresenta un singolo elemento del Qontainer ma ha la possibilità di cambiare valore e iterare fra gli elementi (in avanti) */
    class iterator {
        friend class Qontainer;
    public:
        /** Costruttore che inizializza l'iterator a nullptr */
        iterator();
        /** Costruttore di copia (crea un iterator con lo stesso elemento puntato dall'iterator passato come parametro) */
        iterator(const iterator&);
        /** Costruttore di copia (crea un iterator con lo stesso elemento puntato dal terator passato come parametro) */

        /** Operatore di assegnazione */
        iterator& operator=(const iterator&);
        /** Operatore di incremento unitario prefisso (++iterator) */
        iterator& operator++();
        /** Operatore di incremento unitario postfisso (iterator++) */
        iterator operator++(int);
        /** Operatore di incremento di una copia dell'iteratore di un numero di elementi indicato dal parametro intero */
        iterator operator+(int) const;
        /** Operatore di incremento dell'iteratore stesso di un numero di elementi indicato dal parametro intero */
        iterator& operator+=(int);

        /** Operatore di uguaglianza booleana */
        bool operator==(const iterator&) const;
        /** Operatore di disuguaglianza booleana */
        bool operator!=(const iterator&) const;

        /** Operatore di dereferenziazione */
        T& operator*() const;
        /** "Arrow operator" corrisponde alla scrittura breve di (*it).callProperty(), ovvero it->callProperty() */
        T* operator->() const;
    private:
        /** Elemento puntato dall'iterator */
        Qontainer::q_item* item;

        /** Flag booleano rappresentante la condizione di iteratore "fuori-dai-limiti" o "past-the-end" (true) oppure normale (false) */
        bool pastTheEnd;

        /** Costruttore privato che inizializza l'iterator */
        iterator(q_item*, bool =false);
    };

    /** Rappresenta un singolo elemento costante del Qontainer ma ha la possibilità di cambiare il proprio valore e iterare fra gli elementi (in avanti) */
    class const_iterator {
        friend class Qontainer;
    public:
        /** Costruttore che inizializza il const_iterator a nullptr */
        const_iterator();
        /** Costruttore di copia (crea un const_iterator con lo stesso elemento puntato dall'iterator passato come parametro) */
        const_iterator(const const_iterator&);
        /** Costruttore di copia (crea un const_iterator con lo stesso elemento puntato dall'iterator passato come parametro) */
        const_iterator(const iterator&);

        /** Operatore di assegnazione */
        const_iterator& operator=(const const_iterator&);
        /** Operatore di incremento unitario prefisso (++const_iterator) */
        const_iterator& operator++();
        /** Operatore di incremento unitario postfisso (const_iterator++) */
        const_iterator operator++(int);
        /** Operatore di incremento di una copia del const_iterator di un numero di elementi indicato dal parametro intero */
        const_iterator operator+(int) const;
        /** Operatore di incremento del const_iterator stesso di un numero di elementi indicato dal parametro intero */
        const_iterator& operator+=(int);

        /** Operatore di uguaglianza booleana */
        bool operator==(const const_iterator&) const;
        /** Operatore di disuguaglianza booleana */
        bool operator!=(const const_iterator&) const;

        /** Operatore di dereferenziazione */
        const T& operator*() const;
        /** "Arrow operator" corrisponde alla scrittura breve di (*it).callProperty(), ovvero it->callProperty */
        const T* operator->() const;
    private:
        /** Elemento puntato dal const_iterator */
        const Qontainer::q_item* c_item;

        /** Flag booleano rappresentante la condizione di const_iterator "fuori-dai-limiti" o "past-the-end" (true) oppure normale (false) */
        bool pastTheEnd;

        /** Costruttore privato che inizializza il const_iterator */
        const_iterator(const q_item*, bool =false);
    };

    /** Costruttore del contenitore */
    Qontainer();
    /** Costruttore di copia del contenitore */
    Qontainer(const Qontainer&);
    /** Distruttore del contenitore */
    ~Qontainer();

    /** Operatore di assegnazione */
    Qontainer& operator=(const Qontainer&);

    /** Operatore di uguaglianza booleana */
    bool operator==(const Qontainer&) const;
    /** Operatore di disuguaglianza booleana */
    bool operator!=(const Qontainer&) const;

    /** Restituisce true sse il Qontainer è vuoto (0 elementi) */
    bool empty() const;
    /** Restituisce il numero di elementi presenti nel Qontainer */
    unsigned int size() const;

    /** Inserisce un nuovo elemento in fondo alla lista, infine restituisce per riferimento l'oggetto di invocazione */
    Qontainer& push(const T&);
    /** Rimuove il primo elemento presente in Qontainer */
    void pop();
    /** Svuota il Qontainer (se non lo è già) e restituisce un riferimento al Qontainer */
    Qontainer& clear();
    /** Rimuove l'elemento puntato dal const_iterator passato per parametro dal Qontainer */
    //iterator erase(const iterator&);
    iterator erase(const iterator&);
    /** Rimuove gli elementi puntati dal primo const_iterator a prima dell'ultimo, passati per parametro, dal Qontainer */
    //iterator erase(const iterator&, const iterator&);
    iterator erase(const iterator&, const iterator&);

    /** Restituisce per riferimento il primo elemento contenuto nel Qontainer */
    T& front();
    /** Restituisce per riferimento costante il primo elemento contenuto nel Qontainer */
    const T& front() const;
    /** Restituisce per riferimento l'ultimo elemento contenuto nel Qontainer */
    T& back();
    /** Restituisce per riferimento costante l'ultimo elemento contenuto nel Qontainer */
    const T& back() const;
    /** Restituisce l'iterator che punta al primo elemento del Qontainer */
    iterator begin();
    /** Restituisce l'iterator che punta al primo elemento past-the-end del Qontainer */
    iterator end();
    /** Restituisce il const_iterator che punta al primo elemento (reso costante) del Qontainer */
    const_iterator cbegin() const;
    /** Restituisce il const_iterator che punta al primo elemento past-the-end del Qontainer */
    const_iterator cend() const;

    /** Restituisce un iterator che punta all'elemento con valore uguale a quello passato per parametro (se non viene trovato, restituisce end() */
    iterator find(const T&);
    /** Restituisce un const_iterator che punta all'elemento con valore uguale a quello passato per parametro in versione costante (se non viene trovato, restituisce cend() */
    const_iterator find(const T&) const;
};

template<class T> Qontainer<T>::q_item::q_item(const T& i, q_item* qi): info(i), next(qi) {}

template<class T> Qontainer<T>::q_item::~q_item() {}

template<class T> typename Qontainer<T>::q_item* Qontainer<T>::clone_qontainer(const q_item* qi_toClone, q_item*& thisTail, unsigned int& thisSize) {
    if(!qi_toClone) return thisTail = nullptr; // nodo nullo (non contiene valori)

    ++thisSize; // incremento del numero di elementi presenti

    if(!qi_toClone->next) return thisTail = new q_item(qi_toClone->info); // qi_toClone è l'ultimo elemento

    return new q_item(qi_toClone->info, clone_qontainer(qi_toClone->next, thisTail, thisSize));
}

template<class T> Qontainer<T>::iterator::iterator(q_item* qi, bool pte): item(qi), pastTheEnd(pte) {}

template<class T> Qontainer<T>::iterator::iterator(const iterator& it): item(it.item), pastTheEnd(it.pastTheEnd) {}

template<class T> typename Qontainer<T>::iterator& Qontainer<T>::iterator::operator=(const iterator& it) {
    pastTheEnd = it.pastTheEnd;
    item = it.item;
    return *this;
}

template<class T> Qontainer<T>::iterator::iterator(): item(nullptr), pastTheEnd(false) {}

template<class T> bool Qontainer<T>::iterator::operator==(const iterator& it) const {
    return item == it.item && pastTheEnd == it.pastTheEnd;
}

template<class T> bool Qontainer<T>::iterator::operator!=(const iterator& it) const {
    return item != it.item;
}

template<class T> typename Qontainer<T>::iterator& Qontainer<T>::iterator::operator++() {
    if(item && !pastTheEnd) { //se non sono past-the-end e item punta qualcosa
        if(!item->next) {
            pastTheEnd = true; //se il suo next è nullptr allora è l'ultimo elemento della lista e segnalo che vado past-the-end
            ++item; //sposto il puntatore di sizeof(item)
        } else item = item->next; //sposto il puntatore al successivo
    }

    return *this;
}

template<class T> typename Qontainer<T>::iterator Qontainer<T>::iterator::operator++(int) {
    iterator temp = *this;

    operator++(); //chiamo operator++ prefisso (che è uguale a meno del ritorno di *this che qui non uso)

    return temp;
}

template<class T> typename Qontainer<T>::iterator Qontainer<T>::iterator::operator+(int n) const {
    if (n <= 0) return *this; // non sommo nulla

    iterator cp = *this;

    for(int i = 0; i < n; ++i) {
        ++cp;
    }

    return cp;
}

template<class T> typename Qontainer<T>::iterator& Qontainer<T>::iterator::operator+=(int n) {
    for(int i = 0; i < n; ++i) operator++(); // ++ prefisso

    return *this;
}

template<class T> T& Qontainer<T>::iterator::operator*() const {
    return item->info;
}

template<class T> T* Qontainer<T>::iterator::operator->() const {
    return &(item->info);
}

template<class T> Qontainer<T>::const_iterator::const_iterator(const q_item* cqi, bool pte): c_item(cqi), pastTheEnd(pte) {}

template<class T> Qontainer<T>::const_iterator::const_iterator(const const_iterator& cit): c_item(cit.c_item), pastTheEnd(cit.pastTheEnd) {}

template<class T>
Qontainer<T>::const_iterator::const_iterator(const iterator& it): c_item(it.item), pastTheEnd(it.pastTheEnd) {}

template<class T> typename
Qontainer<T>::const_iterator& Qontainer<T>::const_iterator::operator=(const const_iterator& cit) {
    pastTheEnd = cit.pastTheEnd;
    c_item = cit.c_item;
    return *this;
}

template<class T> Qontainer<T>::const_iterator::const_iterator(): c_item(nullptr), pastTheEnd(false) {}

template<class T> bool Qontainer<T>::const_iterator::operator==(const const_iterator& cit) const {
    return c_item == cit.c_item;
}

template<class T> bool Qontainer<T>::const_iterator::operator!=(const const_iterator& cit) const {
    return c_item != cit.c_item ;
}

template<class T> typename Qontainer<T>::const_iterator& Qontainer<T>::const_iterator::operator++() {
    if(c_item && !pastTheEnd) { //se non sono past-the-end e c_item punta qualcosa
        if(!c_item->next) {
            pastTheEnd = true; //se il suo next è nullptr allora è l'ultimo elemento della lista e segnalo che vado past-the-end
            ++c_item; //sposto il puntatore di sizeof(c_item)
        } else {
            c_item = c_item->next; //sposto il puntatore al successivo
        }
    }

    return *this;
}

template<class T> typename Qontainer<T>::const_iterator Qontainer<T>::const_iterator::operator++(int) {
    const_iterator temp = *this;

    operator++(); //chiamo operator++ prefisso (che è uguale a meno del ritorno di *this che qui non uso)

    return temp;
}

template<class T> typename Qontainer<T>::const_iterator Qontainer<T>::const_iterator::operator+(int n) const {
    if (n <= 0) return *this;

    const_iterator cp = *this;

    for(int i = 0; i < n; ++i) ++cp;

    return cp;
}

template<class T> typename Qontainer<T>::const_iterator& Qontainer<T>::const_iterator::operator+=(int n) {
    for(int i = 0; i < n; ++i) operator++();

    return *this;
}

template<class T> const T& Qontainer<T>::const_iterator::operator*() const {
    return c_item->info;
}

template<class T> const T* Qontainer<T>::const_iterator::operator->() const {
    return &(c_item->info);
}

template<class T> Qontainer<T>::Qontainer(): _size(0), head(nullptr), tail(nullptr) {}

template<class T> Qontainer<T>::Qontainer(const Qontainer& q): Qontainer() {
    head = clone_qontainer(q.head, tail, _size);
}

template<class T> Qontainer<T>::~Qontainer() {
    clear();
}

template<class T> Qontainer<T>& Qontainer<T>::operator=(const Qontainer& q) {
    if(this != &q) {
        clear();
        head = clone_qontainer(q.head, tail, _size);
    }
    return *this;
}

template<class T> bool Qontainer<T>::operator==(const Qontainer& q) const {
    if(empty() == q.empty()) return true;
    if(size() != q.size()) return false;

    const_iterator c_this = cbegin();
    const_iterator c_q = q.cbegin();

    while(c_this != cend() && c_q != q.cend() && *c_this == *c_q) {
        ++c_this;
        ++c_q;
    }

    if(c_this == cend() && c_q == q.cend()) return true;

    return false;
}

template<class T> bool Qontainer<T>::operator!=(const Qontainer& q) const {
    return !operator==(q);
}

template<class T> Qontainer<T>& Qontainer<T>::clear() {
    while(!empty()) {
        pop();
    }

    return *this;
}

template<class T> typename Qontainer<T>::iterator Qontainer<T>::erase(const iterator& it) {
    if(empty() || it == iterator() || it == end() || it == begin()) { // casi in cui posso restituire begin()
        if(it == begin() && it != end()) pop(); // se è richiesta la rimozione del primo devo prima fare il pop()
        return begin();
    }

    iterator i = begin();

    while(i+1 != it) ++i; // trovo l'elemento precedente a quello da eliminare, muovendo l'iteratore

    if(i.item->next == tail) tail = i.item; // verifico che l'elemento da eliminare non sia l'ultimo, perché in quel caso devo anche sistemare il puntatore tail
    q_item* to_delete = i.item->next; // salvo il puntatore all'elemento da eliminare
    i.item->next = (i.item->next)->next; // l'iteratore dell'elemento da eliminare ora punta al successivo elemento
    delete to_delete; // libero la memoria dell'elemento da rimuovere
    ++i; // occupo l'iteratore dell'elemento da eliminare (di cui ho copiato l'indirizzo in to_delete)
    _size--; // diminuisco il contatore degli elementi nel contenitore

    return i; // ritorno il puntatore all'elemento successivo
}

template<class T> typename Qontainer<T>::iterator Qontainer<T>::erase(const iterator& it1, const iterator& it2) {
    // eliminazione di elementi nell'intervallo [it1, it2)
    if(empty() || it1 == iterator() || it2 == iterator()) return begin();
    if(it1 == it2) return it2; // it1 da rimuovere, it2 da non rimuovere, it1 == it2 => restituisco it2
    if(it1+1 == it2) return erase(it1);

    iterator i = begin();


    if(it1 == i) {
        while(i != it2 && i != end()) {
            pop();
            i = begin();
        }
    } else {
        while((i+1) != it1) ++i;

        iterator to_delete = i + 1;
        i.item->next = it2.item; // sistemo i puntatori: collego l'ultimo elemento della parte non da rimuovere (i) con il primo da non eliminare (it2)

        if(tail+1 == it2.item) {
            // in base a come è definito end(), se it2 == end() ovvero se it2.item == tail+1 allora faccio puntare tail all'ultimo elemento da non rimuovere
            // perché sarà il prossimo ultimo elemento nel Qontainer
            tail = i.item;
            tail->next = nullptr;
        }

        q_item* item;
        while(to_delete != it2) {
            item = to_delete.item;
            ++to_delete;
            delete item;
            _size--;
        }
    }

    return it2;
}

template<class T> bool Qontainer<T>::empty() const {
    return (head == nullptr && tail == nullptr && _size == 0);
}

template<class T> unsigned int Qontainer<T>::size() const {
    return _size;
}

template<class T> T& Qontainer<T>::front() {
    return head->info;
}

template<class T> const T& Qontainer<T>::front() const {
    return head->info;
}

template<class T> T& Qontainer<T>::back() {
    return tail->info;
}

template<class T> const T& Qontainer<T>::back() const {
    return tail->info;
}

template<class T> Qontainer<T>& Qontainer<T>::push(const T& newItem) {
    if(empty()) {
        head = tail = new q_item(newItem);
    } else {
        tail->next = new q_item(newItem);
        tail = tail->next;
    }
    _size++;
    return *this;
}

template<class T> void Qontainer<T>::pop() {
    if(!empty()) {
        if(head == tail) {
            delete head;
            head = tail = nullptr;
        } else {
            q_item* front = head;
            head = head->next;
            delete front;
        }
        _size--;
    }
}

template<class T> typename Qontainer<T>::iterator Qontainer<T>::begin() {
    return iterator(head); //se head == nullptr allora iterator(head) == iterator(tail) == iterator(nullptr) == iterator()
}

template<class T> typename Qontainer<T>::iterator Qontainer<T>::end() {
    return (head) ? iterator(tail+1) : iterator();
}

template<class T> typename Qontainer<T>::const_iterator Qontainer<T>::cbegin() const {
    return const_iterator(head); //se head == nullptr const_iterator(head) == const_iterator(tail) == const_iterator(nullptr) == iterator()
}

template<class T> typename Qontainer<T>::const_iterator Qontainer<T>::cend() const {
    return (head) ? const_iterator(tail+1) : const_iterator();
}

template<class T> typename Qontainer<T>::iterator Qontainer<T>::find(const T& info) {
    iterator toRet = end();
    bool found = false;

    for(iterator it = begin(); it != end() && !found; ++it) {
        if(*it == info) {
            toRet = it;
            found = true;
        }
    }

    return toRet;
}

template<class T> typename Qontainer<T>::const_iterator Qontainer<T>::find(const T& info) const {
    const_iterator toRet = cend();
    bool found = false;

    for(const_iterator cit = cbegin(); cit != cend() && !found; ++cit) {
        if(*cit == info) {
            toRet = cit;
            found = true;
        }
    }

    return toRet;
}

#endif // QONTAINER_H
