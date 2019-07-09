#include "EditQueuedOrderDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

EditQueuedOrderDialog::EditQueuedOrderDialog(order_type type, const QString& orderInfo, QWidget *parent):
QDialog(parent), take_away(new QCheckBox("Take away", this)), heating(nullptr), sweetener(nullptr),
confirm(new QPushButton("Confirm edit", this)), cancel(new QPushButton("Cancel", this)) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    QHBoxLayout* buttonsLayout = new QHBoxLayout(this);
    QLabel* info = new QLabel("Editing " + orderInfo, this);

    // metto un background bianco e allargo il bordo per rendere la lettura delle info sull'ordine più leggibili
    info->setStyleSheet("QLabel { background-color: white}");

    // label con il contenuto dell'OrderListItem in modo da ricordare cosa si sta modificando
    layout->addWidget(info);
    // checkbox per cambiare il valore restituito da takeAway() nell'oggetto
    layout->addWidget(take_away);
    if(type == BEVERAGE) {
        sweetener = new QComboBox(this);
        layout->addWidget(sweetener);
    } else {
        heating = new QCheckBox("Heat product", this);
        layout->addWidget(heating);
    }
    // pulsanti per conferma / annullamento delle modifiche
    buttonsLayout->addWidget(confirm);
    buttonsLayout->addWidget(cancel);
    layout->addLayout(buttonsLayout);

    // connessione signal e slot dei pulsanti
    connect(confirm, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));

    // parametri di visualizzazione del dialog
    layout->setContentsMargins(20, 20, 20, 20);
    setLayout(layout);
    setModal(true);
    setWindowTitle("QCafe - Edit queued order");
    setWindowIcon(QIcon(":/icons/coffee.png"));
}

QList<QVariant> EditQueuedOrderDialog::execAndReturnValues() {
    int code = exec();
    QList<QVariant> values; // due elementi massimo

    if(code == Accepted) {
        values.push_back(take_away->isChecked());
        if(sweetener) values.push_back(sweetener->currentText());
        else if(heating) values.push_back(heating->isChecked());
    } // else code == Rejected => la lista vuota va bene e va restituita

    return values;
}

void EditQueuedOrderDialog::setQueuedOrderEditableSettings(const QList<QString>& items) {
    if(!sweetener) return;
    sweetener->addItems(items);
}
