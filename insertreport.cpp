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
    int cf=ui->txtFreq->text().toInt();
    MainWindow mw;
    mw.InsertData(name, cf);
    this->close();
}

