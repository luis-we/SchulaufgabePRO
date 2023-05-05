#ifndef KUNDE_H
#define KUNDE_H

#include <string>

using namespace std;

class Kunde
{
public:
    Kunde();
    Kunde(int id, int anrede, string name, string strasse,
          int hausnr, int ort, int telefon, string geburtsdatum,
          string email, string titel);

    void setAnrede(int anrede);
    void setName(string name);
    void setStrasse(string strasse);
    void setHausNr(int hausnr);
    void setOrt(int ort);
    void setTelefon(int telefon);
    void setGeburtsdatum(string geburtsdatum);
    void setEmail(string email);
    void setTitel(string titel);

    int getAnrede();
    string getName();
    string getStrasse();
    int getHausNr();
    int getOrt();
    int getTelefon();
    string getGeburtsdatum();
    string getEmail();
    string getTitel();

    void updateKunde(int anrede, string name, string vorname, string strasse, int hausNr, int ort, int telefon, string geburtsdatum, string email, string titel);
    void updateKunde();
    void saveKunde();
    void deleteKunde();

private:
    int id;
    int anrede;
    string name;
    string vorname;
    string strasse;
    int hausnummer;
    int ort;
    int telefon;
    string geburtsdatum;
    string email;
    string titel;

};



#endif // KUNDE_H
