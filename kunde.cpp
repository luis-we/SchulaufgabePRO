#include "kunde.h"
#include "qmessagebox.h"
#include "qsqlquery.h"
#include <QString>
#include <QDate>

using namespace std;

// Konstruktoren
Kunde::Kunde()
{
    this->id = 0;
}

Kunde::Kunde(int id, int anrede, QString name, QString vorname, QString strasse,
             QString hausnr, int ort, QString telefon, QDate geburtsdatum,
             QString email, QString titel)
{
    this->id = id;
    setAnrede(anrede);
    setName(name);
    setVorname(vorname);
    setStrasse(strasse);
    setHausNr(hausnr);
    setOrt(ort);
    setTelefon(telefon);
    setGeburtsdatum(geburtsdatum);
    setEmail(email);
    setTitel(titel);
}

// setter
void Kunde::setAnrede(int anrede)
{
    this->anrede = anrede;
}

void Kunde::setName(QString name)
{
    this->name = name;
}

void Kunde::setVorname(QString vorname)
{
    this->vorname = vorname;
}

void Kunde::setStrasse(QString strasse)
{
    this->strasse = strasse;
}

void Kunde::setHausNr(QString hausnr)
{
    this->hausnummer = hausnr;
}

void Kunde::setOrt(int ort)
{
    this->ort = ort;
}

void Kunde::setTelefon(QString telefon)
{
    this->telefon = telefon;
}

void Kunde::setGeburtsdatum(QDate geburtsdatum)
{
    this->geburtsdatum = geburtsdatum;
}

void Kunde::setEmail(QString email)
{
    this->email = email;
}

void Kunde::setTitel(QString titel)
{
    this->titel = titel;
}


// getter
int Kunde::getId()
{
    return this->id;
}

int Kunde::getAnrede()
{
    return this->anrede;
}

QString Kunde::getName()
{
    return this->name;
}

QString Kunde::getVorname()
{
    return this->vorname;
}

QString Kunde::getStrasse()
{
    return this->strasse;
}

QString Kunde::getHausNr()
{
    return this->hausnummer;
}

int Kunde::getOrt()
{
    return this->ort;
}

QString Kunde::getTelefon()
{
    return this->telefon;
}

QDate Kunde::getGeburtsdatum()
{
    return this->geburtsdatum;
}

QString Kunde::getEmail()
{
    return this->email;
}

QString Kunde::getTitel()
{
    return this->titel;
}

// sql functions
void Kunde::updateKunde(int anrede, QString name, QString vorname, QString strasse, QString hausNr, int ort, QString telefon, QDate geburtsdatum, QString email, QString titel)
{
    QSqlQuery query;

    query.prepare("UPDATE kunden SET"
                  "Anrede = :anrede,"
                  "Name = :name,"
                  "Vorname = :vorname,"
                  "Straße = :strasse,"
                  "Hausnummer = :hausnr,"
                  "ID_Ort = :ort,"
                  "Telefon = :telefon,"
                  "Geburtsdatum = :geb,"
                  "Email = :email,"
                  "Titel = :titel"
                  "WHERE ID_Kunde = :kunde");
    query.bindValue(":anrede", anrede);
    query.bindValue(":name", name);
    query.bindValue(":vorname", vorname);
    query.bindValue(":strasse", strasse);
    query.bindValue(":hausnr", hausNr);
    query.bindValue(":ort", ort);
    query.bindValue(":telefon", telefon);
    query.bindValue(":geb", geburtsdatum);
    query.bindValue(":email", email);
    query.bindValue(":titel", titel);
    query.bindValue(":kunde", this->id);

    query.exec();
}

void Kunde::updateKunde()
{
    this->updateKunde(this->anrede, this->name, this->vorname, this->strasse, this->hausnummer, this->ort, this->telefon, this->geburtsdatum, this->email, this->titel);
}

void Kunde::saveKunde()
{
    QSqlQuery query;
    query.prepare("INSERT INTO kunden"
                  "(Anrede, Name, Vorname, Straße, Hausnummer, ID_Ort, Telefon, "
                  "Geburtsdatum, Email, Titel) VALUES("
                  ":anrede, :name, :vorname, :strasse,"
                  ":hausnr, :ort, :telefon, :geb, "
                  ":email, :titel)");

    query.bindValue(":anrede", this->anrede);
    query.bindValue(":name", this->name);
    query.bindValue(":vorname", this->vorname);
    query.bindValue(":strasse", this->strasse);
    query.bindValue(":hausnr", this->hausnummer);
    query.bindValue(":ort", this->ort);
    query.bindValue(":telefon", this->telefon);
    query.bindValue(":geb", this->geburtsdatum);
    query.bindValue(":email", this->email);
    query.bindValue(":titel", this->titel);

    query.exec();

    this->id = query.lastInsertId().toInt();

}

void Kunde::deleteKunde()
{
    QSqlQuery query;
    query.prepare("DELETE FROM kunden WHERE ID_Kunde = :id");
    query.bindValue(":id", this->id);
    query.exec();
}


QString Kunde::getDisplayText()
{
    return this->name + " " + this->vorname;
}






