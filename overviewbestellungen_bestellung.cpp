// overviewbestellungen_bestellung.cpp
#include "overviewbestellungen_bestellung.h"
#include "ui_overviewbestellungen_bestellung.h"
#include <QStackedWidget>
#include <QSqlQuery>
#include <QMessageBox>
#include <qlistwidget.h>
#include <mainwindow.h>
#include "qsqlerror.h"
#include "QSqlQueryModel"
#include <QtGui>



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
    if (searchText.length() < 3) {
        // Suche nicht starten, wenn weniger als 3 Buchstaben eingegeben wurden
        return;
    }

   // ui->artikelListe->clear();

    // Suche nach Artikel mit dem eingegebenen Text im Namen
    QSqlQuery queryArtikel;
    queryArtikel.prepare("SELECT * FROM artikel WHERE Artikelname LIKE :artikel");
    queryArtikel.bindValue(":artikel", "%" + searchText + "%");

    if (!queryArtikel.exec()) {
        // Fehler beim Ausführen der Abfrage
        qDebug() << "Fehler beim Suchen nach Artikel:";
        qDebug() << queryArtikel.lastError().text();
        return;
    }

    // Fügen Sie jeden gefundenen Artikel zur Liste hinzu
    while (queryArtikel.next()) {
        QString artikelName = queryArtikel.value("Artikelname").toString();
        QString artikelNetto = queryArtikel.value("Preis_Netto").toString();
        QString artikelID = queryArtikel.value("Artikelnummer").toString();
        double einzelPreis = queryArtikel.value("Preis_Netto").toDouble();


        QSqlQueryModel *modelArtikel = new QSqlQueryModel();

        QSqlQuery queryTabelle;
        queryTabelle.prepare("SELECT Artikelname, Preis_Netto from artikel WHERE Artikelname LIKE :artikelTest");
        queryTabelle.bindValue(":artikelTest", "%" + searchText + "%");

        queryTabelle.bindValue(":artikelID", artikelID);
        if (!queryTabelle.exec()) {
            QMessageBox::critical(this, "Fehler", "Fehler bei der Datenbankabfrage: " + queryTabelle.lastError().text());
            return;
        }
        queryTabelle.exec();


        modelArtikel->setQuery(std::move(queryTabelle));
        ui->artikelListe->setModel(modelArtikel);
        ui->artikelListe->resizeColumnsToContents();
        int columnCountA = modelArtikel->columnCount();
        int availableWidthA = ui->artikelListe->viewport()->width();
        int defaultColumnWidthA = availableWidthA / columnCountA;

        for (int i = 0; i < columnCountA; ++i) {
            ui->artikelListe->setColumnWidth(i, defaultColumnWidthA);
        }

        ui->artikelListe->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
        ui->artikelListe->horizontalHeader()->setMaximumSectionSize(availableWidthA);



        int menge = 1;
        double preis = 0.0;

        menge = ui->artikelMenge->value();

        preis = einzelPreis * menge;



        on_hinzufugen_clicked(artikelName, menge, preis, artikelNetto);

    }

}

void OverviewBestellungen_Bestellung::on_back_clicked()
{
    m_stack->setCurrentIndex(4);
}


void OverviewBestellungen_Bestellung::on_orders_clicked()
{

    // prüfen, ob bereits ein Widget für die Bestellung existiert, wenn ja, löschen
    if (m_liste) {
        m_stack->removeWidget(m_liste);
        delete m_liste;
        m_liste = nullptr;
    }

    m_liste = new overviewbestellungen_liste(m_customerId, m_stack);
    m_stack->addWidget(m_liste);
    m_stack->setCurrentIndex(6);
}

void OverviewBestellungen_Bestellung::on_hinzufugen_clicked(QString& artikelName, int& menge, double& preis, QString& artikelNetto)
{
    /*QStandardItemModel *modelWaren = new QStandardItemModel(this);
    modelWaren->setHorizontalHeaderLabels(QStringList() << "Artikel" << "Menge" << "Einzelpreis" << "Preis");
    modelWaren->setColumnCount(4);
    modelWaren->setData(modelWaren->index(0, 0), QVariant(artikelName));
    modelWaren->setData(modelWaren->index(0, 1), QVariant(menge));
    modelWaren->setData(modelWaren->index(0, 2), QVariant(artikelNetto));
    modelWaren->setData(modelWaren->index(0, 3), QVariant(preis));

    ui->warenkorb->setModel(modelWaren);
    //ui->warenkorb->resizeColumnsToContents();*/
    ui->debug->setText(artikelName + " " + artikelNetto);

    QSqlQueryModel *modelWaren = new QSqlQueryModel();

    QSqlQuery queryWaren;
    queryWaren.prepare("SELECT Artikelname,"
                       "CONCAT(Preis_Netto, ' €') AS Preis_Netto, "
                       "CONCAT(:menge * Preis_Netto, ' €') AS Gesamtpreis"
                       "from artikel WHERE Artikelname LIKE :artikelName");

    queryWaren.exec();

    modelWaren->setQuery(std::move(queryWaren));
    ui->warenkorb->setModel(modelWaren);

    //qDebug() << queryWaren.value('Artikelname');


    ui->gesamtPreis->setText(QString::number(preis));
}

