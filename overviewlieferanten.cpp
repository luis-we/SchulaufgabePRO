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
    ui->setupUi(this);
    
    //Übergibt parent an private Variable
    this->parent = parent; 

    this->m_layout = new QVBoxLayout(this);

    ui->scrollArea->setLayout(this->m_layout);

    this->m_lieferanten = new vector<ListItem<lieferant>*>();

    this->m_ausgewaelterLieferant = nullptr;

   //Deaktivieren der Erstellen & Löschen Buttons
    ui->pushButton_anlegen->setDisabled(true);
    ui->pushButton_3_loeschen->setDisabled(true);

    //Laden der Anreden
    LadeAnreden();

    //Laden der Orte
    LadeOrte();

    //Laden der Lieferanten
    LadeLieferanten();

    //Leere das Formular initial
    LeereForm();
}

OverviewLieferanten::~OverviewLieferanten()
{
    // Löscht UI wenn Fenster geschlossen wird
    delete ui;
}


// Anrede wird geladen und in DropDown Menü angezeigt
void OverviewLieferanten::LadeAnreden()
{
    QSqlQuery query;

    // SQL Abfrage nach allen Anreden aus Tabelle
    query.prepare("SELECT * FROM anrede");

    // Prüft ob Fehler SQL Querry auftreten & gibt Fehler aus
    if (!query.exec()) {
        qDebug() << "Fehler bei der Suchen nach Anreden: " << query.lastError().text();
        return;
    }

    // Löscht alle Einträge im Drop-Down Menü
    while (query.next()) {
        //Auslesen der Anrede und der ID
        int anrede_id = query.value("ID_Anrede").toInt();
        QString anrede = query.value("Anrede").toString();

        // Hinzufügen zum DropDown damit aktuell
        ui->textBrowser_anrede->addItem(anrede, anrede_id);
    }
}



// Leeren des Forms
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

// Lade Orte aus DB -> DropDown
void OverviewLieferanten::LadeOrte()
{
    QSqlQuery query;

    // Select Orte
    query.prepare("SELECT * FROM ort");

    // Check Datenbank Abfrage
    if (!query.exec()) {
        qDebug() << "Fehler bei der Suchen nach Orten: " << query.lastError().text();
        return;
    }

    // alle Orte auslesen
    while (query.next()) {
        //in Var schreiben
        int ort_id = query.value("ID_Ort").toInt();
        QString ort = query.value("Ort").toString();

        // Hinzufügen Ortes in das DropDown Menü
        ui->textBrowser_ort->addItem(ort, ort_id);
    }
}

// Zum füllen der Liste
void OverviewLieferanten::LadeLieferanten()
{
    QSqlQuery query;

    // Laden der Lieferanten aus SQL Tabelle
    query.prepare("SELECT * FROM lieferant");

    // Check der SQL Abfrage auf Fehler -> Ausgabe
    if (!query.exec()) {
        qDebug() << "Fehler bei der Suchen nach Lieferant: " << query.lastError().text();
        return;
    }

    // Schleife zum Auslesen Lieferanten
    while (query.next()) {
        // Erstellung Lieferant Objekt mit Daten aus DB
        lieferant* delivery = new lieferant(
                query.value("ID_Lieferant").toInt(),
                query.value("Anrede_Ansprechpartner").toInt(),
                query.value("Lieferantenname").toString(),
                query.value("Ansprechpartner").toString(),
                query.value("Straße").toString(),
                query.value("Hausnummer").toString(),
                query.value("ID_Ort").toInt(),
                query.value("Telefon").toString()
        );

        // Erstelle Lieferant Objekt für Liste
        ErstelleLieferant(delivery);
    }
}

void OverviewLieferanten::LadeLieferant(lieferant* delivery)
{
    // Schreiben der Werte aus Obj in die Felder des Forms
    ui->textBrowser_lieferantenid->setText(QString::number(delivery->getID()));
    ui->textBrowser_lieferantenname->setText(delivery->getName());
    ui->textBrowser_lieferantenansprechpartner->setText(delivery->getAnsprechpartner());
    ui->textBrowser_lieferantenstrasse->setText(delivery->getStrasse());
    ui->textBrowser_lieferantenhsnr->setText(delivery->getHausNr());
    ui->textBrowser_lieferantentelefon->setText(delivery->getTelefon());
    

    // Stelle DropDown auf die passenden Werte ein
    ui->textBrowser_anrede->setCurrentIndex(ui->textBrowser_anrede->findData(delivery->getAnrede()));
    ui->textBrowser_ort->setCurrentIndex(ui->textBrowser_ort->findData(delivery->getOrt()));
}

// Erstellen des Listen Eintrags Lieferant
ListItem<lieferant>* OverviewLieferanten::ErstelleLieferant(lieferant* delivery)
{
    // Hier Button erstellen zum anklicken
    QPushButton* button = new QPushButton(this);

    // Listeneintrages generieren (Link zw Lieferant & Button)
    ListItem<lieferant>* lieferatenTeil = new ListItem<lieferant>(delivery, button);

    // Connect zw. Button und Objekt zum übertragen der Daten
    connect(button, &QPushButton::clicked, [this, lieferatenTeil](){ this->on_list_item_clicked(lieferatenTeil); });

    // Schreibe Lieferantenname in den Button
    button->setText(delivery->getName());

    // Füge button in das Layout ein in die Scrollbox
    this->m_layout->addWidget(button);

    // Hinzufügen des Listeneintrags in den Vector der Kundenliste
    this->m_lieferanten->push_back(lieferatenTeil);

    // Rückgabe des Listeneintrages
    return lieferatenTeil;
}

