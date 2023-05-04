#include "overviewbestellungen_liste.h"
#include "ui_overviewbestellungen_liste.h"
#include <QSqlQuery>
#include <QMessageBox>


overviewbestellungen_liste::overviewbestellungen_liste(int customerId, QStackedWidget *stack, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::overviewbestellungen_liste),
    m_customerId(customerId),
    m_stack(stack)
{
    ui->setupUi(this);
    ui->order_list->clear(); // Löscht alle vorhandenen Inhalte

    QSqlQuery query("SELECT b.ID_Bestellung, k.Name, k.Vorname, a.Artikelname, z.Menge FROM bestellungen b INNER JOIN kunden k ON b.ID_Kunde = k.ID_Kunde INNER JOIN zuordnung_bestellungen_artikel z ON b.ID_Bestellung = z.ID_Bestellung INNER JOIN artikel a ON z.ID_Artikel = a.Artikelnummer");

    while (query.next()) {
    QString order = "Bestellung #" + query.value("ID_Bestellung").toString() + ": " + query.value("Name").toString() + ", " + query.value("Vorname").toString() + " - " + query.value("Artikelname").toString() + " (" + query.value("Menge").toString() + ")";
    ui->order_list->append(order); // Fügt die Bestellung als neue Zeile hinzu
    }
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
