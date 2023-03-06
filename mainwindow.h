#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr, QStackedWidget* stack = nullptr);
    ~MainWindow();

    void back_to_main();

private slots:
    void on_overview_kunden_clicked();

    void on_overview_artikel_clicked();

    void on_overview_lieferanten_clicked();

    void on_overview_bestellungen_clicked();

private:
    Ui::MainWindow* ui;

    QStackedWidget* stack;
};
#endif // MAINWINDOW_H