void OverviewLieferanten::on_list_item_clicked(ListItem<lieferant>* item)
{
    // Auswählen des geklickten Kunden
    WaehleLieferant(item);
}

void OverviewLieferanten::on_back_to_main_clicked()
{
    this->parent->back_to_main(); //Zurück zum Hauptmenü Button
}

void OverviewLieferanten::on_pushButton_anlegen_clicked()
{
     //Zurücksetzen des ausgewählten Kunden
    m_ausgewaelterLieferant = nullptr;

    //Zurücksetzen der Formularfelder auf ihre Initialwerte
    LeereForm();

    //Deaktivieren der neu und löschen Buttons
    ui->pushButton_anlegen->setDisabled(true);
    ui->pushButton_anlegen->setDisabled(true);
}

void OverviewLieferanten::on_pushButton_2_bearbeiten_clicked()
{
    //Abbruch der Funktion wenn die Eingabeüberprüfung fehlschlägt
    if(!UeberpruefeEingabe()) {
        return;
    }

    bool created = false;

    //Überprüfung ob kein Kunde ausgewählt ist
    if(this->m_ausgewaelterLieferant == nullptr) {
        //Erstellung eines neuen Kunden-Ojektes
        lieferant* delivery = new lieferant();

        //Erstelllung eines neuen Listeneintrags für den Kunden
        this->m_ausgewaelterLieferant = ErstelleLieferant(delivery);

        //Zwischenspeichern das ein neuer Kunde erstellt wurde
        created = true;
    }

    //Speichern des ausgewählten oder neu erstellten Kunden
    SpeichereLieferant(created);
}

void OverviewLieferanten::on_pushButton_3_loeschen_clicked()
{
    // Zurücksetzen der Formularfelder auf ihre Initialwerte
    LeereForm();

    // Abbruch der Funktion wenn kein Kunde ausgewählt ist
    if(this->m_ausgewaelterLieferant == nullptr)
        return;

    // Löschen des Kunden aus der Kundenliste und der Datenbank
    LoescheLieferant();

    // Deaktivieren der neu und löschen Buttons
    ui->pushButton_anlegen->setDisabled(true);
    ui->pushButton_3_loeschen->setDisabled(true);
}


void OverviewLieferanten::on_pushButton_leeren_clicked()
{
    LeereForm();
}

void OverviewLieferanten::SpeichereLieferant(bool created)
{
    // Auslesen des aktuell ausgewählten Kunden
    lieferant* delivery = m_ausgewaelterLieferant->GetValue();

    delivery->setAnrede(ui->textBrowser_anrede->currentData().value<int>());
    delivery->setName(ui->textBrowser_lieferantenname->toPlainText());
    delivery->setStrasse(ui->textBrowser_lieferantenstrasse->toPlainText());
    delivery->setHausNr(ui->textBrowser_lieferantenhsnr->toPlainText());
    delivery->setOrt(ui->textBrowser_ort->currentData().value<int>());
    delivery->setTelefon(ui->textBrowser_lieferantentelefon->toPlainText());
    delivery->setAnsprechpartner(ui->textBrowser_lieferantenansprechpartner->toPlainText());

    if(created) {

        LadeLieferant(delivery);
    }
}

void OverviewLieferanten::LoescheLieferant()
{
    // Löscht den Kunden aus der Kundenliste
    delete m_ausgewaelterLieferant;

    // Setzt den ausgewählten Kunden auf einen null pointer
    m_ausgewaelterLieferant = nullptr;
}

bool OverviewLieferanten::UeberpruefeEingabe()
{
    return false;
}


void OverviewLieferanten::WaehleLieferant(ListItem<lieferant> *delivery)
{
    // Abbruch bei wiederholten auswählen eines Kunden
    if(this->m_ausgewaelterLieferant == delivery) return;

    // Aktivieren der Erstellen und Löschen Buttons
    ui->pushButton_anlegen->setDisabled(false);
    ui->pushButton_3_loeschen->setDisabled(false);

    // Ausgewählten Kunden setzen
    this->m_ausgewaelterLieferant = delivery;

    // Kundendetails in das Formular Laden
    LadeLieferant(delivery->GetValue());
}

//
void OverviewLieferanten::Ortswechsel(int index)
{
    //
    if(index == -1) {
        //
        ui->textBrowser_plz->clear();
        return;
    }

    //
    int location = ui->textBrowser_ort->currentData().value<int>();

    //
    ui->textBrowser_plz->setText(HolePLZVonOrt(location));
}


QString OverviewLieferanten::HolePLZVonOrt(int loc)
{
    // Initialisieren der Postleitzahl
    QString plz = "";

    QSqlQuery query;

    // Select Statement zum auslesen der Postleitzahl des dazugehörigen Ortes
    query.prepare("SELECT PLZ FROM ort WHERE ID_Ort = " + QString::number(loc));

    // Überprüfung der Datenbank Abfrage
    if (!query.exec()) {
        qDebug() << "Fehler bei der Suchen nach PLZ: " << query.lastError().text();
        return plz;
    }

    // Schleifendurchlauf zum Auslesen und Speichern der Postleitzahl
    while (query.next()) {
        plz = query.value("PLZ").toString();
    }

    // Rückgabe der Postleitzahl
    return plz;
}
