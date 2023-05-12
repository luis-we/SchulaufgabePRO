#ifndef OVERVIEWARTIKEL_H
#define OVERVIEWARTIKEL_H

#include "mainwindow.h"

#include "artikel.h"
#include "listitem.h"

#include <QWidget>
#include <QVBoxLayout>

using namespace std;

namespace Ui {
class OverviewArtikel;
}

//Deklaration des Konstruktor und Destruktor
class OverviewArtikel : public QWidget
{
    Q_OBJECT

//Deklaration von Konstruktor und Destruktor
public:
    explicit OverviewArtikel(MainWindow* parent = nullptr);
    ~OverviewArtikel();

//Slots Deklaration
private slots:
    void on_back_to_main_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonClear_clicked();
    void on_pushButtonAktualisieren_clicked();
    void on_pushButtonNeuanlegen_clicked();

//private Funktionen und Variablen Deklaration
private:
    void LoadArticles();
    void LoadArticle(Artikel* Article);
    void LoadSuppliers();
    void SelectArtikel(ListItem<Artikel>* article);
    void on_list_item_clicked(ListItem<Artikel>* Article);
    void DeleteArtikel();
    void SaveArtikel();
    void UpdateArtikel();
    void SaveArticle(bool created);
    void ClearForm();
    void DeleteArticle();
    bool VerifyInput();

    MainWindow* parent;

    ListItem<Artikel>* CreateArtikelItem(Artikel* artikel);

    Ui::OverviewArtikel* ui;

    MainWindow* m_parent;
    QVBoxLayout* m_layout;

    ListItem<Artikel>* m_selectedArtikel;
    vector<ListItem<Artikel>*>* m_artikels;

};

#endif // OVERVIEWARTIKEL_H



