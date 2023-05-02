#include "overviewlieferanten.h"
#include "ui_overviewlieferanten.h"
#include "listitem.h"
#include "qsqlerror.h"

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
}

OverviewLieferanten::~OverviewLieferanten()
{
    delete ui; //Löscht UI wenn Fenster geschlossen wird
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
    query_insert.prepare("INSERT INTO lieferanten (Name, Adresse, Telefonnummer, Email) VALUES (:Name, :Anrede, :NameAnsprechpartner, :Telefon, :Straße, :Hausnummer, :Ort, :ID)");

    //Binden der Werte aus den Textfeldern an die SQL Abfrage
    query_insert.bindValue(":Name", ui->textBrowser_lieferantenname->toPlainText());
    query_insert.bindValue(":Andrede", ui->textBrowser_lieferantenandrede->toPlainText());
    query_insert.bindValue(":NameAnsprechpartner", ui->textBrowser_lieferantenansprechpartner->toPlainText());
    query_insert.bindValue(":Telefon", ui->textBrowser_lieferantentelefon->toPlainText());
    query_insert.bindValue(":Straße", ui->textBrowser_lieferantenstrasse->toPlainText());
    query_insert.bindValue(":Hausnummer", ui->textBrowser_lieferantenhsnr->toPlainText());
    query_insert.bindValue(":Ort", ui->textBrowser_lieferantenort->toPlainText());
    query_insert.bindValue(":ID", ui->textBrowser_lieferantenid->toPlainText());

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
    query_update.prepare("UPDATE lieferanten SET Name = :Name, Anrede = :Anrede, NameAnsprechpartner = :NameAnsprechpartner, Telefon = :Telefon, Straße = :Straße, Hausnummer = :Hausnummer, Ort = :Ort WHERE id = :ID");
    
    //Binden der Werte aus den Textfeldern an die SQL Abfrage
    query_update.bindValue(":Name", ui->textBrowser_lieferantenname->toPlainText());
    query_update.bindValue(":Andrede", ui->textBrowser_lieferantenandrede->toPlainText());
    query_update.bindValue(":NameAnsprechpartner", ui->textBrowser_lieferantenansprechpartner->toPlainText());
    query_update.bindValue(":Telefon", ui->textBrowser_lieferantentelefon->toPlainText());
    query_update.bindValue(":Straße", ui->textBrowser_lieferantenstrasse->toPlainText());
    query_update.bindValue(":Hausnummer", ui->textBrowser_lieferantenhsnr->toPlainText());
    query_update.bindValue(":Ort", ui->textBrowser_lieferantenort->toPlainText());
    query_update.bindValue(":ID", ui->textBrowser_lieferantenid->toPlainText());

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
    query_delete.prepare("DELETE FROM lieferanten WHERE id = :ID");

    query_delete.bindValue(":ID", ui->textBrowser_lieferantenid->toPlainText());

    query_delete.exec(); //Führt Query aus
    //Prüft ob Fehler beim SQL Querry auftreten und gibt Fehler aus
    if (!query_delete.exec()) {
        qDebug() << "Fehler beim LÖSCHEN eines Lieferanten: " << query_delete.lastError().text();
        return;
    }
}
