#include "insertreport.h"
#include "ui_insertreport.h"
#include "mainwindow.h"

insertreport::insertreport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::insertreport)
{
    ui->setupUi(this);
}

insertreport::~insertreport()
{
    delete ui;
}

void insertreport::on_btnAdd_clicked()
{
    QString name=ui->txtName->text();
    MainWindow mw;
    mw.InsertData(name);
    this->close();
}

