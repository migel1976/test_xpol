#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include "dbmanager.h"
#include "insertreport.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void InsertData(QString name);


private slots:
    void on_pushButton_clicked();
    void on_btnAddReport_clicked();
    void RefreshReportModel();

private:
    Ui::MainWindow *ui;
    QSqlTableModel *model;
    insertreport *insertDlg;
    void RefreshReport();
    // DbManager dbM;
signals:
    void modelReportChanged();

};
#endif // MAINWINDOW_H
