#include "robot4.h"
#include "ui_robot4.h"

robot4::robot4(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::robot4)
{
    ui->setupUi(this);
}

robot4::~robot4()
{
    delete ui;
}
