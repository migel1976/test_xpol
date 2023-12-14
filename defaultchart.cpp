// #include "defaultchart.h"

// DefaultChart::DefaultChart()
// {

// }

// #include "defaultchart.h"

// defaultchart::defaultchart(QObject *parent)
    // : QObject{parent}
// {

// }

// #include "defaultchart.h"

// defaultchart::defaultchart()
// {

// }

#include "defaultchart.h"
#include <QwtMath>
#include <QwtScaleEngine>
#include <QwtSymbol>
#include <QwtPlotGrid>
#include <QwtPlotMarker>
#include <QwtPlotCurve>
#include <QwtLegend>
#include <QwtText>
#include <QwtPlotCanvas>

// DefaultChart::DefaultChart(QwtPlot *uiplot, double freqmax, double freqmin, double ampmax, double ampmin)
DefaultChart::DefaultChart(QwtPlot *uiplot)
{
    plot=uiplot;
    // plot->setAutoReplot(false);
    plot->detachItems(QwtPlotItem::Rtti_PlotItem, true);
    // plot->axisScaleEngine(QwtPlot::xBottom)->setAttribute(QwtScaleEngine::Floating, true);
    // plot->setAxisScale(QwtPlot::xBottom, freqmin, freqmax);
    // plot->setAxisScale(QwtPlot::yLeft, ampmin, ampmax);
    // legend
    QwtLegend* legend = new QwtLegend;
    plot->insertLegend( legend, QwtPlot::BottomLegend );

    // grid
    QwtPlotGrid* grid = new QwtPlotGrid;
    grid->enableXMin( true );
    grid->setMajorPen( Qt::white, 0, Qt::DotLine );
    grid->setMinorPen( Qt::gray, 0, Qt::DotLine );
    grid->attach( plot );

    // axes
    plot->setAxisTitle( QwtAxis::XBottom, "Frequency" );
    plot->setAxisTitle( QwtAxis::YLeft, "Amplitude [dB]" );
    plot->setCanvasBackground( Qt::black);
    plot->setAxisMaxMajor( QwtAxis::XBottom, 6 );
    plot->setAxisMaxMinor( QwtAxis::XBottom, 9 );
}

QwtPlot* DefaultChart::getPlot(){
    return plot;
}
