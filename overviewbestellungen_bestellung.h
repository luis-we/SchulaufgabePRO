#ifndef OVERVIEWBESTELLUNGEN_BESTELLUNG_H
#define OVERVIEWBESTELLUNGEN_BESTELLUNG_H

#include "mainwindow.h"
#include "overviewbestellungen_liste.h"
#include <QWidget>
#include "QSqlQueryModel"

namespace Ui {
class overviewbestellungen_bestellung;
}

class OverviewBestellungen;

class OverviewBestellungen_Bestellung : public QWidget
{
    Q_OBJECT

public:
    explicit OverviewBestellungen_Bestellung(int customerId, QStackedWidget* stack, QWidget *parent = nullptr);
    ~OverviewBestellungen_Bestellung();

private slots:
    void on_back_clicked();
    void searchArtikel(const QString& searchText);
    void on_orders_clicked();

    void on_hinzufugen_clicked(QString& artikelName, int& menge, double& preis, QString& artikelNetto);

private:
    Ui::overviewbestellungen_bestellung *ui;
    int m_customerId;
    QStackedWidget* m_stack;
    overviewbestellungen_liste* m_liste = nullptr;
};

#endif // OVERVIEWBESTELLUNGEN_BESTELLUNG_H
