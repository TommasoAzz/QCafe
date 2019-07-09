#include "XMLFileIO.h"
#include "data_types/Coffee_Milk.h"
#include "data_types/Tea.h"
#include "data_types/Sandwich.h"
#include "data_types/Sweet.h"
#include "FileException.h"
#include <QFile>
#include <QSaveFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QMessageBox>

using QCafe::Order;
using QCafe::Food;
using QCafe::Beverage;
using QCafe::Coffee;
using QCafe::Coffee_Milk;
using QCafe::Tea;
using QCafe::Sandwich;
using QCafe::Sweet;
using QCafe::QCafe_type;
using std::string;

XMLFileIO::XMLFileIO(const string& path): file_name(QString::fromStdString(path)) {}

QString XMLFileIO::getTagName(QCafe_type class_name) {
    QString tag;
    switch(class_name) {
        /*
    case QCafe::ORDER:
        tag = "order"; // <order>
        break;
    case QCafe::BEVERAGE:
        tag = "beverage"; // <beverage>
        break;
    case QCafe::FOOD:
        tag = "food"; // <food>
        break;
        */
    case QCafe::COFFEE:
        tag = "coffee"; // <coffee>
        break;
    case QCafe::COFFEE_MILK:
        tag = "coffee_milk"; // <coffee_milk>
        break;
    case QCafe::TEA:
        tag = "tea"; // <tea>
        break;
    case QCafe::SWEET:
        tag = "sweet"; // <sweet>
        break;
    case QCafe::SANDWICH:
        tag = "sandwich"; // <sandwich>
        break;
    }
    return tag;
}

string XMLFileIO::attributeToStdString(const QXmlStreamAttributes& xsa, const QString& a) {
    return xsa.hasAttribute(a) ? xsa.value(a).toString().toStdString() : "";
}

Qontainer< DeepPtr<Order> > XMLFileIO::readFromFile() const {
    // lista contenente i dati letti da file
    Qontainer< DeepPtr<Order> > list;

    if(file_name == "") return list;// il nome del file è vuoto (possibilmente dovuto al chiamante) quindi non va fatto nulla

    // apertura del file di input
    QFile file(file_name);
    if(!file.open(QIODevice::ReadOnly)) {
        throw FileException(FileException::INPUT, "There was an error opening the requested file in read mode.");
    }

    QXmlStreamReader reader(&file);

    if(reader.readNextStartElement()) {
        if(reader.name() == "root") {
            while(reader.readNextStartElement()) {
                // PARSING Attributi di Order
                string product_name = attributeToStdString(reader.attributes(), "product-name");
                string customer_name = attributeToStdString(reader.attributes(), "customer-name");
                bool ta = reader.attributes().hasAttribute("take-away");
                double discount = reader.attributes().hasAttribute("discount-amount") ? reader.attributes().value("discount-amount").toDouble() : 0.0;
                // FINE PARSING Attributi di Order

                if(reader.name() == getTagName(QCafe::TEA) || reader.name() == getTagName(QCafe::COFFEE) || reader.name() == getTagName(QCafe::COFFEE_MILK)) {
                    // PARSING Attributi di Beverage
                    Beverage::cup_size cs = Beverage::to_cup_size(attributeToStdString(reader.attributes(), "size"));
                    Beverage::sweetener_type st = Beverage::to_sweetener_type(attributeToStdString(reader.attributes(), "sweetener-type"));
                    // FINE PARSING Attributi di Beverage

                    if(reader.name() == getTagName(QCafe::TEA)) {
                        // PARSING Attributi di Tea: non ce ne sono
                        list.push(new Tea(product_name, cs, st, customer_name, ta, discount));
                    } else if(reader.name() == getTagName(QCafe::COFFEE) || reader.name() == getTagName(QCafe::COFFEE_MILK)) {
                        // PARSING Attributi di Coffee
                        Coffee::coffee_variety cv = Coffee::to_coffee_variety(attributeToStdString(reader.attributes(), "variety"));
                        // FINE PARSING Attributi di Coffee

                        if(reader.name() == getTagName(QCafe::COFFEE)) {
                            list.push(new Coffee(product_name, cs, cv, st, customer_name, ta, discount));
                        } else if(reader.name() == getTagName(QCafe::COFFEE_MILK)) {
                            // PARSING Attributi di Coffee_Milk
                            bool whipped_cream = reader.attributes().hasAttribute("whipped-cream");
                            // FINE PARSING Attributi di Coffee_Milk
                            list.push(new Coffee_Milk(product_name, cs, cv, st, whipped_cream, customer_name, ta, discount));
                        }
                    }
                } else if(reader.name() == getTagName(QCafe::SWEET) || reader.name() == getTagName(QCafe::SANDWICH)) {
                    // PARSING Attributi di Food
                    bool heating = reader.attributes().hasAttribute("heat-product");
                    // FINE PARSING Attributi di Food

                    if(reader.name() == getTagName(QCafe::SWEET)) {
                        // PARSING Attributi di Sweet
                        bool whipped_cream = reader.attributes().hasAttribute("whipped-cream");
                        Sweet::flavour f = Sweet::to_flavour(attributeToStdString(reader.attributes(), "flavour"));
                        // FINE PARSING Attributi di Sweet
                        list.push(new Sweet(product_name, whipped_cream, f, heating, customer_name, ta, discount));
                    } else if(reader.name() == getTagName(QCafe::SANDWICH)) {
                        // PARSING Attributi di Sandwich
                        bool cheese = reader.attributes().hasAttribute("cheese");
                        bool lettuce = reader.attributes().hasAttribute("lettuce");
                        Sandwich::bread_type b = Sandwich::to_bread_type(attributeToStdString(reader.attributes(), "bread"));
                        Sandwich::sauce_type s = Sandwich::to_sauce_type(attributeToStdString(reader.attributes(), "sauce"));
                        Sandwich::main_ingredient mi = Sandwich::to_main_ingredient(attributeToStdString(reader.attributes(), "main-ingredient"));
                        // FINE PARSING Attributi di Sandwich
                        list.push(new Sandwich(b, mi, s, cheese, lettuce, heating, customer_name, ta, discount));
                    }
                }/* else {
                    reader.skipCurrentElement();
                }*/
                reader.readNext(); // legge la fine dell'elemento
            }
        } else {
            reader.skipCurrentElement();
        }
    }

    file.close();
    return list;
}

