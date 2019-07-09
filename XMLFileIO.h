#ifndef XMLFILEIO_H
#define XMLFILEIO_H

#include "container/Qontainer.h"
#include "container/DeepPtr.h"
#include "data_types/Order.h"
#include <QXmlStreamAttributes>
#include <QString>

class XMLFileIO {
public:
    XMLFileIO(const std::string& ="");
    Qontainer< DeepPtr<QCafe::Order> > readFromFile() const; // legge da file xml ordini da inserire nel container
    void writeOnFile(const Qontainer< DeepPtr<QCafe::Order> >&) const; // scrive su file xml il contenuto del container passato per parametro
    std::string filename() const; // restituisce il nome del file su cui si scrive / legge
    void setFileName(const std::string&); // imposta il nome del file su cui si scrive legge
private:
    QString file_name;
    static QString getTagName(QCafe::QCafe_type); // restituisce una stringa corrispondente al tipo dell'oggetto
    static std::string attributeToStdString(const QXmlStreamAttributes&, const QString&); // converte un attributo di un elemento xml da QString a STL string
};

#endif // XMLFILEIO_H
