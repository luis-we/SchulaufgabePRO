#include "artikel.h"
#include <QString>

// Konstruktoren
Artikel::Artikel()
{
    this->Artikelnummer = 0;
}

Artikel::Artikel(int Artikelnummer, int Lieferantenbestellnummer,
                 QString Artikelname, double Preis_Netto, int Lagerbestand,
                 int LieferantenID, QString Lieferant)
{
    this->Artikelnummer = Artikelnummer;
    setLieferantenbestellnummer(Lieferantenbestellnummer);
    setArtikelname(Artikelname);
    setPreis_Netto(Preis_Netto);
    setLagerbestand(Lagerbestand);
    setLieferantenID(LieferantenID);
    setLieferant(Lieferant);
}
