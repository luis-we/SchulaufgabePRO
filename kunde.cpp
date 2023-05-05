#include "kunde.h"
using namespace std;
// Konstruktoren

Kunde::Kunde()
{

}

Kunde::Kunde(int id, int anrede, string name, string strasse,
             int hausnr, int ort, int telefon, string geburtsdatum,
             string email, string titel)
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

void Kunde::setName(string name)
{
    this->name = name;
}

void Kunde::setStrasse(string strasse)
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

void Kunde::setGeburtsdatum(string geburtsdatum)
{
    this->geburtsdatum = geburtsdatum;
}

void Kunde::setEmail(string email)
{
    this->email = email;
}

void Kunde::setTitel(string titel)
{
    this->titel = titel;
}


// getter
int Kunde::getAnrede()
{
    return this->anrede;
}

string Kunde::getName()
{
    return this->name;
}

string Kunde::getStrasse()
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

string Kunde::getGeburtsdatum()
{
    return this->geburtsdatum;
}

string Kunde::getEmail()
{
    return this->email;
}

string Kunde::getTitel()
{
    return this->titel;
}

// sql functions
void Kunde::updateKunde(int anrede, string name, string vorname, string strasse, int hausNr, int ort, int telefon, string geburtsdatum, string email, string titel)
{
    string sql("UPDATE kunden SET "
               "Anrede = " + to_string(anrede) +
               ", Name = " + name +
               ", Vorname = " + vorname +
               ", Straße = " + strasse +
               ", Hausnummer = " + to_string(hausNr) +
               ", ID_Ort = " + to_string(ort) +
               ", Telefon = " + to_string(telefon) +
               ", Geburtsdatum = " + geburtsdatum +
               ", Email = " + email +
               ", Titel = " + titel +
               " WHERE ID_Kunde = " + to_string(this->id) + ";");
}

void Kunde::updateKunde()
{
    this->updateKunde(this->anrede, this->name, this->vorname, this->strasse, this->hausnummer, this->ort, this->telefon, this->geburtsdatum, this->email, this->titel);
}

void Kunde::saveKunde()
{
    string sql("INSERT INTO kunden "
               "(Anrede, Name, Vorname, Straße, Hausnummer, ID_Ort, Telefon, "
               "Geburtsdatum, Email, Titel) VALUES(" +
               to_string(this->anrede) + "," +
               this->name + "," +
               this->vorname + "," +
               this->strasse + "," +
               to_string(this->hausnummer) + "," +
               to_string(this->ort) + "," +
               to_string(this->telefon) + "," +
               this->geburtsdatum + "," +
               this->email + "," +
               this->titel + ");");
}

void Kunde::deleteKunde()
{
    string sql("DELETE FROM kunden WHERE ID_Kunde = " + to_string(this->id) + ";");
}







