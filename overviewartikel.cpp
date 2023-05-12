#include "overviewartikel.h"
#include "ui_overviewartikel.h"
#include "listitem.h"
#include "qsqlerror.h"

#include <QSqlQuery>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QVariant>

OverviewArtikel::OverviewArtikel(MainWindow* parent) : QWidget(parent), ui(new Ui::OverviewArtikel)
{
    ui->setupUi(this);

    //Speichern des Elternelements
    this->parent = parent;

    //Erstellung des dynamischen Layouts für die Artikel Liste
    this->m_layout = new QVBoxLayout(this);

    //Erstellung des Vektors zum Speichern von Listeneinträgen der Artikel
    this->m_artikels = new vector<ListItem<Artikel>*>();

    //Initialisieren des ausgewählten Artikel
    this->m_selectedArtikel = nullptr;

    //Zuweisung des dynamischen Layouts für die Scroll Area
    ui->artikels->setLayout(this->m_layout);

    //Artikel laden
    LoadArticles();

    //Laden der Lieferanten
    LoadSuppliers();

    //Deaktivieren der Buttons
    ui->pushButtonAktualisieren->setDisabled(true);
    ui->pushButtonDelete->setDisabled(true);
    ui->pushButtonNeuanlegen->setDisabled(true);
    ui->pushButtonClear->setDisabled(true);

    //Zurücksetzen des Formulars
    ClearForm();
}

//Destructor der Artikel Seite
OverviewArtikel::~OverviewArtikel()
{
    delete ui;
}


//Lädt alle Lieferanten aus der Datenbank und fügt sie dem Drop-Down Menü hinzu
void OverviewArtikel::LoadSuppliers()
{
    QSqlQuery query;

    //Select Statement zum Lade der Lieferanten
    query.prepare("SELECT * FROM lieferant");

    //Überprüfung der Datenbank Abfrage
    if (!query.exec()) {
        qDebug() << "Fehler bei der Suchen nach Lieferanten: " << query.lastError().text();
        return;
    }

    //Schleifendurchlauf durch alle Anreden der Datenbank
    while (query.next()) {
        //Auslesen und Speichern der Werte
        int supplier_id = query.value("ID_Lieferant").toInt();
        QString supplier = query.value("Lieferantenname").toString();

        //Hinzufügen der Lieferanten in das Drop-Down Menü
        ui->comboBoxSuppliers->addItem(supplier, supplier_id);
    }
}

//Laden der Artikel aus der Datenbank
void OverviewArtikel::LoadArticles()
{
    QSqlQuery query;

    //Select Statement zum Lade der Artikel
    query.prepare("SELECT * FROM artikel");

    //Überprüfung der Datenbank Abfrage
    if (!query.exec()) {
        qDebug() << "Fehler bei der Suchen nach Artikel: " << query.lastError().text();
        return;
    }

    //Schleifendurchlauf zum Auslesen aller Artikel
    while (query.next()) {
        //Erstellung eines neuen Artikel-Objektes mit den Werten aus der Datenbank
        Artikel* artikel = new Artikel(
            query.value("Artikelnummer").toInt(),
            query.value("Lieferantenbestellnummer").toInt(),
            query.value("Artikelname").toString(),
            query.value("Preis_Netto").toDouble(),
            query.value("Lagerbestand").toInt(),
            query.value("Lieferant").toInt(),
            query.value("Lagerbestand").toString()
        );
        //Erstellen eines Listeneintrags des Artikels für die Artikelliste
        CreateArtikelItem(artikel);

    }
}

//Auswählen des Artikel
void OverviewArtikel::SelectArtikel(ListItem<Artikel>* artikel)
{
    //Abbruch bei wiederholten auswählen eines Artikel
    if(this->m_selectedArtikel == artikel) return;

    //Ausgewählten Artikel setzen
    this->m_selectedArtikel = artikel;

    //Artikeldetails in das Formular Laden
    LoadArticle(artikel->GetValue());

    //Buttons aktivieren
    ui->pushButtonAktualisieren->setDisabled(false);
    ui->pushButtonDelete->setDisabled(false);
    ui->pushButtonClear->setDisabled(false);
    ui->pushButtonNeuanlegen->setDisabled(false);
}

