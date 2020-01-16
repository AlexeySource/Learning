#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qcustomplot.h>
#include <QImage>
#include <QDebug>
#include <QDir>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QVector<double>t;

    QVector<QVector<double>> Image;
    QVector<QVector<double>> ImageSrc;
    QVector<QVector<int>> ImageSrcIntPix;
    QVector<QVector<int>> VualMass;
    QVector<QVector<int>> ImgPlusVual;


    QVector<QVector<int>> ImageSrcMedian;
    QVector<QVector<int>> ImageSrcLinear;
    QVector<QVector<int>> ImageSrcOrig;
    QVector<QVector<int>> ImageForeMinus;
    QVector<QVector<int>> ImageAfterMinus;
    QVector<QVector<double>> ImageGauss;
    QVector<QVector<int>> ImageGaussInt;

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
    double alpha;


    bool wnd3x3 = false;
    bool wnd5x5 = false;

    int w_size;

private slots:

    double Eps(QVector<QVector<int>> Image, QVector<QVector<int>> ImageRestored);

    double GetContast(QVector<QVector<int>> Image);
    QVector<QVector<int>> IncreaseBrighness(QVector<QVector<int>> Image);
    QVector<QVector<int>> NormaliseImage(QVector<QVector<int>> Image);


    void on_pushButton_Gen_Image_clicked();

    void on_pushButton_MedFilter_2_clicked();

    void on_pushButton_LinFilter_2_clicked();

    void on_pushButton_LinFilter_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_IncreaseBrightness_clicked();




    void on_pushButton_analise_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
