#include "overviewkunde.h"
#include "ui_overviewkunde.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QMessageBox>
#include "qsqlerror.h"



OverviewKunde::OverviewKunde(MainWindow* parent) : QWidget(parent), ui(new Ui::OverviewKunde)
{
    ui->setupUi(this);

    this->parent = parent;

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
        QString customerAddress = query.value("Straße").toString() + " " + query.value("Hausnummer").toString();
        QString customerCity = query.value("ID_Ort").toString();
        QString customerPhone = query.value("Telefon").toString();
        QString customerId = query.value("ID_Kunde").toString();

        qDebug() << "Fehler beim Suchen nach Eis:";
        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setText(customerName);
        msgBox->show();
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

