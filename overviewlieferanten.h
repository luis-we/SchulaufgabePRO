#ifndef OVERVIEWLIEFERANTEN_H
#define OVERVIEWLIEFERANTEN_H

#include "listitem.h"
#include "mainwindow.h"

#include <QWidget>
#include <QVBoxLayout>

using namespace std;

namespace Ui {
class OverviewLieferanten;
}

class OverviewLieferanten : public QWidget
{
    Q_OBJECT

public:
    explicit OverviewLieferanten(MainWindow* parent = nullptr);
    ~OverviewLieferanten();

private slots:
    void on_list_item_clicked(ListItem<QString>* item);

    void on_back_to_main_clicked();

    void on_pushButton_anlegen_clicked();

    void on_pushButton_2_bearbeiten_clicked();

    void on_pushButton_3_loeschen_clicked();

private:
    Ui::OverviewLieferanten* ui;
    vector<ListItem<QString>*>* lieferanten;
    MainWindow* parent;
    QVBoxLayout* m_layout;
};

#endif // OVERVIEWLIEFERANTEN_H
