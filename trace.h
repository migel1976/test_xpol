#ifndef TRACE_H
#define TRACE_H

#include <QMessageBox>

class trace
{
public:
    trace(double* trace, int len);
    double* getTrace();

private:
    double *copol;

};

#endif // TRACE_H
