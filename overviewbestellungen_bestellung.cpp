// overviewbestellungen_bestellung.cpp
#include "overviewbestellungen_bestellung.h"
#include "ui_overviewbestellungen_bestellung.h"
#include <QStackedWidget>
#include <QSqlQuery>
#include <QMessageBox>
#include <qlistwidget.h>
#include <mainwindow.h>
#include "qsqlerror.h"



OverviewBestellungen_Bestellung::OverviewBestellungen_Bestellung(int customerId, QStackedWidget* stack, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::overviewbestellungen_bestellung),
    m_customerId(customerId),
    m_stack(stack)
{
    ui->setupUi(this);

    // Den customerId im Label_ID anzeigen
    ui->ID_Label->setText(QString::number(customerId));

    connect(ui->artikelSuche, &QLineEdit::textChanged, this, &OverviewBestellungen_Bestellung::searchArtikel);
}

OverviewBestellungen_Bestellung::~OverviewBestellungen_Bestellung()
{
    delete ui;
}

void OverviewBestellungen_Bestellung::searchArtikel(const QString &searchText)
{
    if (searchText.length() < 3) {
        // Suche nicht starten, wenn weniger als 3 Buchstaben eingegeben wurden
        return;
    }

    ui->artikelListe->clear();

    // Suche nach Artikel mit dem eingegebenen Text im Namen
    QSqlQuery queryArtikel;
    queryArtikel.prepare("SELECT * FROM kunden WHERE Name LIKE :name");
    queryArtikel.bindValue(":name", "%" + searchText + "%");

    if (!queryArtikel.exec()) {
        // Fehler beim Ausführen der Abfrage
        qDebug() << "Fehler beim Suchen nach Kunden:";
        qDebug() << queryArtikel.lastError().text();
        return;
    }

    // Fügen Sie jeden gefundenen Kunden zur Liste hinzu
    while (queryArtikel.next()) {
        QString customerName = queryArtikel.value("Name").toString();
        QString customerAddress = queryArtikel.value("Straße").toString() + " " + queryArtikel.value("Hausnummer").toString();
        QString customerCity = queryArtikel.value("ID_Ort").toString();
        QString customerPhone = queryArtikel.value("Telefon").toString();
        QString customerId = queryArtikel.value("ID_Kunde").toString();

        QListWidgetItem *itemArtikel = new QListWidgetItem(ui->artikelListe);
        itemArtikel->setText(customerName);
        itemArtikel->setData(Qt::UserRole, customerId);
        itemArtikel->setToolTip("Adresse: " + customerAddress + "\n" + "ID_Ort:\t" + customerCity + "\n" + "Tel.:\t" + customerPhone);
    }

}

void OverviewBestellungen_Bestellung::on_back_clicked()
{
    m_stack->setCurrentIndex(4);
}


void OverviewBestellungen_Bestellung::on_orders_clicked()
{
    m_liste = new overviewbestellungen_liste(m_customerId, m_stack);
    m_stack->addWidget(m_liste);
    m_stack->setCurrentIndex(6);
}
