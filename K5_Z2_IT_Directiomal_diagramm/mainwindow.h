#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qchartviewer.h>
#include <qcustomplot.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    SurfaceChart *c;// = new SurfaceChart(700, 600);



    QVector<QVector<double>> z;
    double R = 200;
    double lyambda = 1;

//    int size = R*R+1;
//    double* dataX=new double[401];
//    double* dataY=new double[401];


    double dataX[401];
    double dataY[401];

    double dataZ[(int)(sizeof(dataX) / sizeof(dataX[0])) * (int)(sizeof(dataY) / sizeof(dataY[0]))];

    double VertAngleValue = 20;
    double HorAngleValue = 0;


    struct coords1
    {
     double x;
     double y;
    };

    QVector<coords1> point1;




private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_GenField_clicked();
    DoubleArray vectorToArray(std::vector<double>& v);

    void on_horizontalSlider_valueChanged(int value);

    void on_verticalSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
