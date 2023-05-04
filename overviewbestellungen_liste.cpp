#include "overviewbestellungen_liste.h"
#include "ui_overviewbestellungen_liste.h"

overviewbestellungen_liste::overviewbestellungen_liste(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::overviewbestellungen_liste)
{
    ui->setupUi(this);
}

overviewbestellungen_liste::~overviewbestellungen_liste()
{
    delete ui;
    
}

void overviewbestellungen_liste::on_back_clicked()
{

}

