// #ifndef ZOOMER_H
// #define ZOOMER_H


// class Zoomer
// {
// public:
    // Zoomer();
// };

// #endif // ZOOMER_H

// #ifndef ZOOMER_H
// #define ZOOMER_H

// #include <QObject>

// class zoomer : public QObject
// {
    // Q_OBJECT
// public:
    // explicit zoomer(QObject *parent = nullptr);

// signals:

// };

// #endif // ZOOMER_H

// #ifndef ZOOMER_H
// #define ZOOMER_H

// #include <QObject>

// class zoomer : public QObject
// {
    // Q_OBJECT
// public:
    // explicit zoomer(QObject *parent = nullptr);

// signals:

// };

// #endif // ZOOMER_H

#ifndef ZOOMER_H
#define ZOOMER_H
#include <QwtPlot>
#include <QwtPlotZoomer>
#include <QwtText>
#include <QMessageBox>

class Zoomer : public QwtPlotZoomer
{
public:
    Zoomer(QWidget*);
    Zoomer(QWidget* canvas, int measType);
    ~Zoomer();
protected:
    virtual QwtText trackerTextF( const QPointF& pos ) const QWT_OVERRIDE;
    QMessageBox msg;
    QwtPlot *plot;
    int type;
};

#endif // ZOOMER_H
