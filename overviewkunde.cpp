#include "overviewkunde.h"
#include "ui_overviewkunde.h"
#include "mainwindow.h"
#include "listitem.h"
#include "qsqlerror.h"
#include "kunde.h"

#include <QSqlQuery>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QVariant>

using namespace std;

//Konstruktor der Kunden Seite
OverviewKunde::OverviewKunde(MainWindow* parent) : QWidget(parent), ui(new Ui::OverviewKunde)
{
    ui->setupUi(this);

    //Speichern des Elternelements
    this->m_parent = parent;

    //Erstellung des dynamischen Layouts für die Kunden Liste
    this->m_layout = new QVBoxLayout(this);

    //Erstellung des Vektors zum Speichern von Listeneinträgen der Kunden
    this->m_customers = new vector<ListItem<Kunde>*>();

    //Initialisieren des ausgewählten Kunden
    this->m_selectedCustomer = nullptr;

    //Zuweisung des dynamischen Layouts für die Scroll Area
    ui->customers->setLayout(this->m_layout);

    //Deaktivieren der Erstellen und Löschen Buttons
    ui->create->setDisabled(true);
    ui->remove->setDisabled(true);

    //Laden der Anreden
    LoadSalutations();

    //Laden der Orte
    LoadLocations();

    //Laden der Kunden
    LoadCustomers();

    //Zurücksetzen des Formulars
    ClearForm();
}

//Destructor der Kunden Seite
OverviewKunde::~OverviewKunde()
{
    delete ui;
}

//Lädt alle Anreden aus der Datenbank und fügt sie dem Drop-Down Menü hinzu
void OverviewKunde::LoadSalutations()
{
    QSqlQuery query;

    //Select Statement zum Lade der Anreden
    query.prepare("SELECT * FROM anrede");

    //Überprüfung der Datenbank Abfrage
    if (!query.exec()) {
        qDebug() << "Fehler bei der Suchen nach Anreden: " << query.lastError().text();
        return;
    }

    //Schleifendurchlauf durch alle Anreden der Datenbank
    while (query.next()) {
        //Auslesen und Speichern der Werte
        int salutation_id = query.value("ID_Anrede").toInt();
        QString salutation = query.value("Anrede").toString();

        //Hinzufügen der Anrede in das Drop-Down Menü
        ui->salutation->addItem(salutation, salutation_id);
    }
}

//Lädt alle Orte aus der Datenbank und fügt sie dem Drop-Down Menü hinzu
void OverviewKunde::LoadLocations()
{
    QSqlQuery query;

    //Select Statement zum Lade der Orte
    query.prepare("SELECT * FROM ort");

    //Überprüfung der Datenbank Abfrage
    if (!query.exec()) {
        qDebug() << "Fehler bei der Suchen nach Orten: " << query.lastError().text();
        return;
    }

    //Schleifendurchlauf durch alle Orte der Datenbank
    while (query.next()) {
        //Auslesen und Speichern der Werte
        int ort_id = query.value("ID_Ort").toInt();
        QString ort = query.value("Ort").toString();

        //Hinzufügen des Ortes in das Drop-Down Menü
        ui->ort->addItem(ort, ort_id);
    }
}

//Löscht den Kunden
void OverviewKunde::DeleteCustomer()
{
    //Löscht den Kunden aus der Datenbank
    m_selectedCustomer->GetValue()->deleteKunde();
    //Löscht den Kunden aus der Kundenliste
    delete m_selectedCustomer;
    //Setzt den ausgewählten Kunden auf einen null pointer
    m_selectedCustomer = nullptr;
}

//Erstellen eines Listeneintrags vom Typ Kunde
ListItem<Kunde>* OverviewKunde::CreateCustomerItem(Kunde* customer)
{
    //Erstellung des Buttons für den Kunden
    QPushButton* button = new QPushButton(this);

    //Erstellung des Listeneintrages (Verknüpfung von Button und Kunde)
    ListItem<Kunde>* customerItem = new ListItem<Kunde>(customer, button);

    //Verbindung des On-Click Events des Buttons mit der Funktion zur übermittlung des Ausgewählten Kunden
    connect(button, &QPushButton::clicked, [this, customerItem](){ this->on_list_item_clicked(customerItem); });

    //Setzen des Button Textes auf den Vollständigen Namen des Kunden
    button->setText(customer->getDisplayText());

    //Hinzugügen des Buttons in das Layout der Kundenliste
    this->m_layout->addWidget(button);

    //Hinzufügen des Listeneintrags in den Vector der Kundenliste
    this->m_customers->push_back(customerItem);

    //Rückgabe des Listeneintrages
    return customerItem;
}

