#include "overviewkunde.h"
#include "ui_overviewkunde.h"
#include "mainwindow.h"


OverviewKunde::OverviewKunde(MainWindow* parent) : QWidget(parent), ui(new Ui::OverviewKunde)
{
    ui->setupUi(this);

    this->parent = parent;
}

OverviewKunde::~OverviewKunde()
{
    delete ui;
}

void OverviewKunde::on_back_to_main_clicked()
{
    this->parent->back_to_main();
}


void OverviewKunde::on_save_clicked()
{

}


void OverviewKunde::on_reset_clicked()
{

}

