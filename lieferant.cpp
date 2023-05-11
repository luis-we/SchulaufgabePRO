#include "lieferant.h"
#include <QString>
#include "qsqlquery.h"

using namespace std;

// Konstruktoren
lieferant::lieferant()
{
    this->id = 0;
}

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

// 
void lieferant::updateLieferant(int anrede, QString name, QString Ansprechpartner, QString strasse, QString hausNr, int ort, QString telefon)
{
    QVariant nullVariant = QVariant::fromValue<QString>(QString());
    nullVariant.clear();

    QSqlQuery query;

    //
    query.prepare("UPDATE lieferant SET "   //ANPASSEN!!
                  "Anrede = :anrede, "
                  "Name = :name, "
                  "Vorname = :Ansprechpartner, "
                  "Straße = :strasse, "
                  "Hausnummer = :hausnr, "
                  "ID_Ort = :ort, "
                  "Telefon = :telefon, "
                  "WHERE ID_Lieferant = :lieferant");

    //
    query.bindValue(":anrede", anrede);
    query.bindValue(":name", name);
    query.bindValue(":vorname", Ansprechpartner);
    query.bindValue(":strasse", strasse);
    query.bindValue(":hausnr", hausNr);
    query.bindValue(":ort", ort);
    query.bindValue(":telefon", telefon);
    query.bindValue(":lieferant", this->id);

    //
    query.exec();
}

//
void lieferant::updateLieferant()
{
    // 
    this->updateLieferant(this->anrede, this->name, this->Ansprechpartner, this->strasse, this->hausnummer, this->ort, this->telefon);
}

//
void lieferant::saveLieferant()
{
    QVariant nullVariant = QVariant::fromValue<QString>(QString());
    nullVariant.clear();

    QSqlQuery query;

    query.prepare("INSERT INTO lieferant"
                  "(Anrede, Name, Vorname, Straße, Hausnummer, ID_Ort, Telefon) " //ANPASSEN!!
                  "VALUES(:anrede, :name, :Ansprechpartner, :strasse,"
                  ":hausnr, :ort, :telefon)");

    //
    query.bindValue(":anrede", this->anrede);
    query.bindValue(":name", this->name);
    query.bindValue(":Ansprechpartner", this->Ansprechpartner);
    query.bindValue(":strasse", this->strasse);
    query.bindValue(":hausnr", this->hausnummer);
    query.bindValue(":ort", this->ort);
    query.bindValue(":telefon", this->telefon);

    query.exec();

    this->id = query.lastInsertId().toInt();

}

void lieferant::deleteLieferant()
{
    //
    QSqlQuery query;
    query.prepare("DELETE FROM lieferant WHERE ID_Lieferant = :id");
    query.bindValue(":id", this->id);
    query.exec();
}

