#ifndef INSERTREPORT_H
#define INSERTREPORT_H

#include <QDialog>

namespace Ui {
class insertreport;
}

class insertreport : public QDialog
{
    Q_OBJECT

public:
    explicit insertreport(QWidget *parent = nullptr);
    ~insertreport();

private slots:
    void on_btnAdd_clicked();

private:
    Ui::insertreport *ui;
};

#endif // INSERTREPORT_H
