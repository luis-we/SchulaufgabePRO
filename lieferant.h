#ifndef LIEFERANT_H
#define LIEFERANT_H

#include <QString>
#include <QDate>

class lieferant
{
public:
    lieferant();
    lieferant(int id, int anrede, QString name, QString Ansprechpartner, QString strasse,
          QString hausnr, int ort, QString telefon);



    void setAnrede(int anrede);
    void setName(QString name);
    void setAnsprechpartner(QString Ansprechpartner);
    void setStrasse(QString strasse);
    void setHausNr(QString hausnr);
    void setOrt(int ort);
    void setTelefon(QString telefon);

    int getID();
    int getAnrede();
    QString getName();
    QString getAnsprechpartner();
    QString getStrasse();
    QString getHausNr();
    int getOrt();
    QString getTelefon();

private:
    int id;
    int anrede;
    QString name;
    QString Ansprechpartner;
    QString strasse;
    QString hausnummer;
    int ort;
    QString telefon;

};



#endif // LIEFERANT_H
