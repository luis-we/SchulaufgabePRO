#include "overviewkunde.h"
#include "ui_overviewkunde.h"
#include "mainwindow.h"
#include "listitem.h"
#include "qsqlerror.h"

#include <QSqlQuery>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QPushButton>

using namespace std;


OverviewKunde::OverviewKunde(MainWindow* parent) : QWidget(parent), ui(new Ui::OverviewKunde)
{
    ui->setupUi(this);

    this->parent = parent;

    this->m_layout = new QVBoxLayout(this);

    vector<ListItem<QString>*>* customers = new vector<ListItem<QString>*>();

    QSqlQuery query;
    query.prepare("SELECT * FROM kunden");

    if (!query.exec()) {
        qDebug() << "Fehler beim Suchen nach Kunden: " << query.lastError().text();
        return;
    }

    while (query.next()) {
        QPushButton* button = new QPushButton(this);

        QString customerName = query.value("Name").toString();

        ListItem<QString>* customer = new ListItem<QString>(&customerName, button);

        connect(button, &QPushButton::clicked, [this, customer](){ this->on_list_item_clicked(customer); });

        button->setText(customerName);

        this->m_layout->addWidget(button);
        customers->push_back(customer);
    }

    ui->customers->setLayout(this->m_layout);
}

OverviewKunde::~OverviewKunde()
{
    delete ui;
}

void OverviewKunde::on_list_item_clicked(ListItem<QString>* item)
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

