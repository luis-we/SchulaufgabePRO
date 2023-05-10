#ifndef OVERVIEWBESTELLUNGEN_LISTE_H
#define OVERVIEWBESTELLUNGEN_LISTE_H

#include "qstackedwidget.h"
#include <QWidget>

namespace Ui {
class overviewbestellungen_liste;
}

class overviewbestellungen_liste : public QWidget
{
    Q_OBJECT

public:
    explicit overviewbestellungen_liste(int customerId, QStackedWidget *stack, QWidget *parent = nullptr);
    ~overviewbestellungen_liste();

private slots:
    void on_back_clicked();

private:
    Ui::overviewbestellungen_liste *ui;
    int m_customerId;
    QStackedWidget *m_stack;
};

#endif // OVERVIEWBESTELLUNGEN_LISTE_H
