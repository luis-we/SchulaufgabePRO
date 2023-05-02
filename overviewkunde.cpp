#include "overviewkunde.h"
#include "ui_overviewkunde.h"
#include "mainwindow.h"
#include "listitem.h"
#include "qsqlerror.h"
#include "kunde.h"

#include <QSqlQuery>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QPushButton>

using namespace std;


OverviewKunde::OverviewKunde(MainWindow* parent) : QWidget(parent), ui(new Ui::OverviewKunde)
{
    ui->setupUi(this);

    this->m_parent = parent;
    this->m_layout = new QVBoxLayout(this);
    this->m_customers = new vector<ListItem<Kunde>*>();
    this->m_selectedCustomer = nullptr;

    ui->customers->setLayout(this->m_layout);

    ui->create->setDisabled(true);
    ui->remove->setDisabled(true);

    LoadCustomers();
}

OverviewKunde::~OverviewKunde()
{
    delete ui;
}

void OverviewKunde::DeleteCustomer()
{
    //m_selectedCustomer->GetValue()->delete();
    delete m_selectedCustomer;
    m_selectedCustomer = nullptr;
}

ListItem<Kunde>* OverviewKunde::CreateCustomerItem(Kunde* customer)
{
    QPushButton* button = new QPushButton(this);

    ListItem<Kunde>* customerItem = new ListItem<Kunde>(customer, button);

    connect(button, &QPushButton::clicked, [this, customerItem](){ this->on_list_item_clicked(customerItem); });

    button->setText(customer->getDisplayText());

    this->m_layout->addWidget(button);
    this->m_customers->push_back(customerItem);

    return customerItem;
}

void OverviewKunde::SelectCustomer(ListItem<Kunde>* customer)
{
    if(this->m_selectedCustomer == customer) return;

    ui->create->setDisabled(false);
    ui->remove->setDisabled(false);

    this->m_selectedCustomer = customer;

    LoadCustomer(customer->GetValue());
}

void OverviewKunde::LoadCustomer(Kunde* customer) {
    ui->id->setText(QString::number(customer->getID()));
    //ui->salutation->setText("Anrede");
    ui->titel->setText(customer->getTitel());
    ui->name->setText(customer->getName());
    ui->firstname->setText(customer->getVorname());
    ui->street->setText(customer->getStrasse());
    ui->streetnr->setText(customer->getHausNr());
    //ui->ort->setText("Ort");
    //ui->plz->setText("PLZ");
    ui->phone->setText(customer->getTelefon());
    ui->birthdate->setDate(customer->getGeburtsdatum());
    ui->mail->setText(customer->getEmail());
}

void OverviewKunde::ClearForm() {
    ui->id->clear();
    ui->salutation->clear();
    ui->titel->clear();
    ui->name->clear();
    ui->firstname->clear();
    ui->street->clear();
    ui->streetnr->clear();
    ui->ort->clear();
    ui->plz->clear();
    ui->phone->clear();
    ui->birthdate->clear();
    ui->mail->clear();
}

void OverviewKunde::SaveCustomer()
{
    Kunde* customer = m_selectedCustomer->GetValue();

    //customer->setAnrede();
    customer->setTitel(ui->titel->toPlainText());
    customer->setName(ui->name->toPlainText());
    customer->setVorname(ui->firstname->toPlainText());
    customer->setStrasse(ui->street->toPlainText());
    customer->setHausNr(ui->streetnr->toPlainText());
    //customer->setOrt();
    customer->setTelefon(ui->phone->toPlainText());
    customer->setGeburtsdatum(ui->birthdate->date());
    customer->setEmail(ui->mail->toPlainText());

    //customer->save();

    m_selectedCustomer->GetButton()->setText(customer->getDisplayText());
}

void OverviewKunde::LoadCustomers()
{
    QSqlQuery query;

    query.prepare("SELECT * FROM kunden");

    if (!query.exec()) {
        qDebug() << "Fehler bei der Suchen nach Kunden: " << query.lastError().text();
        return;
    }

    while (query.next()) {
        Kunde* customer = new Kunde(
            query.value("ID_Kunde").toInt(),
            query.value("Anrede").toInt(),
            query.value("Name").toString(),
            query.value("Vorname").toString(),
            query.value("Straße").toString(),
            query.value("Hausnummer").toString(),
            query.value("ID_Ort").toInt(),
            query.value("Telefon").toString(),
            query.value("Geburtsdatum").toDate(),
            query.value("Email").toString(),
            query.value("Titel").toString()
        );

        CreateCustomerItem(customer);
    }
}

void OverviewKunde::on_list_item_clicked(ListItem<Kunde>* item)
{
    SelectCustomer(item);
}

void OverviewKunde::on_back_to_main_clicked()
{
    this->m_parent->back_to_main();
}


void OverviewKunde::on_save_clicked()
{ 
    // TODO: Funktion für eingabe überprüfung

    if(m_selectedCustomer == nullptr) {
        Kunde* customer = new Kunde();
        m_selectedCustomer = CreateCustomerItem(customer);
    }

    SaveCustomer();
}

void OverviewKunde::on_reset_clicked()
{
    if(this->m_selectedCustomer == nullptr) {
        ClearForm();
        return;
    }

    LoadCustomer(this->m_selectedCustomer->GetValue());
}


void OverviewKunde::on_create_clicked()
{
    m_selectedCustomer = nullptr;
    ClearForm();

    ui->create->setDisabled(true);
    ui->remove->setDisabled(true);
}


void OverviewKunde::on_remove_clicked()
{
    ClearForm();

    if(this->m_selectedCustomer == nullptr) return;

    DeleteCustomer();

    ui->create->setDisabled(true);
    ui->remove->setDisabled(true);
}

