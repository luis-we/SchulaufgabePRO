#ifndef OVERVIEWKUNDE_H
#define OVERVIEWKUNDE_H

#include "mainwindow.h"

#include <QWidget>

namespace Ui {
class OverviewKunde;
}

class OverviewKunde : public QWidget
{
    Q_OBJECT

public:
    explicit OverviewKunde(MainWindow* parent = nullptr);
    ~OverviewKunde();

private slots:
    void on_back_to_main_clicked();

private:
    Ui::OverviewKunde* ui;

    MainWindow* parent;
};

#endif // OVERVIEWKUNDE_H
