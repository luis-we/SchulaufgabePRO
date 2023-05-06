#include "overviewlieferanten.h"
#include "ui_overviewlieferanten.h"
#include "listitem.h"
#include "qsqlerror.h"
#include "lieferant.h"

#include <QSqlQuery>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QPushButton>

using namespace std;

OverviewLieferanten::OverviewLieferanten(MainWindow* parent) : QWidget(parent), ui(new Ui::OverviewLieferanten)
{
    ui->setupUi(this);//Erstellt UI für OverviewLieferanten

    this->parent = parent; //Übergibt parent an private Variable

    this->m_layout = new QVBoxLayout(this);

    this->lieferanten = new vector<ListItem<QString>*>();

    QSqlQuery query;
    query.prepare("SELECT * FROM lieferanten"); //SQL Abfrage nach allen Lieferanten aus Tabelle

    //Prüft ob Fehler beim SQL Querry auftreten und gibt Fehler aus
    if (!query.exec()) {
        qDebug() << "Fehler beim Suchen nach Lieferanten: " << query.lastError().text();
        return;
    }

    while (query.next()) {
        QPushButton* button = new QPushButton(this);

        QString lieferantName = query.value("Name").toString();

        ListItem<QString>* lieferant = new ListItem<QString>(&lieferantName, button);

        connect(button, &QPushButton::clicked, [this, lieferant](){ this->on_list_item_clicked(lieferant); });

        button->setText(lieferantName);

        this->layout()->addWidget(button);
        this->lieferanten->push_back(lieferant);
    }


    //Laden der Anreden
    LadeAnreden();

    //Laden der Orte
    LadeOrte();

    //Laden der Lieferanten
    LadeLieferanten();
}

OverviewLieferanten::~OverviewLieferanten()
{
    delete ui; //Löscht UI wenn Fenster geschlossen wird
}

//Anrede wird geladen und in DropDown Menü angezeigt
void OverviewLieferanten::LadeAnreden()
{
    QSqlQuery query;

    //SQL Abfrage nach allen Anreden aus Tabelle
    query.prepare("SELECT * FROM anrede");

    //Prüft ob Fehler beim SQL Querry auftreten und gibt Fehler aus
    if (!query.exec()) {
        qDebug() << "Fehler bei der Suchen nach Anreden: " << query.lastError().text();
        return;
    }

    //Löschen aller Einträge im Drop-Down Menü
    while (query.next()) {
        //Auslesen der Anrede und der ID
        int anrede_id = query.value("ID_Anrede").toInt();
        QString anrede = query.value("Anrede").toString();

        //Hinzufügen zum DropDown
        ui->textBrowser_anrede->addItem(anrede, anrede_id);
    }
}

// Lade Lieferanten aus DB
void OverviewLieferanten::LadeLieferanten()
{
    QSqlQuery query;

    // SQL Abfragein Tab Lieferanten
    query.prepare("SELECT * FROM lieferanten");

    // Fehlerabfrage
    if (!query.exec()) {
        qDebug() << "Fehler bei der Suchen nach Lieferanren: " << query.lastError().text();
        return;
    }

    // Query Auslesen und schreiben in Lieferanten
    while (query.next()) {
        //
        lieferanten* lieferanten = new lieferant(
            query.value("ID_Lieferant").toInt(),
            query.value("Lieferantenname").toString(),
            query.value("Anrede_Ansprechpartner").toInt(),
            query.value("Ansprechpartner").toString(),
            query.value("Telefon").toString(),
            query.value("Straße").toString(),
            query.value("Hausnummer").toString(),
            query.value("ID_Ort").toInt(),
        );

        // Hinzufügen des Lieferanten in Tabelle
        ErstelleLieferant(lieferant);
    }
}



