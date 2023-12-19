#ifndef INSERTREPORT_H
#define INSERTREPORT_H

#include <QDialog>
#include <QJsonDocument>

namespace Ui {
class insertreport;
}

class insertreport : public QDialog
{
    Q_OBJECT

public:
    // explicit insertreport(QWidget *parent = nullptr);
    explicit insertreport(QJsonDocument doc, QWidget *parent = nullptr);
    ~insertreport();

private slots:
    void on_btnAdd_clicked();

private:
    Ui::insertreport *ui;
    QJsonDocument jsonDoc;
};

#endif // INSERTREPORT_H