//Speichern der aktuellen Daten als neuen Artikel in die Datenbank
void OverviewArtikel::SaveArtikel()
{
    QVariant nullVariant = QVariant::fromValue<QString>(QString());
    nullVariant.clear();

    //SQL Insert zum hinzufügen des neuen Artikels
    QSqlQuery query;
    query.prepare("INSERT INTO artikel"
                  "(Artikelnummer, Lieferantenbestellnummer, Artikelname, Preis_Netto, Lagerbestand, Lieferant) VALUES("
                  ":artikelnummer, :lieferantenbestellnummer, :artikelname, :preis_Netto,"
                  ":lagerbestand, :lieferant)");

    query.bindValue(":lieferantenbestellnummer", ui->textBrowserLieferantenbestellnummer->toPlainText());
    query.bindValue(":artikelname", ui->textBrowserArtikelname->toPlainText());
    query.bindValue(":preis_Netto", ui->textBrowserNettoPreis->toPlainText());
    query.bindValue(":lagerbestand", ui->textBrowserLagerbestand->toPlainText());
    query.bindValue(":lieferant", ui->comboBoxSuppliers->currentData().value<int>());

    //Query ausführen
    query.exec();

    //Formular bereinigen
    ClearForm();

    //Artikel neu laden damit neuer Artikel angezeigt wird
    LoadArticles();
}

// Löscht einen Artikel aus der Datenbank
void OverviewArtikel::DeleteArticle()
{
    QSqlQuery query;

    //SQL Delete zum löschen eines Artikels
    query.prepare("DELETE FROM artikel WHERE `artikel`.`Artikelnummer` = " + QString::number(this->m_selectedArtikel->GetValue()->getArtikelnummer()));

    if (!query.exec()) {
        qDebug() << "Fehler bei der Löschung nach Artikel: " << query.lastError().text();
        return;
    }

    //Query ausführen
    query.exec();

    //Löscht den Artikel aus der Artikelliste
    delete m_selectedArtikel;
}

//Aktualisiert einen Artikel
void OverviewArtikel::UpdateArtikel()
{
    QVariant nullVariant = QVariant::fromValue<QString>(QString());
    nullVariant.clear();

    //SQL Update um einen Artikel in der Datenbank zu verändern
    QSqlQuery query;
    query.prepare("UPDATE artikel SET "
                  "Lieferantenbestellnummer = :lieferantenbestellnummer, "
                  "Artikelname = :artikelname, "
                  "Preis_Netto = :preis_Netto, "
                  "Lagerbestand = :lagerbestand, "
                  "Lieferant = :lieferant "
                  "WHERE artikel.artikelnummer = :artikelnummer");

    query.bindValue(":artikelnummer", this->m_selectedArtikel->GetValue()->getArtikelnummer());
    query.bindValue(":lieferantenbestellnummer", ui->textBrowserLieferantenbestellnummer->toPlainText());
    query.bindValue(":artikelname", ui->textBrowserArtikelname->toPlainText());
    query.bindValue(":preis_Netto", ui->textBrowserNettoPreis->toPlainText());
    query.bindValue(":lagerbestand", ui->textBrowserLagerbestand->toPlainText());
    query.bindValue(":lieferant", ui->comboBoxSuppliers->currentData().value<int>());

    //QMessageBox::warning(this, "Fehler", query.lastQuery());

    //Query ausführen
    query.exec();

    //Formualr bereinigen
    ClearForm();

    //Artikel neu laden um änderung anzuzeigen
    LoadArticles();

}

//Artikeldetails in das Formular laden
void OverviewArtikel::LoadArticle(Artikel* artikel) {
    ui->textBrowserLieferantenbestellnummer->setText(QString::number(artikel->getLieferantenbestellnummer()));
    ui->textBrowserArtikelname->setText(artikel->getArtikelname());
    ui->textBrowserNettoPreis->setText(QString::number(artikel->getPreis_Netto()));
    ui->textBrowserLagerbestand->setText(QString::number(artikel->getLagerbestand()));
    ui->comboBoxSuppliers->setCurrentIndex(ui->comboBoxSuppliers->findData(artikel->getLieferantenID()));
}

//Erstellen eines Listeneintrags vom Typ Artikel
ListItem<Artikel>* OverviewArtikel::CreateArtikelItem(Artikel* artikel)
{
    //Erstellung des Buttons für den Artikel
    QPushButton* button = new QPushButton(this);

    //Erstellung des Listeneintrages (Verknüpfung von Button und Artikel)
    ListItem<Artikel>* artikelItem = new ListItem<Artikel>(artikel, button);

    //Verbindung des On-Click Events des Buttons mit der Funktion zur übermittlung des Ausgewählten Artikel
    connect(button, &QPushButton::clicked, [this, artikelItem](){ this->on_list_item_clicked(artikelItem); });

    //Setzen des Button Textes auf den Namen des Artikel
    button->setText(artikel->getArtikelname());

    //Hinzugügen des Buttons in das Layout der Artikelliste
    this->m_layout->addWidget(button);

    //Hinzufügen des Listeneintrags in den Vector der Artikelliste
    this->m_artikels->push_back(artikelItem);

    //Rückgabe des Listeneintrages
    return artikelItem;
}

