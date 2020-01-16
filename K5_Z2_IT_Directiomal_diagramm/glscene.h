#ifndef GLSCENE_H
#define GLSCENE_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QGLWidget>
#include <QtOpenGL>
#include <QTimer>
#include <GL/glu.h>
#include <stdlib.h>     // srand, rand
#include <time.h>       // time
#include <math.h>
#include <QDebug>
#include "mainwindow.h"


class glScene : public QGLWidget
{
    Q_OBJECT


public:


    explicit glScene(QWidget *parent = 0);

    double N = 9;
    double D =1;
    double w1 = N*D;
    double per = 1;

    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

    void DrawGrid(double h);
    void DrawPoints();
    void CoordsNorm();

    void drawCircle(double x, double y, double r, int amountSegments);


    void mousePressEvent(QMouseEvent *me);

    struct coords
    {
     double x;
     double y;
    };

    QVector<coords> point;

};

#endif // GLSCENE_H
