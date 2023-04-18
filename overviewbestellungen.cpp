#include <QSqlQuery>
#include <QMessageBox>
#include "overviewbestellungen.h"
#include "overviewbestellungen_bestellung.h"
#include "qsqlerror.h"
#include "ui_overviewbestellungen.h"

#include "mainwindow.h"

OverviewBestellungen::OverviewBestellungen(MainWindow* parent) : QWidget(parent), ui(new Ui::OverviewBestellungen)
{
    ui->setupUi(this);
    this->parent = parent;

    connect(ui->search_field, &QLineEdit::textChanged, this, &OverviewBestellungen::searchCustomer);
}

OverviewBestellungen::~OverviewBestellungen()
{
    delete ui;
}

void OverviewBestellungen::on_back_to_main_clicked()
{
    this->parent->back_to_main();
}

void OverviewBestellungen::searchCustomer(const QString &text)
{
    if (text.length() < 3) {
        // Suche nicht starten, wenn weniger als 3 Buchstaben eingegeben wurden
        return;
    }

    ui->customer_list->clear();

    // Suche nach Kunden mit dem eingegebenen Text im Namen
    QSqlQuery query;
    query.prepare("SELECT * FROM kunden WHERE Name LIKE :name");
    query.bindValue(":name", "%" + text + "%");

    if (!query.exec()) {
        // Fehler beim Ausführen der Abfrage
        qDebug() << "Fehler beim Suchen nach Kunden:";
        qDebug() << query.lastError().text();
        return;
    }

    // Fügen Sie jeden gefundenen Kunden zur Liste hinzu
    while (query.next()) {
        QString customerName = query.value("Name").toString();
        QString customerAddress = query.value("Straße").toString() + " " + query.value("Hausnummer").toString();
        QString customerCity = query.value("ID_Ort").toString();
        QString customerPhone = query.value("Telefon").toString();
        QString customerId = query.value("ID_Kunde").toString();

        QListWidgetItem *item = new QListWidgetItem(ui->customer_list);
        item->setText(customerName);
        item->setData(Qt::UserRole, customerId);
        item->setToolTip("Adresse: " + customerAddress + "\n" + "ID_Ort:\t" + customerCity + "\n" + "Tel.:\t" + customerPhone);
    }
}

void OverviewBestellungen::on_next_button_clicked()
{
    if (ui->customer_list->selectedItems().empty()) {
        QMessageBox::information(this, "Information", "Bitte wählen Sie einen Kunden aus.");
    } else {
        // customerId des ausgewählten Elements holen
        int selectedCustomerId = ui->customer_list->selectedItems()[0]->data(Qt::UserRole).toInt();

        QStackedWidget* stack = this->parent->GetStack();
        OverviewBestellungen_Bestellung* bestellung = new OverviewBestellungen_Bestellung(selectedCustomerId);

        // Widget bestellung hinzufügen
        stack->addWidget(bestellung);

        // neues Fenster öffnen
        stack->setCurrentIndex(5);
    }
}