//Leeren des Forms
void OverviewLieferanten::LeereForm() {
    ui->textBrowser_anrede->setCurrentIndex(-1);
    ui->textBrowser_lieferantenansprechpartner->clear();
    ui->textBrowser_lieferantenhsnr->clear();
    ui->textBrowser_lieferantenid->clear();
    ui->textBrowser_lieferantenname->clear();
    ui->textBrowser_lieferantenstrasse->clear();
    ui->textBrowser_ort->setCurrentIndex(-1);
    ui->textBrowser_plz->clear();
    ui->textBrowser_lieferantentelefon->clear();
}

//Lade Orte aus DB -> DropDown
void OverviewLieferanten::LadeOrte()
{
    QSqlQuery query;

    //Select Orte
    query.prepare("SELECT * FROM ort");

    //Check Datenbank Abfrage
    if (!query.exec()) {
        qDebug() << "Fehler bei der Suchen nach Orten: " << query.lastError().text();
        return;
    }

    //alle Orte auslesen
    while (query.next()) {
        //in Var schreiben
        int ort_id = query.value("ID_Ort").toInt();
        QString ort = query.value("Ort").toString();

        //Hinzufügen des Ortes in das Drop-Down Menü
        ui->textBrowser_ort->addItem(ort, ort_id);
    }
}

//Erstellen eines Listeneintrags vom Typ Kunde
ListItem<lieferant>* OverviewLieferanten::ErstelleLieferant(lieferant* lieferant)
{
    //Erstellung des Buttons für den Kunden
    QPushButton* button = new QPushButton(this);

    //Erstellung des Listeneintrages (Verknüpfung von Button und Kunde)
    ListItem<lieferant>* lieferatenTeil = new ListItem<lieferant>(lieferant, button);

    //Verbindung des On-Click Events des Buttons mit der Funktion zur übermittlung des Ausgewählten Kunden
    connect(button, &QPushButton::clicked, [this, lieferatenTeil](){ this->on_list_item_clicked(lieferatenTeil); });

    //Setzen des Button Textes auf den Vollständigen Namen des Kunden
    button->setText(lieferant->getDisplayText());

    //Hinzugügen des Buttons in das Layout der Kundenliste
    this->m_layout->addWidget(button); //?????????????

    //Hinzufügen des Listeneintrags in den Vector der Kundenliste
    this->m_customers->push_back(lieferatenTeil);//?????????????

    //Rückgabe des Listeneintrages
    return lieferatenTeil;
}

void OverviewLieferanten::on_list_item_clicked(ListItem<QString>* item)
{
    qDebug() << "Clicked: " << item->GetButton()->text();
}

void OverviewLieferanten::on_back_to_main_clicked()
{
    this->parent->back_to_main(); //Zurück zum Hauptmenü Button
}

void OverviewLieferanten::on_pushButton_anlegen_clicked()
{
    //Button zum Anlegen eines neuen Lieferanten in der SQL Tabelle Lieferanten
    QSqlQuery query_insert; //SQL Query zum Einfügen eines neuen Lieferanten
    //Zusammenbauen der SQL Abfrage mit den Werten aus den Textfeldern
    query_insert.prepare("INSERT INTO lieferanten (Lieferantenname, Anrede_Ansprechpartner, Ansprechpartner, Telefon, Straße, Hausnummer, ID_Ort) VALUES (:Lieferantenname, :Anrede_Ansprechpartner, :Ansprechpartner, :Telefon, :Straße, :Hausnummer, :ID_Ort)");

    //Binden der Werte aus den Textfeldern an die SQL Abfrage
    query_insert.bindValue(":Lieferantenname", ui->textBrowser_lieferantenname->toPlainText());
    query_insert.bindValue(":Anrede_Ansprechpartner", ui->textBrowser_anrede->currentText());
    query_insert.bindValue(":Ansprechpartner", ui->textBrowser_lieferantenansprechpartner->toPlainText());
    query_insert.bindValue(":Telefon", ui->textBrowser_lieferantentelefon->toPlainText());
    query_insert.bindValue(":Straße", ui->textBrowser_lieferantenstrasse->toPlainText());
    query_insert.bindValue(":Hausnummer", ui->textBrowser_lieferantenhsnr->toPlainText());
    query_insert.bindValue(":ID_Ort", ui->textBrowser_ort->currentText());
    //query_insert.bindValue(":ID_Lieferant", ui->textBrowser_lieferantenid->toPlainText());

    query_insert.exec(); //Führt Query aus
    //Prüft ob Fehler beim SQL Querry auftreten und gibt Fehler aus
    if (!query_insert.exec()) {
        qDebug() << "Fehler beim Anlegen eines Lieferanten: " << query_insert.lastError().text();
        return;
    }
}

