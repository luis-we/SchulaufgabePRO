// overviewbestellungen_bestellung.cpp
#include "overviewbestellungen_bestellung.h"
#include "ui_overviewbestellungen_bestellung.h"
#include <QStackedWidget>
#include <qlineedit.h>
#include <QSqlQuery>
#include "qsqlerror.h"
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


    connect(ui->artiklSuche, &QLineEdit::textChanged, this, &OverviewBestellungen_Bestellung::searchArtikel);
}

OverviewBestellungen_Bestellung::~OverviewBestellungen_Bestellung()
{
    delete ui;
}

void OverviewBestellungen_Bestellung::searchArtikel(const QString &text)
{
    if (text.length() < 3) {
        // Suche nicht starten, wenn weniger als 3 Buchstaben eingegeben wurden
        return;
    }

    ui->artikelListe->clear();

    // Suche nach Kunden mit dem eingegebenen Text im Namen
    QSqlQuery query;
    query.prepare("SELECT * FROM kunden WHERE Name LIKE :name");
    query.bindValue(":name", "%" + text + "%");

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

        QListWidgetItem *item = new QListWidgetItem(ui->artikelListe);
        item->setText(customerName);
        item->setData(Qt::UserRole, customerId);
        item->setToolTip("Adresse: " + customerAddress + "\n" + "ID_Ort:\t" + customerCity + "\n" + "Tel.:\t" + customerPhone);
    }
}

void OverviewBestellungen_Bestellung::on_back_clicked()
{
    m_stack->setCurrentIndex(4);
}

