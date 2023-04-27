#ifndef KUNDE_H
#define KUNDE_H

#include <string>

class Kunde
{
public:
    Kunde();
    Kunde(int id, int anrede, std::string name, std::string strasse,
          int hausnr, int ort, int telefon, std::string geburtsdatum,
          std::string email, std::string titel);

    void setAnrede(int anrede);
    void setName(std::string name);
    void setStrasse(std::string strasse);
    void setHausNr(int hausnr);
    void setOrt(int ort);
    void setTelefon(int telefon);
    void setGeburtsdatum(std::string geburtsdatum);
    void setEmail(std::string email);
    void setTitel(std::string titel);

    int getAnrede();
    std::string getName();
    std::string getStrasse();
    int getHausNr();
    int getOrt();
    int getTelefon();
    std::string getGeburtsdatum();
    std::string getEmail();
    std::string getTitel();

private:
    int id;
    int anrede;
    std::string name;
    std::string vorname;
    std::string strasse;
    int hausnummer;
    int ort;
    int telefon;
    std::string geburtsdatum;
    std::string email;
    std::string titel;

};



#endif // KUNDE_H
