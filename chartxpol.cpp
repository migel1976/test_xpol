// #include "chartxpol.h"

// ChartXpol::ChartXpol()
// {

// }

// #include "chartxpol.h"

// chartxpol::chartxpol(QObject *parent)
    // : QObject{parent}
// {

// }

// #include "chartxpol.h"

// chartxpol::chartxpol()
// {

// }


#include "chartxpol.h"

#include <QwtMath>
// #include <qwt/qwt_math.h>
#include <QwtScaleEngine>
// #include <qwt/qwt_scale_engine.h>
#include <QwtSymbol>
// #include <qwt/qwt_symbol.h>
#include <QwtPlotGrid>
// #include <qwt/qwt_plot_grid.h>
#include <QwtPlotMarker>
// #include <qwt/qwt_plot_marker.h>
#include <QwtPlotCurve>
// #include <qwt/qwt_legend.h>
#include <QwtLegend>
// #include <qwt/qwt_text.h>
#include <QwtText>
// #include <qwt/qwt_plot_canvas.h>
#include <QwtPlotCanvas>
// #include <qwt/qwt_scale_draw.h>
#include <QwtScaleDraw>
// #include <qwt/qwt_scale_engine.h>
#include <QwtScaleEngine>
// #include <qwt/qwt_plot.h>
#include <QwtPlot>
// #include <qwt/qwt_plot_zoomer.h>
#include "QwtPlotZoomer"
#include <QPainterPath>
// #include <qwt/qwt_painter.h>
// #include <qwt/qwt.h>

    class ArrowSymbol : public QwtSymbol
    {
      public:
        ArrowSymbol()
        {
            QPen pen( Qt::black, 0 );
            pen.setJoinStyle( Qt::MiterJoin );

            setPen( pen );
            setBrush( Qt::red );

            QPainterPath path;
            path.moveTo( 0, 8 );
            path.lineTo( 0, 5 );
            path.lineTo( -3, 5 );
            path.lineTo( 0, 0 );
            path.lineTo( 3, 5 );
            path.lineTo( 0, 5 );

            QTransform transform;
            transform.rotate( -30.0 );
            path = transform.map( path );

            setPath( path );
            setPinPoint( QPointF( 0, 0 ) );

            setSize( 10, 14 );
        }
    };

    class LegendItem : public QwtPlotLegendItem
    {
      public:
        LegendItem()
        {
            setRenderHint( QwtPlotItem::RenderAntialiased );

            const QColor c1( Qt::white );

            setTextPen( c1 );
            setBorderPen( c1 );

            QColor c2( Qt::gray );
            c2.setAlpha( 200 );

            setBackgroundBrush( c2 );
        }
    };

ChartXpol::ChartXpol(QwtPlot *uiplot)
{
    plot=uiplot;
    QwtLegend* legend = new QwtLegend;
    plot->insertLegend( legend, QwtPlot::TopLegend );

    m_legendItem = new LegendItem();
    m_legendItem->setMaxColumns(2);
    // m_legendItem->setAlignmentInCanvas( Qt::Alignment(Qt::TopLeftCorner));

    m_legendItem->setBorderRadius( 4 );
    m_legendItem->setMargin( 0 );
    m_legendItem->setSpacing( 4 );
    m_legendItem->setItemMargin( 2 );

    QFont font = m_legendItem->font();
    font.setPointSize(10);
    m_legendItem->setFont( font );
    m_legendItem->attach( plot );

    // grid
    QwtPlotGrid* grid = new QwtPlotGrid;
    grid->enableXMin( true );
    grid->setMajorPen( Qt::white, 0, Qt::DotLine );
    grid->setMinorPen( Qt::gray, 0, Qt::DotLine );
    grid->attach( plot );

    // axes
    plot->setAxisTitle( QwtAxis::XBottom, "Частота, МГц" );
    plot->setAxisTitle( QwtAxis::YLeft, "Амлпитуда, дБм" );

    plot->setCanvasBackground( Qt::black);
    plot->setAxisMaxMajor( QwtAxis::XBottom, 6 );
    plot->setAxisMaxMinor( QwtAxis::XBottom, 9 );


    // curves
    m_curve1 = new QwtPlotCurve( "Copol" );
    // m_curve1 = new QwtPlotCurve();
    m_curve1->setRenderHint( QwtPlotItem::RenderAntialiased );
    m_curve1->setPen( Qt::yellow );
    m_curve1->setItemAttribute(QwtPlotItem::Legend, false);
    // m_curve1->setLegendAttribute( QwtPlotCurve::LegendShowLine );
    m_curve1->setYAxis( QwtAxis::YLeft );
    m_curve1->attach( plot );

    // curves
    m_curve2 = new QwtPlotCurve( "Xpol" );
    m_curve2->setRenderHint( QwtPlotItem::RenderAntialiased );
    m_curve2->setPen( Qt::green );
    m_curve2->setYAxis( QwtAxis::YLeft );
    m_curve2->attach( plot );
}

