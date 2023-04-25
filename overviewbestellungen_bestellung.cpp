// overviewbestellungen_bestellung.cpp
#include "overviewbestellungen_bestellung.h"
#include "ui_overviewbestellungen_bestellung.h"

#include "mainwindow.h"


OverviewBestellungen_Bestellung::OverviewBestellungen_Bestellung(int customerId) :
    ui(new Ui::overviewbestellungen_bestellung),
    m_customerId(customerId)
{
    ui->setupUi(this);

    // Den customerId im Label_ID anzeigen
    ui->ID_Label->setText(QString::number(customerId));
}

OverviewBestellungen_Bestellung::~OverviewBestellungen_Bestellung()
{
    delete ui;
}


void OverviewBestellungen_Bestellung::on_back_clicked()
{

}

