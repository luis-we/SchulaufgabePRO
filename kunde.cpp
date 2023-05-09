#include "kunde.h"
#include "qsqlquery.h"
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
}

void Kunde::deleteKunde()
{
    QSqlQuery query;
    query.prepare("DELETE FROM kunden WHERE ID_Kunde = :id");
    query.bindValue(":id", this->id);
    query.exec();
}







