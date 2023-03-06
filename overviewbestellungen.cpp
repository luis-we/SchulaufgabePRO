#include "overviewbestellungen.h"
#include "ui_overviewbestellungen.h"

#include "mainwindow.h"

OverviewBestellungen::OverviewBestellungen(MainWindow* parent) : QWidget(parent), ui(new Ui::OverviewBestellungen)
{
    ui->setupUi(this);

    this->parent = parent;
}

OverviewBestellungen::~OverviewBestellungen()
{
    delete ui;
}

void OverviewBestellungen::on_back_to_main_clicked()
{
   this->parent->back_to_main();
}