void XMLFileIO::writeOnFile(const Qontainer< DeepPtr<Order> >& orders) const {
    if(file_name == "") return; // il nome del file è vuoto (possibilmente dovuto al chiamante) quindi non va fatto nulla

    if(orders.empty()) {
        QMessageBox::warning(
            Q_NULLPTR,
            "Zero available orders",
            "<p>There are <strong>0 available orders</strong>. A save file will not be created.</p>"
        );
        return;
    }

    QSaveFile file(file_name);

    if(!file.open(QIODevice::WriteOnly)) {
        throw FileException(FileException::OUTPUT, "There was an error opening the file in write mode.");
    }

    QXmlStreamWriter writer(&file);

    writer.setAutoFormatting(true); // per una buona leggibilità del file XML
    writer.writeStartDocument(); //scrive l'intestazione del file XML
    writer.writeComment("QCafe save file. Do not modify this file's content.");

    writer.writeStartElement("root"); // <root>

    for(auto it = orders.cbegin(); it != orders.cend(); ++it) {
        QCafe_type class_name = (*it)->className();
        writer.writeStartElement(getTagName(class_name));

        writer.writeAttribute("product-name", QString::fromStdString((*it)->productName()));
        writer.writeAttribute("customer-name", QString::fromStdString((*it)->customerName()));
        writer.writeAttribute("price", QString::number((*it)->price()));
        if((*it)->discountAmount() > 0.0) writer.writeAttribute("discount-amount", QString::number((*it)->discountAmount()));
        if((*it)->takeAway()) writer.writeAttribute("take-away", "1");

        if(class_name == QCafe::TEA || class_name == QCafe::COFFEE || class_name == QCafe::COFFEE_MILK) {
            const Beverage* b = static_cast<const Beverage*>(&(*(*it))); // it = const_iterator, *it = const DeepPtr<Order>&, *(*it) = const Order, &(*(*it)) = const Order*
            writer.writeAttribute("size", QString::fromStdString(Beverage::to_string(b->cupSize())));
            writer.writeAttribute("sweetener-type", QString::fromStdString(Beverage::to_string(b->sweetenerType())));

            if(class_name == QCafe::COFFEE || class_name == QCafe::COFFEE_MILK) {
                const Coffee* c = static_cast<const Coffee*>(b);
                writer.writeAttribute("variety", QString::fromStdString(Coffee::to_string(c->variety())));

                if(class_name == QCafe::COFFEE_MILK) {
                    const Coffee_Milk* cm = static_cast<const Coffee_Milk*>(c);
                    if(cm->whippedCream()) writer.writeAttribute("whipped-cream", "1");
                }
            }
        } else if(class_name == QCafe::SANDWICH || class_name == QCafe::SWEET) { // FOOD
            const Food* f = static_cast<const Food*>(&(*(*it)));
            if(f->heating()) writer.writeAttribute("heat-product", "1");

            if(class_name == QCafe::SANDWICH) {
                const Sandwich* san = static_cast<const Sandwich*>(f);
                writer.writeAttribute("bread", QString::fromStdString(Sandwich::to_string(san->bread())));
                writer.writeAttribute("main-ingredient", QString::fromStdString(Sandwich::to_string(san->mainIngredient())));
                writer.writeAttribute("sauce", QString::fromStdString(Sandwich::to_string(san->sauce())));
                if(san->cheese()) writer.writeAttribute("cheese", "1");
                if(san->lettuce()) writer.writeAttribute("lettuce", "1");
            } else { // SWEET
                const Sweet* swe = static_cast<const Sweet*>(f);
                writer.writeAttribute("flavour", QString::fromStdString(Sweet::to_string(swe->flavouring())));
                if(swe->whippedCream()) writer.writeAttribute("whipped-cream", "1");
            }
        }

        writer.writeEndElement(); // </getTagName(class_name)>

        // se c'è stato un problema in scrittura interrompe ed esce
        if(writer.hasError()) {
            throw FileException(FileException::OUTPUT, "There was an error while trying to write the save file.");
        }
    }

    writer.writeEndElement(); // </root>
    writer.writeEndDocument();

    file.commit(); // scrivo il contenuto del buffer su file
}

std::string XMLFileIO::filename() const {
    return file_name.toStdString();
}

void XMLFileIO::setFileName(const string& fn) {
    file_name = QString::fromStdString(fn);
}

