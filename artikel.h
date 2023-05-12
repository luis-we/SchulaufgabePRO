#ifndef ARTIKEL_H
#define ARTIKEL_H

#include <QString>
#include <QDate>

class Artikel
{
public:
    Artikel();
    Artikel(int Artikelnummer, int Lieferantenbestellnummer, QString Artikelname, double Preis_Netto, int Lagerbestand, int LieferantenID, QString Lieferant);

    int getArtikelnummer() const;
    void setArtikelnummer(int newArtikelnummer);

    int getLieferantenbestellnummer() const;
    void setLieferantenbestellnummer(int newLieferantenbestellnummer);

    const QString &getArtikelname() const;
    void setArtikelname(const QString &newArtikelname);

    double getPreis_Netto() const;
    void setPreis_Netto(double newPreis_Netto);

    int getLagerbestand() const;
    void setLagerbestand(int newLagerbestand);

    int getLieferantenID() const;
    void setLieferantenID(int newLieferantenID);

    const QString &getLieferant() const;
    void setLieferant(const QString &newLieferant);

private:

    int Artikelnummer;
    int Lieferantenbestellnummer;
    QString Artikelname;
    double Preis_Netto;
    int Lagerbestand;
    int LieferantenID;
    QString Lieferant;

};

// Setter und Getter
inline int Artikel::getArtikelnummer() const
{
    return Artikelnummer;
}

inline void Artikel::setArtikelnummer(int newArtikelnummer)
{
    Artikelnummer = newArtikelnummer;
}

inline int Artikel::getLieferantenbestellnummer() const
{
    return Lieferantenbestellnummer;
}

inline void Artikel::setLieferantenbestellnummer(int newLieferantenbestellnummer)
{
    Lieferantenbestellnummer = newLieferantenbestellnummer;
}

inline const QString &Artikel::getArtikelname() const
{
    return Artikelname;
}

inline void Artikel::setArtikelname(const QString &newArtikelname)
{
    Artikelname = newArtikelname;
}

inline double Artikel::getPreis_Netto() const
{
    return Preis_Netto;
}

inline void Artikel::setPreis_Netto(double newPreis_Netto)
{
    Preis_Netto = newPreis_Netto;
}

inline int Artikel::getLagerbestand() const
{
    return Lagerbestand;
}

inline void Artikel::setLagerbestand(int newLagerbestand)
{
    Lagerbestand = newLagerbestand;
}

inline int Artikel::getLieferantenID() const
{
    return LieferantenID;
}

inline void Artikel::setLieferantenID(int newLieferantenID)
{
    LieferantenID = newLieferantenID;
}

inline const QString &Artikel::getLieferant() const
{
    return Lieferant;
}

inline void Artikel::setLieferant(const QString &newLieferant)
{
    Lieferant = newLieferant;
}



#endif // ARTIKEL_H
