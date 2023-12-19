#include "trace.h"
#include <QDebug>

trace::trace(double* trace, int len)
{
    qWarning()<<"Trace constructor"<<trace[9];
    int i=0;
    copol=new double[len];
    while(i<len){
        copol[i]=trace[i];
        i++;
    }
    qWarning()<<"Trace constructor copol"<<copol[9];

}

double* trace::getTrace(){
    double tmp[601];
    int i=0;
    while(i<601){
        tmp[i]=copol[i];
        i++;
    }
    qWarning()<<"Trace::getTrace tmp"<<tmp[9];
    return copol;
}
