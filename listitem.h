#ifndef LISTITEM_H
#define LISTITEM_H

#include <QPushButton>

//Generische Klasse zum Speichern eines Typunabhängigen Objektes im zusammenhang mit einem Button
template<class T>
class ListItem
{
//Deklaration der öffentlischen Funktionen
public:
    //Konstruktor zum Initialisieren der Werte
    ListItem(T* value, QPushButton* button)
    {
        m_value = value;
        m_button = button;
    }

    //Destruktor zum Löschen der gespeicherten Werte
    ~ListItem()
    {
        delete m_value;
        delete m_button;
    }

    //Getter für den Generischen Wert
    T* GetValue()
    {
        return this->m_value;
    }

    //Getter für den Button
    QPushButton* GetButton()
    {
        return this->m_button;
    }

//Deklaration der privaten Variablen
private:
    T* m_value;
    QPushButton* m_button;
};

#endif // LISTITEM_H
