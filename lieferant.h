#ifndef LIEFERANT_H
#define LIEFERANT_H

#include <QString>
#include <QDate>

//Szymichowski

// Definition der Klasse "lieferant". Diese Klasse repräsentiert einen Lieferanten
// in unserem Kontext mit diversen Attributen wie Name, Adresse und Kontaktinformationen.
class lieferant
{
    // Öffentliche Konstruktoren
    public:
        lieferant(); // Standardkonstruktor. Erstellt ein neues Objekt ohne Initialwerte.

        // Überladener Konstruktor. Erstellt ein neues Objekt mit vorgegebenen Initialwerten.
        lieferant(int id, int anrede, QString name, QString Ansprechpartner, QString strasse,
            QString hausnr, int ort, QString telefon);

        // Setter-Funktionen. Diese Methoden erlauben es uns, die Werte der privaten Attribute zu ändern.
        void setAnrede(int anrede); // Setzt die Anrede des Lieferanten.
        void setName(QString name); // Setzt den Namen des Lieferanten.
        void setAnsprechpartner(QString Ansprechpartner); // Setzt den Ansprechpartner des Lieferanten.
        void setStrasse(QString strasse); // Setzt die Straße des Lieferanten.
        void setHausNr(QString hausnr); // Setzt die Hausnummer des Lieferanten.
        void setOrt(int ort); // Setzt den Ort des Lieferanten.
        void setTelefon(QString telefon); // Setzt die Telefonnummer des Lieferanten.

        // Getter-Funktionen. Diese Methoden erlauben es uns, die aktuellen Werte der privaten Attribute abzurufen.
        int getID(); // Gibt die ID des Lieferanten zurück.
        int getAnrede(); // Gibt die Anrede des Lieferanten zurück.
        QString getName(); // Gibt den Namen des Lieferanten zurück.
        QString getAnsprechpartner(); // Gibt den Ansprechpartner des Lieferanten zurück.
        QString getStrasse(); // Gibt die Straße des Lieferanten zurück.
        QString getHausNr(); // Gibt die Hausnummer des Lieferanten zurück.
        int getOrt(); // Gibt den Ort des Lieferanten zurück.
        QString getTelefon(); // Gibt die Telefonnummer des Lieferanten zurück.

        // Methoden zur Bearbeitung eines Lieferanten.
        void updateLieferant(int anrede, QString name, QString Ansprechpartner, QString strasse, QString hausNr, int ort, QString telefon); // Aktualisiert die Daten eines existierenden Lieferanten.
        void updateLieferant(); // Überladene Version der obigen Methode, die keine Parameter akzeptiert.
        void saveLieferant(); // Speichert die aktuellen Daten des Lieferanten (z.B. in einer Datenbank).
        void deleteLieferant(); // Löscht die Daten eines Lieferanten.

    // Deklaration der privaten Variablen. Diese repräsentieren die Attribute, die jeder Lieferant haben sollte.
    private:
        int id; // Eindeutige Identifikationsnummer des Lieferanten.
        int anrede; // Anrede des Lieferanten (z.B. Herr, Frau, Dr., etc.).
        QString name; // Name des Lieferanten.
        QString Ansprechpartner; // Name des Ansprechpartners beim Lieferanten.
        QString strasse; // Straße, in der der Lieferant ansässig ist.
        QString hausnummer; // Hausnummer des Lieferanten.
        int ort; // Ort, in dem der Lieferant ansässig ist. Könnte durch eine spezifischere Klasse/Struktur ersetzt werden, die Stadt, Staat usw. enthält.
        QString telefon; // Telefonnummer des Lieferanten.

};


#endif // LIEFERANT_H