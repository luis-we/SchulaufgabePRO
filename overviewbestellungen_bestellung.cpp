#include "overviewbestellungen_bestellung.h"
#include "ui_overviewbestellungen_bestellung.h"

overviewbestellungen_bestellung::overviewbestellungen_bestellung(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::overviewbestellungen_bestellung)
{
    ui->setupUi(this);
}

overviewbestellungen_bestellung::~overviewbestellungen_bestellung()
{
    delete ui;
}
