#ifndef KUNDE_H
#define KUNDE_H

#include <QString>
#include <QDate>

class Kunde
{
public:
    Kunde();
    Kunde(int id, int anrede, QString name, QString vorname, QString strasse,
          QString hausnr, int ort, QString telefon, QDate geburtsdatum,
          QString email, QString titel);

    void setAnrede(int anrede);
    void setName(QString name);
    void setVorname(QString vorname);
    void setStrasse(QString strasse);
    void setHausNr(QString hausnr);
    void setOrt(int ort);
    void setTelefon(QString telefon);
    void setGeburtsdatum(QDate geburtsdatum);
    void setEmail(QString email);
    void setTitel(QString titel);

    int getID();
    int getAnrede();
    QString getName();
    QString getVorname();
    QString getStrasse();
    QString getHausNr();
    int getOrt();
    QString getTelefon();
    QDate getGeburtsdatum();
    QString getEmail();
    QString getTitel();

    QString getDisplayText();

private:
    int id;
    int anrede;
    QString name;
    QString vorname;
    QString strasse;
    QString hausnummer;
    int ort;
    QString telefon;
    QDate geburtsdatum;
    QString email;
    QString titel;

};



#endif // KUNDE_H
