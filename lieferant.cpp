#include "lieferant.h"
#include <QString>

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

// setter
void lieferant::setAnrede(int anrede)
{
    this->anrede = anrede;
}

void lieferant::setName(QString name)
{
    this->name = name;
}

void lieferant::setAnsprechpartner(QString Ansprechpartner)
{
    this->Ansprechpartner = Ansprechpartner;
}

void lieferant::setStrasse(QString strasse)
{
    this->strasse = strasse;
}

void lieferant::setHausNr(QString hausnr)
{
    this->hausnummer = hausnr;
}

void lieferant::setOrt(int ort)
{
    this->ort = ort;
}

void lieferant::setTelefon(QString telefon)
{
    this->telefon = telefon;
}



// getter
int lieferant::getID()
{
    return this->id;
}

int lieferant::getAnrede()
{
    return this->anrede;
}

QString lieferant::getName()
{
    return this->name;
}

QString lieferant::getAnsprechpartner()
{
    return this->Ansprechpartner;
}

QString lieferant::getStrasse()
{
    return this->strasse;
}

QString lieferant::getHausNr()
{
    return this->hausnummer;
}

int lieferant::getOrt()
{
    return this->ort;
}

QString lieferant::getTelefon()
{
    return this->telefon;
}






