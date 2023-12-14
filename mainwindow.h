#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include "dbmanager.h"
#include "insertreport.h"

#include <QwtSymbol>
#include <QwtPlotGrid>
#include <QwtLegend>
#include <QwtPlotCurve>
#include <QwtScaleEngine>
#include <QwtScaleDraw>

#include "defaultchart.h"
#include "chartxpol.h"
#include "zoomer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void InsertData(QString name, int cf);


private slots:
    void on_btnAddReport_clicked();
    void on_btnDeleteReport_clicked();

    void RefreshReportModel();

    void on_tableView_clicked(const QModelIndex &index);

    void on_btnLoadJSON_clicked();

private:
    Ui::MainWindow *ui;
    QSqlTableModel *model;
    insertreport *insertDlg;
    void ConnectReport();

    DefaultChart *defaultChart;

    QwtPlot *plot;
    ChartXpol *chartXpol;
    Zoomer *zoomer;
    void SetZoomer(QwtPlot *chart);
    double* ReadJSONDB(QString val, int &lend);

    QString glRow;
signals:
    void modelReportChanged();


};
#endif // MAINWINDOW_H
