// overviewbestellungen_bestellung.cpp
#include "overviewbestellungen_bestellung.h"
#include "ui_overviewbestellungen_bestellung.h"
#include <QStackedWidget>
#include <QSqlQuery>
#include <QMessageBox>
#include <qlistwidget.h>
#include <mainwindow.h>
#include "qsqlerror.h"
#include "QSqlQueryModel"
#include <QtGui>


// Komplette Bestellung durchführen
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


/**
    * Zeigt alle Artikel in der TableView an, die den Suchtext enthalten
    * Zeilen sind aklickbar und ruft die Funktion onArtikelClicked auf
    * @param searchText
    */
void OverviewBestellungen_Bestellung::searchArtikel(const QString &searchText)
{
    if (searchText.length() < 3) {
        // Suche nicht starten, wenn weniger als 3 Buchstaben eingegeben wurden
        QStandardItemModel *model = new QStandardItemModel(0, 0); // Neues leeres Datenmodell erstellen
        ui->artikelListe->setModel(model); // Das neue Datenmodell der TableView zuweisen
        return;
    }

    QSqlQuery queryArtikel;
    queryArtikel.prepare("SELECT Artikelnummer, Artikelname, Lagerbestand, Preis_Netto FROM artikel WHERE Artikelname LIKE :artikel");
    queryArtikel.bindValue(":artikel", "%" + searchText + "%");

    if (!queryArtikel.exec()) {
        // Fehler beim Ausführen der Abfrage
        qDebug() << "Fehler beim Suchen nach Artikel:";
        qDebug() << queryArtikel.lastError().text();
        return;
    }

    // Fügen Sie jeden gefundenen Artikel zur Liste hinzu
    while (queryArtikel.next()) {
        QSqlQueryModel *modelArtikel = new QSqlQueryModel();
        modelArtikel->setQuery(queryArtikel);


        ui->artikelListe->setModel(modelArtikel);
        ui->artikelListe->resizeColumnsToContents();
        int columnCountA = modelArtikel->columnCount();
        int availableWidthA = ui->artikelListe->viewport()->width();
        int defaultColumnWidthA = availableWidthA / columnCountA;

        for (int i = 0; i < columnCountA; ++i) {
            ui->artikelListe->setColumnWidth(i, defaultColumnWidthA);
        }

        ui->artikelListe->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
        ui->artikelListe->horizontalHeader()->setMaximumSectionSize(availableWidthA);




        connect(ui->artikelListe, &QTableView::clicked, this, &OverviewBestellungen_Bestellung::onArtikelClicked);
    }

}


/**
 * Wird aufgerufen, wenn eine Zelle in der TableView artikelListe angeklickt wurde
 * @param index
*/

void OverviewBestellungen_Bestellung::onArtikelClicked(const QModelIndex &index)
{
    // Überprüfen, ob ein gültiger Index vorliegt
    if (index.isValid()) {
        // Zeile der ausgewählten Zelle abrufen
        int row = index.row();

        artikelID = ui->artikelListe->model()->data(ui->artikelListe->model()->index(row, 0)).toInt();
        artikelName = ui->artikelListe->model()->data(ui->artikelListe->model()->index(row, 1)).toString();
        lagerbestand = ui->artikelListe->model()->data(ui->artikelListe->model()->index(row, 2)).toInt();
        einzelPreis = ui->artikelListe->model()->data(ui->artikelListe->model()->index(row, 3)).toDouble();

        ui->artikelMenge->setMaximum(lagerbestand);
    }
}


/**
 * Wird aufgerufen, wenn der Button "Zurück" geklickt wurde
*/
void OverviewBestellungen_Bestellung::on_back_clicked()
{
    m_stack->setCurrentIndex(4);
}


/**
 * Wird aufgerufen, wenn der Button "bisherige Bestellungen" geklickt wurde
 * der Stack wird erweitert
*/
void OverviewBestellungen_Bestellung::on_orders_clicked()
{

    // prüfen, ob bereits ein Widget für die Bestellung existiert, wenn ja, löschen
    if (m_liste) {
        m_stack->removeWidget(m_liste);
        delete m_liste;
        m_liste = nullptr;
    }

    m_liste = new overviewbestellungen_liste(m_customerId, m_stack);
    m_stack->addWidget(m_liste);
    m_stack->setCurrentIndex(6);
}