//Auswählen des Kunden
void OverviewKunde::SelectCustomer(ListItem<Kunde>* customer)
{
    //Abbruch bei wiederholten auswählen eines Kunden
    if(this->m_selectedCustomer == customer) return;

    //Aktivieren der Erstellen und Löschen Buttons
    ui->create->setDisabled(false);
    ui->remove->setDisabled(false);

    //Ausgewählten Kunden setzen
    this->m_selectedCustomer = customer;

    //Kundendetails in das Formular Laden
    LoadCustomer(customer->GetValue());
}

//Kundendetails in das Formular laden
void OverviewKunde::LoadCustomer(Kunde* customer) {
    //Setzen aller Parameter vom Kunden in die Formular Felder
    ui->id->setText(QString::number(customer->getId()));
    ui->titel->setText(customer->getTitel());
    ui->name->setText(customer->getName());
    ui->firstname->setText(customer->getVorname());
    ui->street->setText(customer->getStrasse());
    ui->streetnr->setText(customer->getHausNr());
    ui->phone->setText(customer->getTelefon());
    ui->mail->setText(customer->getEmail());

    //Überprüfen ob das Geburtsdatum des Kunden valide ist
    if(customer->getGeburtsdatum().isValid()) {
        //Laden des Geburtsdatums in das Formularfeld
        ui->birthdate->setDate(customer->getGeburtsdatum());
    }
    else {
        //Setzen des Datums des Formularfeldes auf das heutige Datum
        ui->birthdate->setDate(QDate::currentDate());
    }

    //Setzen der Drop-Down-Felder anhand der im Kunden gespeicherten ID's
    ui->salutation->setCurrentIndex(ui->salutation->findData(customer->getAnrede()));
    ui->ort->setCurrentIndex(ui->ort->findData(customer->getOrt()));
}

