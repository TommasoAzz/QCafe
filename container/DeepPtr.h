#ifndef DEEPPTR_H
#define DEEPPTR_H
#include <iostream>

/** Smart pointer per un tipo T puntatore */
template<class T> class DeepPtr {
public:
    /** Costruisce uno smart pointer al puntatore di tipo T */
    DeepPtr(T*);
    /** Costruttore di copia di uno smart pointer*/
    DeepPtr(const DeepPtr&);
    /** Distrugge lo smart pointer e il suo elemento */
    ~DeepPtr();

    /** Operatore di assegnazione */
    DeepPtr& operator=(const DeepPtr&);
    /** Operatore di dereferenziazione */
    T& operator*() const;
    /** "Arrow operator" corrisponde alla scrittura breve di (*dp).callProperty(), ovvero dp->callProperty() */
    T* operator->() const;
private:
    /** Elemento puntato e gestito dallo smart pointer */
    T* ptr;
};

/* IMPLEMENTATION */
template<class T> DeepPtr<T>::DeepPtr(T* p): ptr(p) {}

template<class T> DeepPtr<T>::DeepPtr(const DeepPtr& dp): ptr(dp.ptr ? dp.ptr->clone() : nullptr) {}

template<class T> DeepPtr<T>::~DeepPtr() {
    if(ptr) delete ptr;
}

template<class T> DeepPtr<T>& DeepPtr<T>::operator=(const DeepPtr& dp) {
    if(this != &dp) {
        if(ptr) delete ptr;
        ptr = (dp.ptr ? dp.ptr->clone() : nullptr);
    }
    return *this;
}

template<class T> T& DeepPtr<T>::operator*() const {
    return *ptr;
}

template<class T> T* DeepPtr<T>::operator->() const {
    return ptr;
}

#endif // DEEPPTR_H
