#include "kunde.h"
#include <QString>

// Konstruktoren
Kunde::Kunde()
{

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
int Kunde::getID()
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

QString Kunde::getDisplayText()
{
    return this->name + " " + this->vorname;
}






