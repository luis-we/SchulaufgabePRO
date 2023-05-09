#ifndef OVERVIEWARTIKEL_H
#define OVERVIEWARTIKEL_H

#include "mainwindow.h"

#include "artikel.h"
#include "listitem.h"

#include <QWidget>

using namespace std;

namespace Ui {
class OverviewArtikel;
}

//Deklaration des Konstruktor und Destruktor
class OverviewArtikel : public QWidget
{
    Q_OBJECT


public:
    explicit OverviewArtikel(MainWindow* parent = nullptr);
    ~OverviewArtikel();

//Slots Deklaration
private slots:
    void on_back_to_main_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

//private Funktionen und Variablen Deklaration
private:
    void LoadArticles();
    void LoadArticle(Artikel* Article);
    void SelectArticle(ListItem<Artikel>* Article);
    void SaveArticle(bool created);
    void ClearForm();
    void DeleteArticle();
    bool VerifyInput();

    Ui::OverviewArtikel* ui;

    MainWindow* parent;

};

#endif // OVERVIEWARTIKEL_H



