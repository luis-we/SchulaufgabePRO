#include "overviewkunde.h"
#include "ui_overviewkunde.h"
#include "mainwindow.h"

#include <QVBoxLayout>
#include <QLabel>

OverviewKunde::OverviewKunde(MainWindow* parent) : QWidget(parent), ui(new Ui::OverviewKunde)
{
    ui->setupUi(this);

    this->parent = parent;

    QVBoxLayout* customerLayout = new QVBoxLayout(this);

    for(int i = 0; i < 50; i++) {
        QLabel* customerLabel = new QLabel(this);

        customerLabel->setText("Test: " + QString::number(i));
        customerLayout->addWidget(customerLabel);
    }

    ui->customers->setLayout(customerLayout);
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

