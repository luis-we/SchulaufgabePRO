#include "overviewartikel.h"
#include "ui_overviewartikel.h"

OverviewArtikel::OverviewArtikel(MainWindow* parent) : QWidget(parent), ui(new Ui::OverviewArtikel)
{
    ui->setupUi(this);

    this->parent = parent;
}

OverviewArtikel::~OverviewArtikel()
{
    delete ui;
}

void OverviewArtikel::on_back_to_main_clicked()
{
    this->parent->back_to_main();
}


void OverviewArtikel::on_pushButton_clicked()
{

}


void OverviewArtikel::on_pushButton_2_clicked()
{

}

