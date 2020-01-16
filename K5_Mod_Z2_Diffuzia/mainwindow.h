#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qchartviewer.h>
#include <vector>

namespace Ui {
class MainWindow;
}

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    SurfaceChart *c;

    int angle = 100;

    struct coord_surface
    {
        int x;
        int y;
        int z;

        coord_surface(int x, int y, int z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }
    };

//    double *chd_x;
//    double *chd_y;
//    double *chd_z;

    int step;
    int CountOfSteps;
    QVector<double> CoordX;
    QVector<QVector<double>> ConcentrationOnXAtStep;

    void createSurface();
    void createArrayForCartD(double* x,   double* y,     double* z,
                               int hight,    int weight,
                             vector<coord_surface> &coord
    );
    void findPointsOnField( int x,  int y,  int n,
                            QVector <QVector <bool> > &point,
                            vector <coord_surface> &coord
    );

private slots:
    void on_pushButton_GenStart_clicked();

    void on_pushButton_clicked();

    void on_pushButton_Animation_clicked();


    void slotTimerAlarm();


    void on_pushButton_Concentration_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalSlider_2_valueChanged(int value);

    void on_pushButton_GenStart_1000_clicked();

    void on_pushButton_GenStart_Ogran_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;

};

#endif // MAINWINDOW_H
