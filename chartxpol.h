// #ifndef CHARTXPOL_H
// #define CHARTXPOL_H


// class ChartXpol
// {
// public:
    // ChartXpol();
// };

// #endif // CHARTXPOL_H

// #ifndef CHARTXPOL_H
// #define CHARTXPOL_H

// #include <QObject>

// class chartxpol : public QObject
// {
    // Q_OBJECT
// public:
    // explicit chartxpol(QObject *parent = nullptr);

// signals:

// };

// #endif // CHARTXPOL_H

// #ifndef CHARTXPOL_H
// #define CHARTXPOL_H


// class chartxpol
// {
// public:
    // chartxpol();
// };

// #endif // CHARTXPOL_H

#ifndef CHARTXPOL_H
#define CHARTXPOL_H

#include <QObject>
// #include <qwt/qwt_plot.h>
// #include <qwt/qwt_plot_legenditem.h>
#include <QwtPlot>
#include "QwtPlotLegendItem"

// #include "./zoomer.h"
class QwtPlotCurve;
class QwtPlotMarker;

class ChartXpol : public QwtPlot
{
public:
    ChartXpol(QwtPlot *plot);
    // ChartXpol(QwtPlot *uiplot, double freqMarker, double apmMarker);
    // void showData( const double* frequency, const double* amplitude, int count );
    void showData( const double* frequency, const double* copol, const double* xpol, int count );
    // void showData( double* frequency, double* copol, double* xpol, int count );
    // void showData( double frequency, double copol, double xpol, int count );
    // void showData( const double* frequency, const double* copol, int count );

private:
    QwtPlot *plot;
    QwtPlotCurve* m_curve1;
    QwtPlotCurve* m_curve2;
    QwtPlotLegendItem* m_legendItem;

};

#endif // CHARTXPOL_H
