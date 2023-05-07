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

    this->m_lieferanten = new vector<ListItem<lieferant>*>();

    this->m_ausgewaelterLieferant = nullptr;


   //Deaktivieren der Erstellen und Löschen Buttons
    ui->pushButton_anlegen->setDisabled(true);
    ui->pushButton_3_loeschen->setDisabled(true);


    //Laden der Anreden
    LadeAnreden();

    //Laden der Orte
    LadeOrte();

    //Laden der Lieferanten
    LadeLieferanten();

    LeereForm();
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



//Leeren des Forms
void OverviewLieferanten::LeereForm()
{
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

//ZUm füllen der Liste
void OverviewLieferanten::LadeLieferanten()
{
    QSqlQuery query;

    //Select Statement zum Lade der Kunden
    query.prepare("SELECT * FROM lieferant");

    //Überprüfung der Datenbank Abfrage
    if (!query.exec()) {
        qDebug() << "Fehler bei der Suchen nach Lieferant: " << query.lastError().text();
        return;
    }

    //Schleifendurchlauf zum Auslesen aller Kunden
    while (query.next()) {
        //Erstellung eines neuen Kunden-Objektes mit den Werten aus der Datenbank
        lieferant* delivery = new lieferant(
            query.value("ID_Lieferant").toInt(),
            query.value("Anrede_Ansprechpartner").toInt(),
            query.value("Lieferantenname").toString(),
            query.value("Straße").toString(),
            query.value("Hausnummer").toString(),
            query.value("ID_Ort").toInt(),
            query.value("Telefon").toString(),
            query.value("Ansprechpartner").toString()
        );

        //Erstellen eines Listeneintrags des Kundens für die Kundenliste
        ErstelleLieferant(delivery);
    }
}

void OverviewLieferanten::LadeLieferant(lieferant* delivery)
{
    //Setzen aller Parameter vom Kunden in die Formular Felder
    ui->textBrowser_lieferantenid->setText(QString::number(delivery->getID()));
    ui->textBrowser_lieferantenname->setText(delivery->getName());
    ui->textBrowser_lieferantenansprechpartner->setText(delivery->getAnsprechpartner());
    ui->textBrowser_lieferantenstrasse->setText(delivery->getStrasse());
    ui->textBrowser_lieferantenhsnr->setText(delivery->getHausNr());
    ui->textBrowser_lieferantentelefon->setText(delivery->getTelefon());
    

    //Setzen der Drop-Down-Felder anhand der im Kunden gespeicherten ID's
    ui->textBrowser_anrede->setCurrentIndex(ui->textBrowser_anrede->findData(delivery->getAnrede()));
    ui->textBrowser_ort->setCurrentIndex(ui->textBrowser_ort->findData(delivery->getOrt()));
}

//Erstellen eines Listeneintrags vom Typ Kunde
ListItem<lieferant>* OverviewLieferanten::ErstelleLieferant(lieferant* delivery)
{
    //Erstellung des Buttons für den Kunden
    QPushButton* button = new QPushButton(this);

    //Erstellung des Listeneintrages (Verknüpfung von Button und Kunde)
    ListItem<lieferant>* lieferatenTeil = new ListItem<lieferant>(delivery, button);

    //Verbindung des On-Click Events des Buttons mit der Funktion zur übermittlung des Ausgewählten Kunden
    connect(button, &QPushButton::clicked, [this, lieferatenTeil](){ this->on_list_item_clicked(lieferatenTeil); });

    //Setzen des Button Textes auf den Vollständigen Namen des Kunden
    button->setText(delivery->getAnsprechpartner());

    //Hinzugügen des Buttons in das Layout der Kundenliste
    this->m_layout->addWidget(button); //?????????????

    //Hinzufügen des Listeneintrags in den Vector der Kundenliste
    this->m_lieferanten->push_back(lieferatenTeil);//?????????????

    //Rückgabe des Listeneintrages
    return lieferatenTeil;
}

void OverviewLieferanten::on_list_item_clicked(ListItem<lieferant>* item)
{
    //Auswählen des geklickten Kunden
    WaehleLieferant(item);
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
    query_update.prepare("UPDATE lieferant SET Lieferantenname = :Lieferantenname, Anrede_Ansprechpartner = :Anrede_Ansprechpartner, Ansprechpartner = :Ansprechpartner, Telefon = :Telefon, Straße = :Straße, Hausnummer = :Hausnummer, ID_Ort = :ID_Ort WHERE ID_Lieferant = :ID_Lieferant");
    
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
    //Zurücksetzen der Formularfelder auf ihre Initialwerte
    LeereForm();

    //Abbruch der Funktion wenn kein Kunde ausgewählt ist
    if(this->m_ausgewaelterLieferant == nullptr)
        return;

    //Löschen des Kunden aus der Kundenliste und der Datenbank
    LoescheLieferant();

    //Deaktivieren der neu und löschen Buttons
    ui->pushButton_anlegen->setDisabled(true);
    ui->pushButton_3_loeschen->setDisabled(true);
}


void OverviewLieferanten::on_pushButton_leeren_clicked()
{
    LeereForm();
}

void OverviewLieferanten::SpeichereLieferant(bool created)
{
    //Auslesen des aktuell ausgewählten Kunden
    lieferant* delivery = m_ausgewaelterLieferant->GetValue();

    delivery->setAnrede(ui->textBrowser_anrede->currentData().value<int>());
    delivery->setName(ui->textBrowser_lieferantenname->toPlainText());
    delivery->setStrasse(ui->textBrowser_lieferantenstrasse->toPlainText());
    delivery->setHausNr(ui->textBrowser_lieferantenhsnr->toPlainText());
    delivery->setOrt(ui->textBrowser_ort->currentData().value<int>());
    delivery->setTelefon(ui->textBrowser_lieferantentelefon->toPlainText());
    delivery->setAnsprechpartner(ui->textBrowser_lieferantenansprechpartner->toPlainText());

    if(created) {
        //Erstellen eines neuen Kundeneintrags in der Datenbank
        //customer->create();
        //Laden der Kundendetails in das Formular
        LadeLieferant(delivery);
    }
    else {
        //Speichern der veränderten Kundendaten
        //customer->save();
    }
}

void OverviewLieferanten::LoescheLieferant()
{
    //Löscht den Kunden aus der Kundenliste
    delete m_ausgewaelterLieferant;
    //Setzt den ausgewählten Kunden auf einen null pointer
    m_ausgewaelterLieferant = nullptr;
}

bool OverviewLieferanten::UeberpruefeEingabe()
{
    return false;
}


void OverviewLieferanten::WaehleLieferant(ListItem<lieferant> *delivery)
{
    //Abbruch bei wiederholten auswählen eines Kunden
    if(this->m_ausgewaelterLieferant == delivery) return;

    //Aktivieren der Erstellen und Löschen Buttons
    ui->pushButton_anlegen->setDisabled(false);
    ui->pushButton_3_loeschen->setDisabled(false);

    //Ausgewählten Kunden setzen
    this->m_ausgewaelterLieferant = delivery;

    //Kundendetails in das Formular Laden
    LadeLieferant(delivery->GetValue());
}


QString OverviewLieferanten::HolePLZVonOrt(int loc)
    //Initialisieren der Postleitzahl
    QString plz = "";

    QSqlQuery query;

    //Select Statement zum auslesen der Postleitzahl des dazugehörigen Ortes
    query.prepare("SELECT PLZ FROM ort WHERE ID_Ort = " + QString::number(loc));

    //Überprüfung der Datenbank Abfrage
    if (!query.exec()) {
        qDebug() << "Fehler bei der Suchen nach PLZ: " << query.lastError().text();
        return plz;
    }

    //Schleifendurchlauf zum Auslesen und Speichern der Postleitzahl
    while (query.next()) {
        plz = query.value("PLZ").toString();
    }

    //Rückgabe der Postleitzahl
    return plz;
}