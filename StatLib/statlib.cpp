#include "statlib.h"


StatLib::StatLib()
{
}

StatLib::ErrCode StatLib::TriangleAreaSolve(double x1, double y1, double x2, double y2, double x3, double y3, double& res)
{
    if (x1 == x2 && y1 == y2) return INVALID_DATA;
    if (x1 == x3 && y1 == y3) return INVALID_DATA;
    if (x3 == x2 && y3 == y2) return INVALID_DATA;

    //if (!isdigit(x1) || !isdigit(x2) || !isdigit(x3) || !isdigit(y1) || !isdigit(y2) || !isdigit(y3))
    //{
    //	return INVALID_DATA;
    //}

    double a1 = sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
    double b1 = sqrt((x3 - x1)*(x3 - x1) + (y3 - y1)*(y3 - y1));
    double c1 = sqrt((x3 - x2)*(x3 - x2) + (y3 - y2)*(y3 - y2));

    double p = (a1 + b1 + c1) / 2.0;

    double S = sqrt(p*(p - a1)*(p - b1)*(p - c1));

    res = S;

    return SUCCESS;
}




