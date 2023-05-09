#include "mainwindow.h"

#include "overviewkunde.h"
#include "overviewlieferanten.h"
#include "overviewartikel.h"
#include "overviewbestellungen.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QStackedWidget>
#include <QVBoxLayout>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);


    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("schlumpfshop3");
    db.setUserName("root");
    db.setPassword("");

    if (db.open()) {
        qDebug() << "Erfolgreich mit der MySQL-Datenbank verbunden!";
    } else {
        qDebug() << "Fehler beim Verbinden mit der MySQL-Datenbank:";
        qDebug() << db.lastError().text();
    }

    QStackedWidget* stack = new QStackedWidget();

    stack->setFixedWidth(800);
    stack->setFixedHeight(800);

    MainWindow* mainWindow = new MainWindow(nullptr, stack);

    stack->addWidget(mainWindow);

    OverviewKunde* overviewKunde = new OverviewKunde(mainWindow);
    OverviewArtikel* overviewArtikel = new OverviewArtikel(mainWindow);
    OverviewLieferanten* overviewLieferanten = new OverviewLieferanten(mainWindow);
    OverviewBestellungen* overviewBestellungen = new OverviewBestellungen(mainWindow);

    stack->addWidget(overviewKunde);
    stack->addWidget(overviewArtikel);
    stack->addWidget(overviewLieferanten);
    stack->addWidget(overviewBestellungen);

    stack->setCurrentWidget(mainWindow);
    stack->show();







    return a.exec();
}
