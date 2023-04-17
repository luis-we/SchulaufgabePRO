#ifndef OVERVIEWBESTELLUNGEN_H
#define OVERVIEWBESTELLUNGEN_H

#include "mainwindow.h"

#include <QWidget>

namespace Ui {
class OverviewBestellungen;
}

class OverviewBestellungen : public QWidget
{
    Q_OBJECT

public:
    explicit OverviewBestellungen(MainWindow* parent = nullptr);
    ~OverviewBestellungen();

private slots:
    void on_back_to_main_clicked();
    void searchCustomer(const QString& searchText);
    void on_next_button_clicked();

private:
    Ui::OverviewBestellungen* ui;

    MainWindow* parent;
};

#endif // OVERVIEWBESTELLUNGEN_H
