#include "lieferant.h"
#include <QString>
#include "qsqlquery.h"

using namespace std;

// Konstruktor ohne Parameter
lieferant::lieferant()
{
    this->id = 0;
}

// Konstruktor mit Parametern
lieferant::lieferant(int id, int anrede, QString name, QString Ansprechpartner, QString strasse,
             QString hausnr, int ort, QString telefon)
{
    this->id = id;
    setAnrede(anrede);
    setName(name);
    setAnsprechpartner(Ansprechpartner);
    setStrasse(strasse);
    setHausNr(hausnr);
    setOrt(ort);
    setTelefon(telefon);
}

// Setterfunktionen 
void lieferant::setAnrede(int anrede)
{this->anrede = anrede;}

void lieferant::setAnsprechpartner(QString Ansprechpartner)
{this->Ansprechpartner = Ansprechpartner;}

void lieferant::setStrasse(QString strasse)
{this->strasse = strasse;}

void lieferant::setHausNr(QString hausnr)
{this->hausnummer = hausnr;}

void lieferant::setName(QString name)
{this->name = name;}

void lieferant::setOrt(int ort)
{this->ort = ort;}

void lieferant::setTelefon(QString telefon)
{this->telefon = telefon;}


// Getterfunktionen
int lieferant::getID()
{return this->id;}

int lieferant::getAnrede()
{return this->anrede;}

QString lieferant::getName()
{return this->name;}

QString lieferant::getAnsprechpartner()
{return this->Ansprechpartner;}

QString lieferant::getStrasse()
{return this->strasse;}

QString lieferant::getHausNr()
{return this->hausnummer;}

int lieferant::getOrt()
{return this->ort;}

QString lieferant::getTelefon()
{return this->telefon;}


// SQL FUNKTIONEN

// Fkt zum DB Update eines Lieferanten (mit Parametern)
void lieferant::updateLieferant(int anrede, QString name, QString Ansprechpartner, QString strasse, QString hausNr, int ort, QString telefon)
{
    // Löscht den Inhalt der QVariant-Variable "nullVariant"
    QVariant nullVariant = QVariant::fromValue<QString>(QString());
    nullVariant.clear();

    QSqlQuery query;

    // SQL-Query zum Update eines Lieferanten
    query.prepare("UPDATE lieferant SET "
                  "Anrede_Ansprechpartner = :anrede, "
                  "Lieferantenname = :name, "
                  "Ansprechpartner  = :Ansprechpartner, "
                  "Straße = :strasse, "
                  "Hausnummer = :hausnr, "
                  "ID_Ort = :ort, "
                  "Telefon = :telefon "
                  "WHERE ID_Lieferant = :lieferant");

    // Bindet die Parameter an die SQL-Query
    query.bindValue(":anrede", anrede);
    query.bindValue(":name", name);
    query.bindValue(":Ansprechpartner", Ansprechpartner);
    query.bindValue(":strasse", strasse);
    query.bindValue(":hausnr", hausNr);
    query.bindValue(":ort", ort);
    query.bindValue(":telefon", telefon);
    query.bindValue(":lieferant", this->id);

    
    // Führt die SQL-Query aus
    query.exec();
}

// Fkt zum DB Update eines Lieferanten (mit den Werten des Objekts)
void lieferant::updateLieferant()
{
    // Ruft die Methode "updateLieferant()" auf und übergibt Parameterwerte
    this->updateLieferant(this->anrede, this->name, this->Ansprechpartner, this->strasse, this->hausnummer, this->ort, this->telefon);
}

// Fkt zum DB Laden eines Lieferanten (mit Parametern)
void lieferant::saveLieferant()
{
    // Löscht den Inhalt der QVariant-Variable "nullVariant"
    QVariant nullVariant = QVariant::fromValue<QString>(QString());
    nullVariant.clear();

    // Erstellt ein QSqlQuery-Objekt
    QSqlQuery query;

    // SQL-Query zum Laden eines Lieferanten
    query.prepare("INSERT INTO lieferant"
                  "(Anrede_Ansprechpartner , Lieferantenname, Ansprechpartner, Straße, Hausnummer, ID_Ort, Telefon) "
                  "VALUES(:anrede, :name, :Ansprechpartner, :strasse, :hausnr, :ort, :telefon)");

    // Bindet die Parameter an die SQL-Query
    query.bindValue(":anrede", this->anrede);
    query.bindValue(":name", this->name);
    query.bindValue(":Ansprechpartner", this->Ansprechpartner);
    query.bindValue(":strasse", this->strasse);
    query.bindValue(":hausnr", this->hausnummer);
    query.bindValue(":ort", this->ort);
    query.bindValue(":telefon", this->telefon);

    // Weist Variable "id" als Ganzzahl konvertierten Wert von "lastInsertId()" zu
    this->id = query.lastInsertId().toInt();

    // Führt die SQL-Query aus
    query.exec();

}

// Fkt zum DB Löschen eines Lieferanten
void lieferant::deleteLieferant()
{
    // SQL Query + Bindung des Parameters + Ausführung
    QSqlQuery query;
    query.prepare("DELETE FROM lieferant WHERE ID_Lieferant = :id");
    query.bindValue(":id", this->id);
    query.exec();
}

