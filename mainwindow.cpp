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
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

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

    plot=ui->qwtPlot;
    defaultChart=new DefaultChart(plot);
    QwtPlot* chart=defaultChart->getPlot();
    zoomer = new Zoomer(chart->canvas());

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

    QString val;
    QFile file;
    // file.setFileName("/home/mike/copol.json");
    file.setFileName("/home/mike/trace.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val=file.readAll();
    file.close();
    // qWarning()<<val;

    QJsonDocument copol=QJsonDocument::fromJson(val.toUtf8());
    dbM.addReport(name, cf, copol);
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
    QModelIndex idxCopol=model->index(rowId,3);
    QString val=idxCopol.data().toString();
    qWarning()<<"val is "<<val;
    int lend=8190;
    double *dcopol=ReadJSONDB(val, lend);
    double cf=11200;
    double span=10;
    double startFreq=cf-span/2;
    double freq[lend];

    for(int i=0; i<lend;i++){
        // double f=freq[i]=startFreq+i*span/lend-1;
        double f=startFreq+i*span/lend-1;
        freq[i]=f;
    }

    defaultChart=new DefaultChart(plot);
    QwtPlot* chart=defaultChart->getPlot();
    chartXpol=new ChartXpol(chart);
    chartXpol->showData(freq, dcopol, dcopol, lend);
    delete []dcopol;
    SetZoomer(chart);
}

void MainWindow::SetZoomer(QwtPlot *chart){
    if(zoomer!=0){
            delete zoomer;
    }
    zoomer = new Zoomer(chart->canvas());
    // zoomer->setAxes(QwtPlot::xBottom, QwtPlot::yLeft);
}

double* MainWindow::ReadJSONDB(QString val, int &lend){
        QJsonDocument d=QJsonDocument::fromJson(val.toUtf8());
        QJsonObject sett2=d.object();
        QJsonValue value=sett2.value("amp");
        QJsonObject obj=value.toObject();
        QJsonArray arr=value.toArray();
        int len=arr.size();
        lend=len;
        double *copol=new double[len];
        for(int count=0;count<len; count++){
                QString itemStr=arr[count].toString();
                double item=itemStr.toDouble();
                copol[count]=item;
                // qWarning<<copol[count]<<"\n";
        }
        return copol;
}

void MainWindow::on_btnLoadJSON_clicked()
{

    QString val;
    QFile file;
    // file.setFileName("/home/mike/copol_correct.json");
    file.setFileName("/home/mike/trace.json");
    // file.setFileName("~/trace.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val=file.readAll();
    file.close();
    // qWarning()<<val;

    QJsonDocument d=QJsonDocument::fromJson(val.toUtf8());
    QJsonObject sett2=d.object();
    QJsonValue value=sett2.value("amp");
    QJsonObject obj=value.toObject();
    QJsonArray arr=value.toArray();
    qWarning()<<"arr "<<arr;
    int len=arr.size();
    double copol[len];
    for(int count=0;count<len; count++){
        // double item=arr[count].toDouble();
        QString item=arr[count].toString();
        qWarning()<<"item "<<item;
        // double item=item.toDouble();
        // copol[count]=item;
        copol[count]=item.toDouble();
    }
    double cf=12200;
    double span=1;
    double startFreq=cf-span/2;
    double freq[len];

    for(int i=0; i<len;i++){
            // double f=freq[i]=startFreq+i*span/len-1;
            double f=startFreq+i*span/len-1;
            freq[i]=f;
            qWarning()<<"freq["<<i<<"]"<<freq[i];
            qWarning()<<"amp["<<i<<"]"<<copol[i];
    }

    // defaultChart=new DefaultChart(plot);
    // QwtPlot* chart=defaultChart->getPlot();
    // chartXpol=new ChartXpol(chart);
    // chartXpol->showData(freq, copol, copol, len);
    // SetZoomer(chart);

}