/**
 * Die Artikel werden in den Warenkorb hinzugefügt
 * Prüfung auf Menge <= Lagerbestand
 * Prüfung auf Menge > 0
 * Prüfung auf Artikel bereits im Warenkorb, Anpassung der bisherigen Menge
 * 
 * Gesamtpreis wird berechnet
 * Entfernen Button des Artiekls wird hinzugefügt
 * 
*/
void OverviewBestellungen_Bestellung::on_hinzufugen_clicked()
{
    menge = ui->artikelMenge->value();

    QMessageBox *fehlerMenge = new QMessageBox();

    if (menge == 0) {
        fehlerMenge->setText("Menge darf nicht Null sein!");
        fehlerMenge->show();
        return;
    }





    // Setze die Artikelinformationen entsprechend in die Tabelle warenkorb ein
    QStandardItemModel *warenkorbModel = qobject_cast<QStandardItemModel*>(ui->warenkorb->model());
    if (!warenkorbModel) {
        warenkorbModel = new QStandardItemModel(this);
        ui->warenkorb->setModel(warenkorbModel);
        warenkorbModel->setHorizontalHeaderLabels(QStringList() << "Artikelnummer" << "Artikelname" << "Einzelpreis" << "Menge" << "Gesamtpreis" << "Entfernen");
    }

    // Prüfen, ob die Summe der Menge im Warenkorb und der neuen Menge den maximalen Lagerbestand übersteigt
    int mengeImWarenkorb = 0;
    if (warenkorbModel) {
        int rowCount = warenkorbModel->rowCount();
        for (int row = 0; row < rowCount; ++row) {
            QModelIndex artikelNameIndex = warenkorbModel->index(row, 1); // Spalte mit dem Artikelnamen
            QModelIndex mengeIndex = warenkorbModel->index(row, 3); // Spalte mit der Menge
            if (warenkorbModel->data(artikelNameIndex).toString() == artikelName) {
                mengeImWarenkorb += warenkorbModel->data(mengeIndex).toInt();
            }
        }
    }

    int verfuegbarerLagerbestand = lagerbestand - mengeImWarenkorb;
    if (menge > verfuegbarerLagerbestand) {
        // Menge auf den verfügbaren Lagerbestand begrenzen
        menge = verfuegbarerLagerbestand;


        // Warnung anzeigen
        fehlerMenge->setText("Nicht genügend Artikel vorrätig. Insgesamt vorrätig: " + QString::number(lagerbestand) + " Stück");
        fehlerMenge->show();
        return;
    }

    preis = einzelPreis * menge;
    gesamtPreis += preis;

    // Überprüfen, ob der Artikel bereits im Warenkorb vorhanden ist
    bool artikelVorhanden = false;
    int rowCount = warenkorbModel->rowCount();
    for (int row = 0; row < rowCount; ++row) {
        QModelIndex index = warenkorbModel->index(row, 1); // Spalte mit dem Artikelnamen
        if (warenkorbModel->data(index).toString() == artikelName) {
            // Artikel bereits im Warenkorb gefunden
            artikelVorhanden = true;

            // Menge und Preis aktualisieren
            QModelIndex mengeIndex = warenkorbModel->index(row, 3); // Spalte mit der Menge
            int vorhandeneMenge = warenkorbModel->data(mengeIndex).toInt();
            int neueMenge = vorhandeneMenge + menge;
            warenkorbModel->setData(mengeIndex, neueMenge);

            QModelIndex preisIndex = warenkorbModel->index(row, 4); // Spalte mit dem Gesamtpreis
            double vorhandenerPreis = warenkorbModel->data(preisIndex).toDouble();
            double neuerPreis = vorhandenerPreis + preis;
            warenkorbModel->setData(preisIndex, neuerPreis);

            break;
        }
    }

    if (!artikelVorhanden) {
        // Artikel ist noch nicht im Warenkorb, neuen Eintrag hinzufügen
        QList<QStandardItem*> rowData;
        rowData << new QStandardItem(QString::number(artikelID));
        rowData << new QStandardItem(artikelName);
        rowData << new QStandardItem(QString::number(einzelPreis));
        rowData << new QStandardItem(QString::number(menge));
        rowData << new QStandardItem(QString::number(preis));
        rowData << new QStandardItem();


        warenkorbModel->appendRow(rowData);

        // erstelle Löschen-Button am Ende der Zeile, um den Artikel dann aus dem Warenkorb zu entfernen
        QPushButton *deleteButton = new QPushButton("Löschen");
        ui->warenkorb->setIndexWidget(rowData.at(5)->index(), deleteButton);

        connect(deleteButton, &QPushButton::clicked, [=]() {
            // Artikel aus dem Warenkorb entfernen
            warenkorbModel->removeRow(rowData.at(5)->index().row());

            // Gesamtpreis aktualisieren
            gesamtPreis -= preis;
            ui->gesamtPreis->setText(QString::number(gesamtPreis));
        });
    }

    // Warenkorb-Tabelle anpassen
    ui->warenkorb->resizeColumnsToContents();

    int columnCount = warenkorbModel->columnCount();
    int availableWidth = ui->warenkorb->viewport()->width();
    int defaultColumnWidth = availableWidth / columnCount;

    for (int i = 0; i < columnCount; ++i) {
        ui->warenkorb->setColumnWidth(i, defaultColumnWidth);
    }

    ui->gesamtPreis->setText(QString::number(gesamtPreis));


}


