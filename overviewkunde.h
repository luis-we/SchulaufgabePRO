#ifndef OVERVIEWKUNDE_H
#define OVERVIEWKUNDE_H

#include "mainwindow.h"
#include "listitem.h"

#include <QWidget>
#include <QVBoxLayout>

namespace Ui {
class OverviewKunde;
}

class OverviewKunde : public QWidget
{
    Q_OBJECT

public:
    explicit OverviewKunde(MainWindow* parent = nullptr);
    ~OverviewKunde();

private slots:
    void on_back_to_main_clicked();

    void on_save_clicked();

    void on_reset_clicked();

    void on_list_item_clicked(ListItem<int>* item);

private:
    Ui::OverviewKunde* ui;

    MainWindow* parent;
    QVBoxLayout* m_layout;
};

#endif // OVERVIEWKUNDE_H
