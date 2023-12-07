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

    // QSqlTableModel *model=new QSqlTableModel(this);
    // model=new QSqlTableModel(this);
    // model->setTable("report");
    // // model->setEditStrategy(QSqlTableModel::OnRowChange);
    // // model->setEditStrategy(QSqlTableModel::OnFieldChange);
    // model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    // model->select();
    // ui->tableView->setModel(model);
    RefreshReport();
    // connect(this, &MainWindow::modelReportChanged, this, &MainWindow::RefreshReportModel);
    // connect(this, &MainWindow::modelReportChanged, this, &MainWindow::on_pushButton_clicked);
}

void MainWindow::RefreshReport(){
    model=new QSqlTableModel(this);
    model->setTable("report");
    // model->setEditStrategy(QSqlTableModel::OnRowChange);
    // model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    ui->tableView->setModel(model);
}

void MainWindow::RefreshReportModel(){
    model->select();
    qWarning()<<"this is fuck";
}
void MainWindow::InsertData(QString name){
    dbM.addReport(name);

    // ui->tableView->setModel(NULL);
    // QMessageBox msg;
    // msg.setText("insert was succesfull");
    // msg.exec();
    // usleep(1000);
    // QThread::sleep(2);
    // emit modelReportChanged();
    // model->submitAll();
    // model->select();
    // ui->tableView->reset();
    // QSqlTableModel::select();
    // RefreshReport();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnAddReport_clicked()
{
    qWarning()<<"WARNING: add button";
    qDebug()<<"DEBUG: add button";
    // insertDlg=new insertreport(0);
    // insertDlg->show();

    // insertreport *newT=0;
    // newT=new insertreport();
    insertreport *newT=new insertreport(this);
    newT->setAttribute(Qt::WA_DeleteOnClose);
    connect(newT,SIGNAL(destroyed(QObject*)), SLOT(RefreshReportModel()));
    newT->show();
}


void MainWindow::on_pushButton_clicked()
{
    // ui->tableView->setModel(NULL);
    // QString name=ui->txtName->text();
    // dbM.addReport(name, *model);
    // ui->tableView->setModel(NULL);
    // model->select();
    // RefreshReport();

    // model->select();

    // QSqlDatabase db=QSqlDatabase::addDatabase("QPSQL");
    // db.setHostName("localhost");
    // db.setDatabaseName("xpol");
    // db.setPassword("");
    // db.setUserName("postgres");
    // QMessageBox msg;
    // if(db.open()){
        // //msg.setText("Success");
        // QString sql="select * from report";
        // QSqlQuery *query=new QSqlQuery(db);
        // //query->setQuery(sql);
        // query->prepare(sql);
        // query->exec();

        // QSqlQueryModel *modelReport=new QSqlQueryModel();
        // modelReport->setQuery(*query);
        // ui->tableView->setModel(modelReport);

    // }else{

        // msg.setText("Failed");
    // }
    // msg.exec();
}
