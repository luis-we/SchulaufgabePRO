#include "overviewlieferanten.h"
#include "ui_overviewlieferanten.h"
#include "mainwindow.h"

OverviewLieferanten::OverviewLieferanten(MainWindow* parent) : QWidget(parent), ui(new Ui::OverviewLieferanten)
{
    ui->setupUi(this);//Erstellt UI für OverviewLieferanten

    this->parent = parent; //Übergibt parent an private Variable
}

OverviewLieferanten::~OverviewLieferanten()
{
    delete ui; //Löscht UI wenn Fenster geschlossen wird
}

void OverviewLieferanten::on_back_to_main_clicked()
{
    this->parent->back_to_main(); //Zurück zum Hauptmenü Button
}


void OverviewLieferanten::on_pushButton_anlegen_clicked()
{
    //Button zum Anlegen eines neuen Lieferanten
}


void OverviewLieferanten::on_pushButton_2_bearbeiten_clicked()
{
    //Button zum Bearbeiten eines Lieferanten
}


void OverviewLieferanten::on_pushButton_3_loeschen_clicked()
{
    //Button zum Löschen eines Lieferanten
}

