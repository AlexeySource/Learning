#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <qcustomplot.h>
#include <cmath>
#include <math.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    int N;

    double A1;
    double X01;
    double Y01;
    double SigmaX1;
    double SigmaY1;
    double A2;
    double X02;
    double Y02;
    double SigmaX2;
    double SigmaY2;
    double A3;
    double X03;
    double Y03;
    double SigmaX3;
    double SigmaY3;
    double A4;
    double X04;
    double Y04;
    double SigmaX4;
    double SigmaY4;
    double A5;
    double X05;
    double Y05;
    double SigmaX5;
    double SigmaY5;

    double IIm;
    double IImSh;


    QVector<double>t;
    QVector<QVector<double>> Image;
    QVector<QVector<double>> ImageClear;
    QVector<QVector<double>> ImageRestored;
    QVector<QVector<double>> SpectrImage;
    QVector<QVector<double>> SpectrImageCentr;
    QVector<QVector<double>> SpectrImageCleared;
    QVector<QVector<double>> SpectrImageClearedCentr;
    QVector<double>sig;
    //QVector<double>t1;
    double SpectrEnergy00;

    double noise_energy;
    double noise_procent;
    double SpectrEnergyFull;
    double ClearProcent;

    struct cmplx {float real; float image; } ;

    QVector<QVector<cmplx>> data_cmplx;



private slots:


    void FUR(struct cmplx *data,int n,int is);
    void gen_image();
    QVector<double> GaussRandom(int length);
    double Energy(QVector<double> & S);
    double Energy2d(QVector<QVector<double>> & S);
    QVector<double> AddNoise(QVector<double>&Signal, double noise_procent, QVector<QVector<double>> & Signal2d) ;
    void on_pushButtonGenImage_clicked();
    void FUR_For_2D();
    void FUR_For_2D_Obr();
    void ClearSpectr();
    double Eps(QVector<QVector<double>> Image1, QVector<QVector<double>> Image2);
//    void lagrange();
//    void Interpolation();
    QVector<QVector<double>> SpectrImageTransform(QVector<QVector<double>> SpectrImage);

    void on_pushButtonClearSpectr_clicked();
    void on_pushButton_RestoreImage_clicked();
    void on_pushButton_LoadImage_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
