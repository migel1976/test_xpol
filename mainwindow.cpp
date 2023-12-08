#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <unistd.h>
#include <QThread>
#include <QMessageBox>

QString host="localhost";
QString dbname="xpol";
QString pass="";
QString username="postgres";
DbManager dbM(host, dbname, pass, username);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ConnectReport();
}

void MainWindow::ConnectReport(){
    model=new QSqlTableModel(this);
    model->setTable("report");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    ui->tableView->setModel(model);
}

void MainWindow::RefreshReportModel(){
    model->select();
}
void MainWindow::InsertData(QString name, int cf){
    dbM.addReport(name, cf);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnAddReport_clicked()
{
    qWarning()<<"WARNING: add button";
    insertreport *newT=new insertreport(this);
    newT->setAttribute(Qt::WA_DeleteOnClose);
    connect(newT,SIGNAL(destroyed(QObject*)), SLOT(RefreshReportModel()));
    newT->show();
}

void MainWindow::on_btnDeleteReport_clicked()
{
    dbM.removeReport(glRow);
    model->select();
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    int rowId=index.row();
    QModelIndex idx=model->index(rowId,0);
    glRow =idx.data().toString();
    qWarning()<<glRow;
}

