// overviewbestellungen_bestellung.cpp
#include "overviewbestellungen_bestellung.h"
#include "ui_overviewbestellungen_bestellung.h"
#include <QStackedWidget>
#include <QSqlQuery>
#include <QMessageBox>
#include <qlistwidget.h>
#include <mainwindow.h>


OverviewBestellungen_Bestellung::OverviewBestellungen_Bestellung(int customerId, QStackedWidget* stack, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::overviewbestellungen_bestellung),
    m_customerId(customerId),
    m_stack(stack)
{
    ui->setupUi(this);

    // Den customerId im Label_ID anzeigen
    ui->ID_Label->setText(QString::number(customerId));

    connect(ui->artikelSuche, &QLineEdit::textChanged, this, &OverviewBestellungen_Bestellung::searchArtikel);
}

OverviewBestellungen_Bestellung::~OverviewBestellungen_Bestellung()
{
    delete ui;
}

void OverviewBestellungen_Bestellung::searchArtikel(const QString &searchText)
{


}

void OverviewBestellungen_Bestellung::on_back_clicked()
{
    m_stack->setCurrentIndex(4);
}


void OverviewBestellungen_Bestellung::on_orders_clicked()
{
    m_liste = new overviewbestellungen_liste(m_customerId, m_stack);
    m_stack->addWidget(m_liste);
    m_stack->setCurrentIndex(6);
}