bool OverviewArtikel::VerifyInput() {

    //Auslesen der Formularfelder-Werte
    QString lieferantenbestellnummer = ui->textBrowserLieferantenbestellnummer->toPlainText();
    QString artikelname = ui->textBrowserArtikelname->toPlainText();
    QString nettopreis = ui->textBrowserNettoPreis->toPlainText();
    QString lagerbestand =ui->textBrowserLagerbestand->toPlainText();

    QRegularExpression regexName("[A-Za-z]{2,50}");
    QRegularExpression regexPreis("\\b(0*[1-9][0-9]*|0*\\.[0-9]*[1-9])\\b");
    QRegularExpression regexInt("\\b0*[0-9]{1,10}\\b");


    //Überprüfung des Titels
    if(!artikelname.isEmpty()) {
        if(!artikelname.contains(regexName)) {
            QMessageBox::warning(this, "Fehler", "Bitte geben Sie einen gültigen Artikelnamen ein.");
            ui->textBrowserArtikelname->setFocus();
            ui->textBrowserArtikelname->selectAll();
            return false;
        }
    }


    //Überprüfung der Lieferantenbestellnummer
    if(!lieferantenbestellnummer.isEmpty()) {
        if(!lieferantenbestellnummer.contains(regexInt)) {
            QMessageBox::warning(this, "Fehler", "Bitte geben Sie einen gültig Lieferantenbestellnummer ein.");
            ui->textBrowserLieferantenbestellnummer->setFocus();
            ui->textBrowserLieferantenbestellnummer->selectAll();
            return false;
        }
    }

    //Überprüfung des Lagerbestands
    if(!lagerbestand.isEmpty()) {
        if(!lagerbestand.contains(regexInt)) {
            QMessageBox::warning(this, "Fehler", "Bitte geben Sie einen gültigen Lagerbestand ein.");
            ui->textBrowserLagerbestand->setFocus();
            ui->textBrowserLagerbestand->selectAll();
            return false;
        }
    }

    //Überprüfung des Nettopreises
    if(!nettopreis.isEmpty()) {
        if(!nettopreis.contains(regexPreis)) {
            if(nettopreis.toDouble() < 0)
            {
                QMessageBox::warning(this, "Fehler", "Bitte geben Sie einen gültigen Nettopreis ein.");
                ui->textBrowserNettoPreis->setFocus();
                ui->textBrowserNettoPreis->selectAll();
                return false;
            }
        }
    }

    return true;
}

//Zurücksetzen des Formulares auf die Initialwerte
void OverviewArtikel::ClearForm() {
    ui->textBrowserLieferantenbestellnummer->clear();
    ui->textBrowserArtikelname->clear();
    ui->textBrowserNettoPreis->clear();
    ui->textBrowserLagerbestand->clear();
    ui->comboBoxSuppliers->setCurrentIndex(-1);

    ui->pushButtonAktualisieren->setDisabled(true);
    ui->pushButtonDelete->setDisabled(true);
    ui->pushButtonClear->setDisabled(true);
    ui->pushButtonNeuanlegen->setDisabled(true);
}

//Aufruf des zurück Buttons
void OverviewArtikel::on_back_to_main_clicked()
{
    this->parent->back_to_main();
}

//Slot der aufgerufen wird wenn man auf einen Button in der Artikelliste klickt
void OverviewArtikel::on_list_item_clicked(ListItem<Artikel>* item)
{
    //Auswählen des geklickten Artikel
    SelectArtikel(item);
}

//Slot der aufgerufen wird wenn man auf den löschen Button klickt
void OverviewArtikel::on_pushButtonDelete_clicked()
{
    //Abbruch der Funktion wenn kein Artikel ausgewählt ist
    if(this->m_selectedArtikel == nullptr) return;

    //Löscht den Artikel
    DeleteArticle();
}

//Slot der aufgerufen wird wenn man auf den neu anlegen Button klickt
void OverviewArtikel::on_pushButtonNeuanlegen_clicked()
{
    //Überprüft Eingabe
    if(!VerifyInput()) {
        return;
    }
    //Legt neuen Artikel an
    SaveArtikel();
}

//Slot der aufgerufen wird wenn man auf den Aktualisieren Button klickt
void OverviewArtikel::on_pushButtonAktualisieren_clicked()
{
    //Überprüft Eingabe
    if(!VerifyInput()) {
        return;
    }
    //Aktualisiert einen Artikel
    UpdateArtikel();
}

//Slot der aufgerufen wird wenn man auf den Zurücksetzen Button klickt
void OverviewArtikel::on_pushButtonClear_clicked()
{
    this->m_selectedArtikel = nullptr;

    ui->pushButtonClear->setDisabled(true);

    //Zurücksetzen der Formularfelder auf ihre Initialwerte
    ClearForm();
}