// void ChartXpol::showData( const double* frequency, const double* amplitude, int count )
void ChartXpol::showData( const double* freq, const double* copol, const double* xpol, int count )
// void ChartXpol::showData( double* freq, double* copol, double* xpol, int count )
// void ChartXpol::showData( double freq, double copol, double xpol, int count )
// void ChartXpol::showData( const double* freq, const double* copol, const double* xpol, int count )
{
    double freqmax,freqmin, ampmax, ampmin, ampcopolmax, ampcopolmin, ampxpolmax, ampxpolmin;
    freqmax=freqmin=freq[0];
    ampcopolmax=ampcopolmin=copol[0];
    ampxpolmax=ampxpolmin=xpol[0];
    for(int i=0;i<count;i++){
        if(freqmax<freq[i]){ freqmax=freq[i];}
        else{freqmin=freq[i];}

        if(ampcopolmax<copol[i]){ ampcopolmax=copol[i];}
        else{ampcopolmin=copol[i];}

        if(ampxpolmax<xpol[i]){ampxpolmax=xpol[i];}
        else{ampxpolmin=xpol[i];}
    }
    if(ampcopolmax>ampxpolmax){ampmax=ampcopolmax;}
    else{ampmax=ampxpolmax;}

    if(ampcopolmin<ampxpolmin){ampmin=ampcopolmin;}
    else{ampmin=ampxpolmin;}

    plot->setAxisScale(QwtPlot::xBottom, freqmin, freqmax);
    plot->setAxisScale(QwtPlot::yLeft, ampmin-10, ampmax+10);


    double freqMarker=freqmin+((freqmax-freqmin)/2);
    // an arrow at a specific position
    QwtPlotMarker* mPos = new QwtPlotMarker( "Marker" );
    mPos->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    mPos->setItemAttribute( QwtPlotItem::Legend, false);
    // mPos->setSymbol( new ArrowSymbol() );

    mPos->setSymbol( new QwtSymbol( QwtSymbol::Diamond,
        QColor( Qt::yellow ), QColor( Qt::green ), QSize( 8, 8 ) ) );
    // mPos->setSymbol( QwtSymbol::Diamond );
    mPos->setValue( QPointF( freqMarker, ampmax));
    QwtText *txt=new QwtText(QString("copol"));
    txt->setColor(Qt::red);
    txt->setBackgroundBrush(QBrush(Qt::white));
    mPos->setLabel(*txt);
    // mPos->setLabel( QwtText(QString( "copol"), QTextFormat());
    mPos->setLabelAlignment( Qt::AlignRight | Qt::AlignBottom );
    mPos->attach( plot );

    m_curve1->setSamples( freq, copol, count );
    m_curve2->setSamples( freq, xpol, count );
    plot->setAutoReplot( true );
}
