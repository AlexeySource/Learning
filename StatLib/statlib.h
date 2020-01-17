#ifndef STATLIB_H
#define STATLIB_H
#include <QDebug>

enum ErrCode
{
    INVALID_DATA,
    SUCCESS,
};

class StatLib
{

public:
    StatLib();

    ErrCode TriangleAreaSolve(double x1, double y1, double x2, double y2, double x3, double y3, double& res);
};

#endif // STATLIB_H
