#ifndef OVERVIEWKUNDE_H
#define OVERVIEWKUNDE_H

#include "mainwindow.h"
#include "listitem.h"
#include "kunde.h"

#include <QWidget>
#include <QVBoxLayout>

using namespace std;

namespace Ui {
    class OverviewKunde;
}

class OverviewKunde : public QWidget
{
    Q_OBJECT

//Deklaration von Konstruktor und Destruktor
public:
    explicit OverviewKunde(MainWindow* parent = nullptr);
    ~OverviewKunde();

//Deklaration der Slots
private slots:
    void on_back_to_main_clicked();
    void on_save_clicked();
    void on_reset_clicked();
    void on_list_item_clicked(ListItem<Kunde>* item);
    void on_create_clicked();
    void on_remove_clicked();
    void on_ort_currentIndexChanged(int index);

//Deklaration privater Funktionen und Variablen
private:
    void LoadCustomers();
    void LoadCustomer(Kunde* customer);
    void SelectCustomer(ListItem<Kunde>* customer);
    void SaveCustomer(bool created);
    void ClearForm();
    void DeleteCustomer();
    void LoadSalutations();
    void LoadLocations();
    bool VerifyInput();
    QString FetchPLZFromLocation(int location);

    ListItem<Kunde>* CreateCustomerItem(Kunde* customer);

    Ui::OverviewKunde* ui;

    MainWindow* m_parent;
    QVBoxLayout* m_layout;

    ListItem<Kunde>* m_selectedCustomer;
    vector<ListItem<Kunde>*>* m_customers;
};

#endif // OVERVIEWKUNDE_H
