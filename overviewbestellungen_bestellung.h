#ifndef OVERVIEWBESTELLUNGEN_BESTELLUNG_H
#define OVERVIEWBESTELLUNGEN_BESTELLUNG_H

#include <QWidget>

namespace Ui {
class overviewbestellungen_bestellung;
}

class OverviewBestellungen;

class OverviewBestellungen_Bestellung : public QWidget
{
    Q_OBJECT

public:
    explicit OverviewBestellungen_Bestellung(int customerId);
    ~OverviewBestellungen_Bestellung();

private slots:
    void on_back_clicked();

private:
    Ui::overviewbestellungen_bestellung *ui;
    int m_customerId;
    OverviewBestellungen *m_parent;
};

#endif // OVERVIEWBESTELLUNGEN_BESTELLUNG_H