//Auslesen der Postleitzahl aus der Datenbank anhand der Ort ID
QString OverviewKunde::FetchPLZFromLocation(int location) {
    //Initialisieren der Postleitzahl
    QString plz = "";

    QSqlQuery query;

    //Select Statement zum auslesen der Postleitzahl des dazugehörigen Ortes
    query.prepare("SELECT PLZ FROM ort WHERE ID_Ort = " + QString::number(location));

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

//Zurücksetzen des Formulares auf die Initialwerte
void OverviewKunde::ClearForm() {
    ui->id->clear();
    ui->salutation->setCurrentIndex(-1);
    ui->titel->clear();
    ui->name->clear();
    ui->firstname->clear();
    ui->street->clear();
    ui->streetnr->clear();
    ui->ort->setCurrentIndex(-1);
    ui->plz->clear();
    ui->phone->clear();
    ui->birthdate->setDate(QDate::currentDate());
    ui->mail->clear();
}

//Speichern der Formularwerte in die Kundenklasse
void OverviewKunde::SaveCustomer(bool created)
{
    //Auslesen des aktuell ausgewählten Kunden
    Kunde* customer = m_selectedCustomer->GetValue();

    customer->setAnrede(ui->salutation->currentData().value<int>());
    customer->setTitel(ui->titel->toPlainText());
    customer->setName(ui->name->toPlainText());
    customer->setVorname(ui->firstname->toPlainText());
    customer->setStrasse(ui->street->toPlainText());
    customer->setHausNr(ui->streetnr->toPlainText());
    customer->setOrt(ui->ort->currentData().value<int>());
    customer->setTelefon(ui->phone->toPlainText());
    customer->setGeburtsdatum(ui->birthdate->date());
    customer->setEmail(ui->mail->toPlainText());

    if(created) {
        //Erstellen eines neuen Kundeneintrags in der Datenbank
        customer->saveKunde();
        //Laden der Kundendetails in das Formular
        LoadCustomer(customer);
    }
    else {
        //Speichern der veränderten Kundendaten
        customer->updateKunde();
    }

    //Aktualisieren des Button Textes
    m_selectedCustomer->GetButton()->setText(customer->getDisplayText());
}

//Laden der Kunden aus der Datenbank
void OverviewKunde::LoadCustomers()
{
    QSqlQuery query;

    //Select Statement zum Lade der Kunden
    query.prepare("SELECT * FROM kunden");

    //Überprüfung der Datenbank Abfrage
    if (!query.exec()) {
        qDebug() << "Fehler bei der Suchen nach Kunden: " << query.lastError().text();
        return;
    }

    //Schleifendurchlauf zum Auslesen aller Kunden
    while (query.next()) {
        //Erstellung eines neuen Kunden-Objektes mit den Werten aus der Datenbank
        Kunde* customer = new Kunde(
            query.value("ID_Kunde").toInt(),
            query.value("Anrede").toInt(),
            query.value("Name").toString(),
            query.value("Vorname").toString(),
            query.value("Straße").toString(),
            query.value("Hausnummer").toString(),
            query.value("ID_Ort").toInt(),
            query.value("Telefon").toString(),
            query.value("Geburtsdatum").toDate(),
            query.value("Email").toString(),
            query.value("Titel").toString()
        );

        //Erstellen eines Listeneintrags des Kundens für die Kundenliste
        CreateCustomerItem(customer);
    }
}

//Eingabeüberprüfung der Formularfelder
bool OverviewKunde::VerifyInput() {
    //Auslesen der Formularfelder-Werte
    QString titel = ui->titel->toPlainText();
    QString email = ui->mail->toPlainText();
    QString firstName = ui->firstname->toPlainText();
    QString lastName = ui->name->toPlainText();
    QDate birthdate = ui->birthdate->date();
    QString street = ui->street->toPlainText();
    QString phone = ui->phone->toPlainText();
    QString nr = ui->streetnr->toPlainText();
    QComboBox *comboBoxSalutation = ui->salutation;
    QComboBox *comboBoxOrt = ui->ort;

    //Erstellen der Regulären ausdrücke zur Überprüfung der Werte
    QRegularExpression regexName("[A-Za-z]{2,40}");
    QRegularExpression regexEmail("[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+[A-Za-z]{0,}");
    QRegularExpression regexStreet("[A-Za-z]{3,50}");
    QRegularExpression regexPhone("^(?=.{5,30}$)[+]?[\\d\\s]+$");
    QRegularExpression regexTitel("^[a-zA-Z .]{2,80}$");
    QRegularExpression regexNr("^\\d{1,4}\\s?[a-zA-Z]?$");

    //Überprüfung der Anrede
    if(comboBoxSalutation->currentIndex() == -1) {
        QMessageBox::warning(this, "Fehler", "Bitte wählen Sie eine Anrede aus.");
        comboBoxSalutation->setFocus();
        return false;
    }

    //Überprüfung des Titels
    if(!titel.isEmpty()) {
        if(!titel.contains(regexTitel)) {
            QMessageBox::warning(this, "Fehler", "Bitte geben Sie einen gültigen Titel ein.");
            ui->name->setFocus();
            ui->name->selectAll();
            return false;
        }
    }

    //Überprüfung des Namens
    if(!lastName.contains(regexName)) {
        QMessageBox::warning(this, "Fehler", "Bitte geben Sie einen gültigen Namen ein.");
        ui->name->setFocus();
        ui->name->selectAll();
        return false;
    }

    //Überprüfung des Vornamens
    if(!firstName.contains(regexName)) {
        QMessageBox::warning(this, "Fehler", "Bitte geben Sie einen gültigen Vornamen ein.");
        ui->firstname->setFocus();
        ui->firstname->selectAll();
        return false;
    }

    //Überprüfung der Strasse
    if(!street.contains(regexStreet)) {
        QMessageBox::warning(this, "Fehler", "Bitte geben Sie ein gültiges Straße ein.");
        ui->street->setFocus();
        ui->birthdate->selectAll();
        return false;
    }

    //Überprüfung der Hausnummer
    if(!nr.contains(regexNr)) {
        QMessageBox::warning(this, "Fehler", "Bitte geben Sie eine gültige Nr ein");
        ui->streetnr->setFocus();
        ui->streetnr->selectAll();
        return false;
    }

    //Überprüfung des Ortes
    if(comboBoxOrt->currentIndex() == -1) {
        QMessageBox::warning(this, "Fehler", "Bitte wählen Sie ein Ort aus.");
        comboBoxOrt->setFocus();
        return false;
    }

    //Überprüfung der Telefonnummer
    if(!phone.contains(regexPhone)) {
        QMessageBox::warning(this, "Fehler", "Bitte geben Sie eine gültige Telefonnummer ein (mindestens 5 Ziffern).");
        ui->phone->setFocus();
        ui->phone->selectAll();
        return false;
    }

    //Überprüfung des Geburtsdatums
    if(!birthdate.isValid()) {
        QMessageBox::warning(this, "Fehler", "Bitte geben Sie ein gültiges Geburtsdatum ein.");
        ui->mail->setFocus();
        ui->mail->selectAll();
        return false;
    }

    //Überprüfung der Email
    if(!email.isEmpty()) {
        if(!email.contains(regexEmail)) {
            QMessageBox::warning(this, "Fehler", "Bitte geben Sie eine gültige E-Mail-Adresse ein.");
            ui->mail->setFocus();
            ui->mail->selectAll();
            return false;
        }
    }

    return true;
}

//Slot der aufgerufen wird wenn man auf einen Button in der Kundenliste klickt
void OverviewKunde::on_list_item_clicked(ListItem<Kunde>* item)
{
    //Auswählen des geklickten Kunden
    SelectCustomer(item);
}

//Slot der aufgerufen wird wenn man auf den zurück Button klickt
void OverviewKunde::on_back_to_main_clicked()
{
    //Ruft die Funktion des Elternelements der Seite auf um zurück auf die Startseite zu gelangen
    this->m_parent->back_to_main();
}

//Slot der aufgerufen wird wenn man auf den speichern Button klickt
void OverviewKunde::on_save_clicked()
{
    //Abbruch der Funktion wenn die Eingabeüberprüfung fehlschlägt
    if(!VerifyInput()) {
        return;
    }

    bool created = false;

    //Überprüfung ob kein Kunde ausgewählt ist
    if(this->m_selectedCustomer == nullptr) {
        //Erstellung eines neuen Kunden-Ojektes
        Kunde* customer = new Kunde();

        //Erstelllung eines neuen Listeneintrags für den Kunden
        this->m_selectedCustomer = CreateCustomerItem(customer);

        //Zwischenspeichern das ein neuer Kunde erstellt wurde
        created = true;
    }

    //Speichern des ausgewählten oder neu erstellten Kunden
    SaveCustomer(created);
}

//Slot der aufgerufen wird wenn man auf den zurücksetzen Button klickt
void OverviewKunde::on_reset_clicked()
{
    //Überprüfen ob kein Kunde ausgewählt ist
    if(this->m_selectedCustomer == nullptr) {
        //Zurücksetzen der Formularfelder auf ihre Initialwerte und Abbruch der Funktion
        ClearForm();
        return;
    }

    //Wenn Kunde ausgewählt: Laden der uhrsprünglichen Kundendaten
    LoadCustomer(this->m_selectedCustomer->GetValue());
}

//Slot der aufgerufen wird wenn man auf den neu Button klickt
void OverviewKunde::on_create_clicked()
{
    //Zurücksetzen des ausgewählten Kunden
    m_selectedCustomer = nullptr;

    //Zurücksetzen der Formularfelder auf ihre Initialwerte
    ClearForm();

    //Deaktivieren der neu und löschen Buttons
    ui->create->setDisabled(true);
    ui->remove->setDisabled(true);
}


//Slot der aufgerufen wird wenn man auf den löschen Button klickt
void OverviewKunde::on_remove_clicked()
{
    //Zurücksetzen der Formularfelder auf ihre Initialwerte
    ClearForm();

    //Abbruch der Funktion wenn kein Kunde ausgewählt ist
    if(this->m_selectedCustomer == nullptr) return;

    //Löschen des Kunden aus der Kundenliste und der Datenbank
    DeleteCustomer();

    //Deaktivieren der neu und löschen Buttons
    ui->create->setDisabled(true);
    ui->remove->setDisabled(true);
}

//Slot der aufgerufen wird wenn der Wert des Ort-Drop-Down Menüs geändert wird
void OverviewKunde::on_ort_currentIndexChanged(int index)
{
    //Überprüfen ob der Veränderte Wert der Initialwert ist
    if(index == -1) {
        //Zurücksetzen des Postleitzahl Formularfeldes und Abbruch der Funktion
        ui->plz->clear();
        return;
    }

    //Auslesen der aktuell ausgewählten Ort_ID Wertes des Ort-Drop-Down Menüs
    int location = ui->ort->currentData().value<int>();

    //Laden der Postleitzahl anhand der Ort_ID und setzen des Formularfeldes
    ui->plz->setText(FetchPLZFromLocation(location));
}

