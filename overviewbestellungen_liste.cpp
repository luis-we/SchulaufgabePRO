#include "overviewbestellungen_liste.h"
#include "ui_overviewbestellungen_liste.h"

overviewbestellungen_liste::overviewbestellungen_liste(int customerId, QStackedWidget *stack, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::overviewbestellungen_liste),
    m_customerId(customerId),
    m_stack(stack)
{
    ui->setupUi(this);
}

overviewbestellungen_liste::~overviewbestellungen_liste()
{
    delete ui;
}

void overviewbestellungen_liste::on_back_clicked()
{

    m_stack->setCurrentIndex(5);
}
