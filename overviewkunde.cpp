#include "overviewkunde.h"
#include "ui_overviewkunde.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QMessageBox>
#include "qsqlerror.h"



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

    QSqlQuery query;
    query.prepare("SELECT * FROM kunden");

    if (!query.exec()) {
        // Fehler beim Ausführen der Abfrage
        qDebug() << "Fehler beim Suchen nach Kunden:";
        qDebug() << query.lastError().text();
        return;
    }

    // Fügen Sie jeden gefundenen Kunden zur Liste hinzu
    while (query.next()) {
        QString customerName = query.value("Name").toString();

        qDebug() << "Kunde " << customerName << "erfolgreich geladen!";
    }
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

