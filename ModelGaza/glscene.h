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

    template <class Value>
    int Sign(Value Val) {
      if (Val > 0.)  return 1;
      else return -1;
    }


    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

    void Triangulation();

    bool BoolTriangulation = false;
    bool BoolVerle = false;
    bool BoolSlider = false;

    int h1, w1;
    int N=100;
    int SliderMean;
    int frames = 10000;
    double a =  382.e-12; // м


    double tau = 2.*10.e-12; // сек
    //double m = 39.95 * 1.66 *10e-27;
    double m = 66.34 * 1.e-25;
    double hdt = 0.0005;
    double dt = hdt*tau;
    double k = 1;
    double vmax = 40; // м/с

    //double D = 1.648e-21; // эВ
    double D = 0.0103 * 1.6*1.e-19; // эВ

    double sigma = a/(pow(2, 1.0/6.));

    QVector <double> VSredn;
    QVector <QVector <double> > VModVKv;
    QVector <QVector <double> > EnPotChast;
    QVector <double> EnKin;
    QVector <double> EnPot;
    QVector <double> EnFull;
    double T;

    QVector <double> TimeForEnergy;
    QVector<double> IntMass;
    QVector<double> vi;
    QVector<double> Fi;

    QVector<QVector<double>> n;         //n(50,0);
    QVector<double> nsr;



    struct coords
    {
     double x;
     double y;
     double vx;
     double vy;
     double v;
     double Fx;
     double Fy;
     double Ep;
     double Ek;
     int index;
    };


QVector <coords> point;
QVector <QVector <coords> > point2;

//coords *point = new coords[N];

public slots:

void verle();
void DrawSlider();
void slot_VerleButton();
void slot_TriangulationButton();
void slot_CountOfPoints();
void slot_Slider();
void drawCircle(double x, double y, double r, int amountSegments);
double Rasst(double coord1, double coord2);
double Rasst1(double coord1, double coord2);
double K(double r);
void Maxvell();


};

#endif // GLSCENE_H
