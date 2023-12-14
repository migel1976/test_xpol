// #ifndef DEFAULTCHART_H
// #define DEFAULTCHART_H


// class DefaultChart
// {
// public:
    // DefaultChart();
// };

// #endif // DEFAULTCHART_H

// #ifndef DEFAULTCHART_H
// #define DEFAULTCHART_H

// #include <QObject>

// class defaultchart : public QObject
// {
    // Q_OBJECT
// public:
    // explicit defaultchart(QObject *parent = nullptr);

// signals:

// };

// #endif // DEFAULTCHART_H



#ifndef DEFAULTCHART_H
#define DEFAULTCHART_H

// class defaultchart
// {
// public:
    // defaultchart();
// };


#include <QObject>
#include <QwtPlot>
// #include <zoomer.h>

class QwtPlotCurve;

class DefaultChart : public QwtPlot
{
public:
    DefaultChart(QwtPlot *plot);
    // DefaultChart(QwtPlot *uiplot, double freqmax, double freqmin);
       // DefaultChart(QwtPlot *uiplot, double freqmax, double freqmin, double ampmax, double ampmin);
    QwtPlot* getPlot();

private:
    QwtPlot *plot;
    // Zoomer *zoomer;
};

#endif // DEFAULTCHART_H
