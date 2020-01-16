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
#include <QVector>
#include "mainwindow.h"




class glScene : public QGLWidget
{
public:
    explicit glScene(QWidget *parent = nullptr);

    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

    double N = 100;
    double D =1;
    double h1 = N*D;
    double w1 = 2*N*D;
    int frames = 50;
    double counter;

    void DrawGrid(double hGrid);
    void DrawPoints();
    void GenStart();
    void GenStart1000();
    void GenStartCenter();
    void Diffuzia();
    void InfinitySource();

    void Movefor();

    bool bStart = false;
    void mousePressEvent(QMouseEvent *me);
    QVector<QVector<bool>> isPoint;
    QVector<QVector<int>> isPointint;
    QVector<double> ConcentrationOnX;

    struct coords
    {
     int x;
     int y;
    };


    //QVector<QVector<coords>> point;
    QVector<coords> point;


    void MovePoint(coords &point);

};

#endif // GLSCENE_H
