#include "overviewbestellungen_liste.h"
#include "qsqlerror.h"
#include "ui_overviewbestellungen_liste.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlQueryModel>

overviewbestellungen_liste::overviewbestellungen_liste(int customerId, QStackedWidget *stack, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::overviewbestellungen_liste),
    m_customerId(customerId),
    m_stack(stack)
{
    ui->setupUi(this);

    QSqlQueryModel *model = new QSqlQueryModel();

    QSqlQuery query;
    query.prepare("SELECT b.Bestelldatum, a.Artikelname, z.Menge, a.Preis_Netto, "
                  "z.Menge * a.Preis_Netto AS Gesamtpreis_Netto "
                  "FROM bestellungen b "
                  "INNER JOIN kunden k ON b.ID_Kunde = k.ID_Kunde "
                  "INNER JOIN zuordnung_bestellungen_artikel z ON b.ID_Bestellung = z.ID_Bestellung "
                  "INNER JOIN artikel a ON z.ID_Artikel = a.Artikelnummer "
                  "WHERE b.ID_Kunde = :customerId "
                  "ORDER BY b.Bestelldatum ASC, a.Artikelname");

    query.bindValue(":customerId", customerId);
    if (!query.exec()) {
        QMessageBox::critical(this, "Fehler", "Fehler bei der Datenbankabfrage: " + query.lastError().text());
        return;
    }
    query.exec();

    model->setQuery(std::move(query));
    ui->order_tableView->setModel(model);
    ui->order_tableView->resizeColumnsToContents();
    int columnCount = model->columnCount();
    int availableWidth = ui->order_tableView->viewport()->width();
    int defaultColumnWidth = availableWidth / columnCount;

    for (int i = 0; i < columnCount; ++i) {
        ui->order_tableView->setColumnWidth(i, defaultColumnWidth);
    }

    ui->order_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->order_tableView->horizontalHeader()->setMaximumSectionSize(availableWidth);


}

overviewbestellungen_liste::~overviewbestellungen_liste()
{
    delete ui;
}

void overviewbestellungen_liste::on_back_clicked()
{
    m_stack->setCurrentIndex(5);
    m_stack->removeWidget(this);
}