/**
 * Bestellung wird in die Datenbank eingetragen
 * MessageBox für erfolgreiche Bestellung
 * 
*/
void OverviewBestellungen_Bestellung::on_bestellen_clicked()
{
    QSqlQuery queryBestellung;
    queryBestellung.prepare("INSERT INTO `bestellungen` (`ID_Kunde`) VALUES (:m_customerId);");
    queryBestellung.bindValue(":m_customerId", m_customerId);
    queryBestellung.exec();

    // Erstelle das Query, um die Tabelle `bestellungen` abzurufen
    QSqlQuery queryBestellungen;
    queryBestellungen.prepare("SELECT ID_Bestellung FROM bestellungen WHERE ID_Kunde = :m_customerId ORDER BY Bestelldatum DESC LIMIT 1");
    queryBestellungen.bindValue(":m_customerId", m_customerId);

    // Führe das Query aus
    if (!queryBestellungen.exec()) {
        // Fehler beim Ausführen des Querys
        qDebug() << "Fehler beim Abrufen der Bestellungen:";
        qDebug() << queryBestellungen.lastError().text();
        return;
    }

    int idBestellung = 0;

    // Überprüfe, ob mindestens eine Bestellung gefunden wurde
    if (queryBestellungen.next()) {
        // Speichere die ID_Bestellung in einer Variablen
        idBestellung = queryBestellungen.value("ID_Bestellung").toInt();

        // Verwende die ID_Bestellung wie gewünscht
        qDebug() << "ID_Bestellung: " << idBestellung;
    } else {
        // Keine Bestellung für den Kunden gefunden
        qDebug() << "Keine Bestellung gefunden";
        return;
    }

    // Überprüfe, ob ein Warenkorb vorhanden ist
    QStandardItemModel *warenkorbModel = qobject_cast<QStandardItemModel*>(ui->warenkorb->model());
    if (!warenkorbModel) {
        // Message box alert "Füge Artikel dem Warenkorb hinzu"
        QMessageBox *leererWarenkorb = new QMessageBox();
        leererWarenkorb->setText("Füge Artikel dem Warenkorb hinzu");
        leererWarenkorb->show();
        return;
    }


    // Durchlaufe den Warenkorb und füge die Einträge in die Tabelle "zuordnung Bestellung" ein
    int rowCount = warenkorbModel->rowCount();
    for (int row = 0; row < rowCount; ++row) {
        QModelIndex aritkelIDIndex = warenkorbModel->index(row, 0); // Spalte mit ArtikelID
        QModelIndex artikelNameIndex = warenkorbModel->index(row, 1); // Spalte mit dem Artikelnamen
        QModelIndex mengeIndex = warenkorbModel->index(row, 3); // Spalte mit der Menge

        QString artikelName = warenkorbModel->data(artikelNameIndex).toString();
        artikelID = warenkorbModel->data(aritkelIDIndex).toInt();
        int menge = warenkorbModel->data(mengeIndex).toInt();


        // Füge den Eintrag in die Tabelle "zuordnung Bestellung" ein
        QSqlQuery queryZuordnung;
        queryZuordnung.prepare("INSERT INTO `zuordnung_bestellungen_artikel`(`ID_Bestellung`, `ID_Artikel`, `Menge`) VALUES (:idBestellung, :artikelID, :menge)");
        queryZuordnung.bindValue(":idBestellung", idBestellung);
        queryZuordnung.bindValue(":artikelID", artikelID);
        queryZuordnung.bindValue(":menge", menge);
        queryZuordnung.exec();


        // Ändere den Lagerbestand für die Artikel, die bestellt wurden
        QSqlQuery queryLagerbestand;
        queryLagerbestand.prepare("UPDATE artikel SET Lagerbestand = Lagerbestand - :menge WHERE Artikelnummer = :artikelID");
        queryLagerbestand.bindValue(":menge", menge);
        queryLagerbestand.bindValue(":artikelID", artikelID);
        queryLagerbestand.exec();

    }

    QMessageBox *erfolgBestellung = new QMessageBox();
    erfolgBestellung->setText("Herzlichen Glückwunsch, der Kladeradatsch ist Bestellt");
    erfolgBestellung->show();

    // Lösche den Warenkorb
    ui->warenkorb->model()->deleteLater();

    // Setze den Gesamtpreis auf 0
    gesamtPreis = 0;
    ui->gesamtPreis->setText(0);

    // Leere das Artikel auswählen-Feld und setze den Lagerbestand auf 0
    ui->artikelListe->clearSelection();
    ui->artikelMenge->setValue(0);
    lagerbestand = 0;

}



