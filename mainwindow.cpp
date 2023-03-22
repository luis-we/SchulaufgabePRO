#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStackedWidget>
#include <QSqlDatabase>
#include <QMessageLogger>

MainWindow::MainWindow(QWidget* parent, QStackedWidget* stack) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->stack = stack;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::back_to_main()
{
    this->stack->setCurrentWidget(this);
}


void MainWindow::on_overview_kunden_clicked()
{
    this->stack->setCurrentIndex(1);
}

void MainWindow::on_overview_artikel_clicked()
{
    this->stack->setCurrentIndex(2);
}

void MainWindow::on_overview_lieferanten_clicked()
{
    this->stack->setCurrentIndex(3);
}

void MainWindow::on_overview_bestellungen_clicked()
{
    this->stack->setCurrentIndex(4);
}

