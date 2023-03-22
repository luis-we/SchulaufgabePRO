#ifndef OVERVIEWARTIKEL_H
#define OVERVIEWARTIKEL_H

#include "mainwindow.h"

#include <QWidget>

namespace Ui {
class OverviewArtikel;
}

class OverviewArtikel : public QWidget
{
    Q_OBJECT

public:
    explicit OverviewArtikel(MainWindow* parent = nullptr);
    ~OverviewArtikel();

private slots:
    void on_back_to_main_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::OverviewArtikel* ui;

    MainWindow* parent;
};

#endif // OVERVIEWARTIKEL_H
