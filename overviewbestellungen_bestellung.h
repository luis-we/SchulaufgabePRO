#ifndef OVERVIEWBESTELLUNGEN_BESTELLUNG_H
#define OVERVIEWBESTELLUNGEN_BESTELLUNG_H

#include <QWidget>

namespace Ui {
class overviewbestellungen_bestellung;
}

class overviewbestellungen_bestellung : public QWidget
{
    Q_OBJECT

public:
    explicit overviewbestellungen_bestellung(QWidget *parent = nullptr);
    ~overviewbestellungen_bestellung();

private:
    Ui::overviewbestellungen_bestellung *ui;
};

#endif // OVERVIEWBESTELLUNGEN_BESTELLUNG_H
