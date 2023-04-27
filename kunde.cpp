#include "kunde.h"
// Konstruktoren

Kunde::Kunde()
{

}

Kunde::Kunde(int id, int anrede, std::string name, std::string strasse,
             int hausnr, int ort, int telefon, std::string geburtsdatum,
             std::string email, std::string titel)
{
    this->id = id;
    setAnrede(anrede);
    setName(name);
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

void Kunde::setName(std::string name)
{
    this->name = name;
}

void Kunde::setStrasse(std::string strasse)
{
    this->strasse = strasse;
}

void Kunde::setHausNr(int hausnr)
{
    this->hausnummer = hausnr;
}

void Kunde::setOrt(int ort)
{
    this->ort = ort;
}

void Kunde::setTelefon(int telefon)
{
    this->telefon = telefon;
}

void Kunde::setGeburtsdatum(std::string geburtsdatum)
{
    this->geburtsdatum = geburtsdatum;
}

void Kunde::setEmail(std::string email)
{
    this->email = email;
}

void Kunde::setTitel(std::string titel)
{
    this->titel = titel;
}


// getter
int Kunde::getAnrede()
{
    return this->anrede;
}

std::string Kunde::getName()
{
    return this->name;
}

std::string Kunde::getStrasse()
{
    return this->strasse;
}

int Kunde::getHausNr()
{
    return this->hausnummer;
}

int Kunde::getOrt()
{
    return this->ort;
}

int Kunde::getTelefon()
{
    return this->telefon;
}

std::string Kunde::getGeburtsdatum()
{
    return this->getGeburtsdatum();
}

std::string Kunde::getEmail()
{
    return this->email;
}

std::string Kunde::getTitel()
{
    return this->titel;
}






