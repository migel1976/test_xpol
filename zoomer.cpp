// #include "zoomer.h"

// Zoomer::Zoomer()
// {

// }

// #include "zoomer.h"

// zoomer::zoomer(QObject *parent)
    // : QObject{parent}
// {

// }

// #include "zoomer.h"

// zoomer::zoomer(QObject *parent)
    // : QObject{parent}
// {

// }

// #ifndef ZOOMER_H

// #endif // ZOOMER_H



#include "zoomer.h"
#include <QColor>
#include <QPen>
#include <QwtDateScaleDraw>
#include <QwtDateScaleEngine>

Zoomer::Zoomer( QWidget* canvas)
            : QwtPlotZoomer( canvas )
{
        plot=(QwtPlot*)canvas;
        setZoomBase();
        setRubberBandPen( QColor( Qt::red ) );
        setTrackerMode( QwtPlotPicker::AlwaysOn );

        setMousePattern( QwtEventPattern::MouseSelect2,
                         Qt::RightButton, Qt::ControlModifier );
        setMousePattern( QwtEventPattern::MouseSelect3,
                         Qt::RightButton );
        setEnabled(true);
        type=1;
}

Zoomer::Zoomer( QWidget* canvas, int measType)
            : QwtPlotZoomer( canvas )
{
        plot=(QwtPlot*)canvas;
        setZoomBase();
        setRubberBandPen( QColor( Qt::red ) );
        setTrackerMode( QwtPlotPicker::AlwaysOn );

        setMousePattern( QwtEventPattern::MouseSelect2,
                         Qt::RightButton, Qt::ControlModifier );
        setMousePattern( QwtEventPattern::MouseSelect3,
                         Qt::RightButton );
        setEnabled(true);
        type=measType;
}

Zoomer::~Zoomer( )
{
    setZoomBase(true);
}

QwtText Zoomer::trackerTextF( const QPointF& pos ) const
{
        QString s;
        if(type==1){
        s+="Частота ";
        s+=QString::number(pos.x(),'f',6);
        s+=" МГц";
        s+='\r\n';
        s+="Уровень ";
        s+=QString::number(pos.y(),'f',2);
        s+=" дБм";
        }

        if(type==2){
        s+="Градусы ";
        s+=QString::number(pos.x(),'f',2);
        s+='\r\n';
        s+="Уровень ";
        s+=QString::number(pos.y(),'f',2);
        s+=" дБ";
        }

        if(type==3){
        // QDateTime tm = QDateTime::fromTime_t(pos.x());
        QDateTime tm= QwtDate::toDateTime(pos.x()).toLocalTime();
        s+="Время ";
        s+=tm.toString("hh:mm:ss");
        s+='\r\n';
        s+="Частота ";
        s+=QString::number(pos.y(),'f',6);
        s+=" МГц";
        }

        if(type==4){
        // QDateTime tm = QDateTime::fromTime_t(pos.x());
        QDateTime tm= QwtDate::toDateTime(pos.x()).toLocalTime();
        s+="Время ";
        s+=tm.toString("hh:mm:ss");
        s+='\r\n';
        s+="Уровень ";
        s+=QString::number(pos.y(),'f',2);
        s+=" дБм";
        }

        if(type==5){
        s+="Частота ";
        s+=QString::number(pos.x(),'f',6);
        s+=" МГц";
        s+='\r\n';
        s+="Уровень ";
        s+=QString::number(pos.y(),'f',2);
        s+=" дБ";
        }

        QwtText text( s );
        text.setColor( Qt::white );

        QColor c = rubberBandPen().color();
        text.setBorderPen( QPen( c ) );
        text.setBorderRadius( 6 );
        c.setAlpha( 170 );
        text.setBackgroundBrush( c );

        return text;
}
