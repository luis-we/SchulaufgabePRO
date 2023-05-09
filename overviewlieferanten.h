#ifndef OVERVIEWLIEFERANTEN_H
#define OVERVIEWLIEFERANTEN_H

#include "listitem.h"
#include "mainwindow.h"
#include "lieferant.h"

#include <QWidget>
#include <QVBoxLayout>

using namespace std;

// 
namespace Ui {
class OverviewLieferanten;
}

// Klasse für die Übersicht der Lieferanten
class OverviewLieferanten : public QWidget
{
    Q_OBJECT

// Öffentliche Methoden
public:
    explicit OverviewLieferanten(MainWindow* parent = nullptr);
    ~OverviewLieferanten();



public slots:


// Private Attribute    
private slots:
    void on_list_item_clicked(ListItem<lieferant>* item);
    void on_back_to_main_clicked();
    void on_pushButton_anlegen_clicked();
    void on_pushButton_2_bearbeiten_clicked();
    void on_pushButton_3_loeschen_clicked();
    void on_pushButton_leeren_clicked();


private:
    Ui::OverviewLieferanten* ui;
    vector<ListItem<lieferant>*>* lieferanten;
    MainWindow* parent;
    QVBoxLayout* m_layout;

    void LeereForm();
    void LadeAnreden();
    void LadeOrte();
    void LadeLieferanten();
    void LadeLieferant(lieferant* delivery);
    void SpeichereLieferant(bool created);
    void LoescheLieferant();
    bool UeberpruefeEingabe();
    QString HolePLZVonOrt(int loc);
    void WaehleLieferant(ListItem<lieferant>* delivery);
    void Ortswechsel(int index);

    ListItem<lieferant>* ErstelleLieferant(lieferant* delivery);
    ListItem<lieferant>* m_ausgewaelterLieferant;
    vector<ListItem<lieferant>*>* m_lieferanten;

};

#endif // OVERVIEWLIEFERANTEN_H
