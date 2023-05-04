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
#include <QVariant>

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

    LoadSalutations();
    LoadLocations();
    LoadCustomers();

    ClearForm();
}

OverviewKunde::~OverviewKunde()
{
    delete ui;
}

void OverviewKunde::LoadSalutations()
{
    QSqlQuery query;

    query.prepare("SELECT * FROM anrede");

    if (!query.exec()) {
        qDebug() << "Fehler bei der Suchen nach Anreden: " << query.lastError().text();
        return;
    }

    while (query.next()) {
        int salutation_id = query.value("ID_Anrede").toInt();
        QString salutation = query.value("Anrede").toString();

        ui->salutation->addItem(salutation, salutation_id);
    }
}

void OverviewKunde::LoadLocations()
{
    QSqlQuery query;

    query.prepare("SELECT * FROM ort");

    if (!query.exec()) {
        qDebug() << "Fehler bei der Suchen nach Orten: " << query.lastError().text();
        return;
    }

    while (query.next()) {
        int ort_id = query.value("ID_Ort").toInt();
        QString ort = query.value("Ort").toString();

        ui->ort->addItem(ort, ort_id);
    }

    ui->birthdate->setDate(QDate::currentDate());
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
    ui->salutation->setCurrentIndex(ui->salutation->findData(customer->getAnrede()));
    ui->titel->setText(customer->getTitel());
    ui->name->setText(customer->getName());
    ui->firstname->setText(customer->getVorname());
    ui->street->setText(customer->getStrasse());
    ui->streetnr->setText(customer->getHausNr());
    ui->ort->setCurrentIndex(ui->ort->findData(customer->getOrt()));
    ui->phone->setText(customer->getTelefon());

    if(customer->getGeburtsdatum().isValid()) {
        ui->birthdate->setDate(customer->getGeburtsdatum());
    }
    else {
        ui->birthdate->setDate(QDate::currentDate());
    }

    ui->mail->setText(customer->getEmail());
}

QString OverviewKunde::FetchPLZFromLocation(int location) {
    QString plz = "";

    QSqlQuery query;

    query.prepare("SELECT PLZ FROM ort WHERE ID_Ort = " + QString::number(location));

    if (!query.exec()) {
        qDebug() << "Fehler bei der Suchen nach PLZ: " << query.lastError().text();
        return plz;
    }

    while (query.next()) {
        plz = query.value("PLZ").toString();
    }

    return plz;
}

void OverviewKunde::ClearForm() {
    ui->id->clear();
    ui->salutation->setCurrentIndex(-1);
    ui->titel->clear();
    ui->name->clear();
    ui->firstname->clear();
    ui->street->clear();
    ui->streetnr->clear();
    ui->ort->setCurrentIndex(-1);
    ui->plz->clear();
    ui->phone->clear();
    ui->birthdate->setDate(QDate::currentDate());
    ui->mail->clear();
}

void OverviewKunde::SaveCustomer(bool created)
{
    Kunde* customer = m_selectedCustomer->GetValue();

    customer->setAnrede(ui->salutation->currentData().value<int>());
    customer->setTitel(ui->titel->toPlainText());
    customer->setName(ui->name->toPlainText());
    customer->setVorname(ui->firstname->toPlainText());
    customer->setStrasse(ui->street->toPlainText());
    customer->setHausNr(ui->streetnr->toPlainText());
    customer->setOrt(ui->ort->currentData().value<int>());
    customer->setTelefon(ui->phone->toPlainText());
    customer->setGeburtsdatum(ui->birthdate->date());
    customer->setEmail(ui->mail->toPlainText());

    if(created) {
        //customer->create();
        LoadCustomer(customer);
    }
    else {
        //customer->save();
    }

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

bool OverviewKunde::VerifyInput() {
    return true;
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
    if(!VerifyInput()) {
        return;
    }

    bool created = false;

    if(m_selectedCustomer == nullptr) {
        Kunde* customer = new Kunde();
        m_selectedCustomer = CreateCustomerItem(customer);
        created = true;
    }

    SaveCustomer(created);
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


void OverviewKunde::on_ort_currentIndexChanged(int index)
{
    if(index == -1) {
        ui->plz->clear();
        return;
    }

    int location = ui->ort->currentData().value<int>();

    ui->plz->setText(FetchPLZFromLocation(location));
}