void OverviewLieferanten::on_pushButton_2_bearbeiten_clicked()
{
    //Funktion um einen gesuchten Lieferanten zu bearbeiten und wieder in die SQL Tabelle zurückschreiben
    QSqlQuery query_update; //SQL Query zum Updaten eines Lieferanten
    query_update.prepare("UPDATE lieferanten SET Lieferantenname = :Lieferantenname, Anrede_Ansprechpartner = :Anrede_Ansprechpartner, Ansprechpartner = :Ansprechpartner, Telefon = :Telefon, Straße = :Straße, Hausnummer = :Hausnummer, ID_Ort = :ID_Ort WHERE ID_Lieferant = :ID_Lieferant");
    
    //Binden der Werte aus den Textfeldern an die SQL Abfrage
    query_update.bindValue(":Lieferantenname", ui->textBrowser_lieferantenname->toPlainText());
    query_update.bindValue(":Anrede_Ansprechpartner", ui->textBrowser_anrede->currentText());
    query_update.bindValue(":Ansprechpartner", ui->textBrowser_lieferantenansprechpartner->toPlainText());
    query_update.bindValue(":Telefon", ui->textBrowser_lieferantentelefon->toPlainText());
    query_update.bindValue(":Straße", ui->textBrowser_lieferantenstrasse->toPlainText());
    query_update.bindValue(":Hausnummer", ui->textBrowser_lieferantenhsnr->toPlainText());
    query_update.bindValue(":ID_Ort", ui->textBrowser_ort->currentText());
    //query_update.bindValue(":ID_Lieferant", ui->textBrowser_lieferantenid->toPlainText());

    query_update.exec(); //Führt Query aus
    //Prüft ob Fehler beim SQL Querry auftreten und gibt Fehler aus
    if (!query_update.exec()) {
        qDebug() << "Fehler beim Bearbeiten eines Lieferanten: " << query_update.lastError().text();
        return;
    }  
}

void OverviewLieferanten::on_pushButton_3_loeschen_clicked()
{
    //Button zum Löschen eines Lieferanten
    QSqlQuery query_delete;
    query_delete.prepare("DELETE FROM lieferanten WHERE ID_Lieferant = :ID_Lieferant");

    query_delete.bindValue(":ID_Lieferant", ui->textBrowser_lieferantenid->toPlainText());

    query_delete.exec(); //Führt Query aus
    //Prüft ob Fehler beim SQL Querry auftreten und gibt Fehler aus
    if (!query_delete.exec()) {
        qDebug() << "Fehler beim LÖSCHEN eines Lieferanten: " << query_delete.lastError().text();
        return;
    }
}

void OverviewLieferanten::on_pushButton_leeren_clicked()
{
    LeereForm();
}

void OverviewLieferanten::SpeichereLieferant(bool created)
{
}

void OverviewLieferanten::LoescheLieferant()
{
}

bool OverviewLieferanten::UeberpruefeEingabe()
{
    return false;
}

QString OverviewLieferanten::HolePLZVonOrt(int ort)
{
    return QString();
}

void OverviewLieferanten::WaehleLieferant(ListItem<lieferant> *lieferant)
{
}
