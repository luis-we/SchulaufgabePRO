#include "overviewlieferanten.h"
#include "ui_overviewlieferanten.h"
#include "mainwindow.h"

OverviewLieferanten::OverviewLieferanten(MainWindow* parent) : QWidget(parent), ui(new Ui::OverviewLieferanten)
{
    ui->setupUi(this);

    this->parent = parent;
}

OverviewLieferanten::~OverviewLieferanten()
{
    delete ui;
}

void OverviewLieferanten::on_back_to_main_clicked()
{
    this->parent->back_to_main();
}


void OverviewLieferanten::on_pushButton_anlegen_clicked()
{

}


void OverviewLieferanten::on_pushButton_2_bearbeiten_clicked()
{

}


void OverviewLieferanten::on_pushButton_3_loeschen_clicked()
{

}

