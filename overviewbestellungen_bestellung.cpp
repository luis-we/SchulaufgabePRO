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
    queryArtikel.prepare("SELECT Artikelnummer, Artikelname, Lagerbestand, Preis_Netto FROM artikel WHERE Artikelname LIKE :artikel");
    queryArtikel.bindValue(":artikel", "%" + searchText + "%");

    if (!queryArtikel.exec()) {
        // Fehler beim Ausführen der Abfrage
        qDebug() << "Fehler beim Suchen nach Artikel:";
        qDebug() << queryArtikel.lastError().text();
        return;
    }

    // Fügen Sie jeden gefundenen Artikel zur Liste hinzu
    while (queryArtikel.next()) {
        QSqlQueryModel *modelArtikel = new QSqlQueryModel();
        modelArtikel->setQuery(queryArtikel);


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




        connect(ui->artikelListe, &QTableView::clicked, this, &OverviewBestellungen_Bestellung::onArtikelClicked);
    }

}

void OverviewBestellungen_Bestellung::onArtikelClicked(const QModelIndex &index)
{
    // Überprüfen, ob ein gültiger Index vorliegt
    if (index.isValid()) {
        // Zeile der ausgewählten Zelle abrufen
        int row = index.row();

        artikelID = ui->artikelListe->model()->data(ui->artikelListe->model()->index(row, 0)).toString();
        artikelName = ui->artikelListe->model()->data(ui->artikelListe->model()->index(row, 1)).toString();
        lagerbestand = ui->artikelListe->model()->data(ui->artikelListe->model()->index(row, 2)).toInt();
        einzelPreis = ui->artikelListe->model()->data(ui->artikelListe->model()->index(row, 3)).toDouble();

        ui->artikelMenge->setMaximum(lagerbestand);
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


void OverviewBestellungen_Bestellung::on_hinzufugen_clicked()
{
    menge = ui->artikelMenge->value();
    preis = einzelPreis * menge;

    QMessageBox *fehlerMenge = new QMessageBox();

    if(menge==0){
        fehlerMenge->setText("Menge darf nicht Null sein! Du Hurensohn");
        fehlerMenge->show();
    }

    // Setze die Artikelinformationen entsprechend in die Tabelle warenkorb ein
    QStandardItemModel *warenkorbModel = qobject_cast<QStandardItemModel*>(ui->warenkorb->model());
    if (!warenkorbModel) {
        warenkorbModel = new QStandardItemModel(this);
        ui->warenkorb->setModel(warenkorbModel);
        warenkorbModel->setHorizontalHeaderLabels(QStringList() << "Artikelname" << "Einzelpreis" << "Menge" << "Preis");
    }

    QList<QStandardItem*> rowData;
    rowData << new QStandardItem(artikelName);
    rowData << new QStandardItem(QString::number(einzelPreis));
    rowData << new QStandardItem(QString::number(menge));
    rowData << new QStandardItem(QString::number(preis));

    warenkorbModel->appendRow(rowData);

    // Optional: Warenkorb-Tabelle anpassen
    ui->warenkorb->resizeColumnsToContents();
}


