#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int counter = 0;
    QVector<double> iter;
    QVector<double> iter1;
    QVector<double> iter2;
    QVector<double> iter3;
    QVector<double> Fi1;

    double v1;
    double v2;
    double v3;
    double T1;
    double T2;
    double T3;


private slots:

    void on_N_spinbox_valueChanged(int arg1);

    void on_horizontalSlider_valueChanged(int value);

    void slotTimerAlarm();

    void on_pushButton_Animation_clicked();

    void on_pushButton_Animation_stop_clicked();

    void on_N_spinbox_frames_count_valueChanged(int arg1);

    void on_pushButton_4_clicked();

    void on_N_spinbox_2_valueChanged(int arg1);

    void on_doubleSpinBox_valueChanged(double arg1);



    void on_pushButton_Save1_clicked();

    void on_pushButton_Plot3Maxwell_clicked();

    void on_pushButton_Save2_clicked();

    void on_pushButton_Save3_clicked();

private:
    Ui::MainWindow *ui;

    QTimer *timer;
};

#endif // MAINWINDOW_H
