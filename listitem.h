#ifndef LISTITEM_H
#define LISTITEM_H

#include <QPushButton>

template<class T>
class ListItem
{
public:
    ListItem(T* value, QPushButton* button)
    {
        m_value = value;
        m_button = button;
    }

    T* GetValue()
    {
        return this->m_value;
    }

    QPushButton* GetButton()
    {
        return this->m_button;
    }

private:
    T* m_value;
    QPushButton* m_button;
};

#endif // LISTITEM_H
