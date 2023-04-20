#include "overviewkunde.h"
#include "ui_overviewkunde.h"
#include "mainwindow.h"
#include "listitem.h"

#include <listitem.h>
#include <QVBoxLayout>
#include <QPushButton>

using namespace std;

OverviewKunde::OverviewKunde(MainWindow* parent) : QWidget(parent), ui(new Ui::OverviewKunde)
{
    ui->setupUi(this);

    this->parent = parent;

    this->m_layout = new QVBoxLayout(this);

    vector<ListItem<int>*>* customers = new vector<ListItem<int>*>();

    for(int i = 0; i < 50; i++) {
        QPushButton* button = new QPushButton(this);
        ListItem<int>* customer = new ListItem<int>(&i, button);

        connect(button, &QPushButton::clicked, [this, customer](){ this->on_list_item_clicked(customer); });

        button->setText("Test" + QString::number(i));

        this->m_layout->addWidget(button);
        customers->push_back(customer);
    }

    ui->customers->setLayout(this->m_layout);
}

OverviewKunde::~OverviewKunde()
{
    delete ui;
}

void OverviewKunde::on_list_item_clicked(ListItem<int>* item)
{
    qDebug() << "Clicked: " << item->GetButton()->text();
    this->m_layout->removeWidget(item->GetButton());
    delete item->GetButton();
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

