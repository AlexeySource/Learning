#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <cmath>
#include <QDebug>
#include <qcustomplot.h>
#include <QFile>
#include <QList>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    int N;// = 2048;
    QVector<double>w_t;
    QVector<double>lfm;
    QVector<double>t;
     QVector<double>U;
     QVector<double>sig;


     QVector<double>SpeCtr;
      QVector<double>t1;
      QVector<double>Line;
      QVector<double>x=QVector<double>(2);
      QVector<double>y=QVector<double>(2);
      QVector<double>x2=QVector<double>(2);
      QVector<double>y2=QVector<double>(2);
      QCPCurve *verticalLine1;
      QCPCurve *verticalLine2;

      int N_INWND;
      int wnd_count;

      //QVector<double>rxx2;

      QVector<QVector<double>>okna;

      QVector<QVector<double>>okna_spectrov;
      QVector<QVector<double>>okna_rxx;

     struct cmplx {float real; float image; } ;
     cmplx*data=new cmplx[N];

    double h=1;
    double wx;
    double ax;
   // double w0;
    double w1; //несущая частота
    double alpha; //глубина модуляции
    double tx;
    int b;
    double A;
    QVector<double> TickValues{0, 20, 40, 60, 80, 100, 120};
    QVector<double> TickValues2{0, 20, 40, 60, 80, 100, 120};
    QVector<QString> TickLabels{"0", "20%","40%","60%","80%","100%","120%"};
    QVector<QString> TickLabels2;


    //Для синусоид//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    double X(double A, double f, double t); // функция синуса

        int svd_hestenes(int m_m, int n_n, double * a, double * u, double * v, double * sigma);//функция морозова

        double noise_procent;// осчеты сигнала
        double porog;//порог
        // Амплитуды
        int Amplituda1;
        int Amplituda2;
        int Amplituda3;
        int Amplituda4;
        int Amplituda5;
        int Amplituda6;
        int Amplituda7;
        int Amplituda8;
        int Amplituda9;
        int Amplituda10;
        // Частоты
        double Chastota1;
        double Chastota2;
        double Chastota3;
        double Chastota4;
        double Chastota5;
        double Chastota6;
        double Chastota7;
        double Chastota8;
        double Chastota9;
        double Chastota10;

        int P_mod;//порядок модели

        int shag;//кол-во разбиений
        int koliter; //кол-во итераций
        double *kvadrad;
        double *research; //массив исследования
        double *s;//массив шум+сигнал
        double *m;//рандом
        double Es;// энергия сигнала
        double Eh;// энергия шума
        double Ef;// энергия спектра
        double *Mg;// массив гауссового шума
        double Gauss;//энергия гауссового шума
        int k;//количество случайных чисел
        double alfa;//коэффициент, необходимый для того, чтобы белый шум стал пропорционален энергии сигнала
        double d; // доля шума
        int M =80;
        vector<double> eigen_values;
        int i_on_porog;
        vector<double> prediction;
        double noise_energy;



        //           Multitaper data

        QVector<double> mass1;
        QVector<double> mass2;
        QVector<double> mass3;
        QVector<double> mass4;
        QVector<double> mass5;
        QVector<QVector<double>>okna1;
        QVector<QVector<double>>okna2;
        QVector<QVector<double>>okna3;
        QVector<QVector<double>>okna4;
        QVector<QVector<double>>okna5;





private slots:
    void on_pushButton_clicked();
    double func_w_t_plus(double wx,double ax, int bx, double tx);
    double func(double t);
    void FUR(struct cmplx *data,int n,int is);
    void razb_na_okna();
    void FUR_FOR_WND(QVector<QVector<double>>okna,int N_INWND, int nmb_wnd);
    void nomer_1();


    void ReadMtpWnds();
    void CreateMtpWnds();
    void FUR_FOR_MtpWND(/*QVector<QVector<double>>okna,*/ int N_INWND, int nmb_wnd);

    void BurgAlgorithm( vector<double> &coeffs, const vector<double> &x ) ;


    QVector<double> rxxFunc(QVector<double>data_in_wnd, int N_INWND);
    void rxxFunc_FOR_WND(QVector<QVector<double>>okna,int N_INWND, int nmb_wnd);
    //QVector<QVector<double>> gen_rxx(QVector<double> & SIGN, int rxx_type, bool full_size, int nmb_wnd);

    vector<vector<double>> gen_rxx(QVector<QVector<double>>okna, int nmb_wnd, int rxx_type, bool full_size);
    int svd_hestenes(int m_m, int n_n, vector<vector<double>> &WNDM, vector<vector<double>> &U, vector<vector<double>> &V, vector<vector<double>> &SIGMA);
    void kazf(vector<vector<double>> &a, vector<double> &b, vector<double> &x);
    //vector<double> gen_armodel(vector<double> SIGN, vector<double> koeff);
    vector<double> gen_armodel(QVector<QVector<double>> okna, int nmb_wnd, vector<double> koeff);
    double On_porog(vector<double>&S,double porog);
    vector<double> svobodn(vector<vector<double>>&S, int porog);
    QVector<double> GaussRandom(int length);
    double Energy(QVector<double> & S);
    QVector<double> AddNoise(QVector<double>&Signal, double noise_procent) ;

    void on_pushButton_2_clicked();
    void on_horizontalSlider_valueChanged(int value);
    void method_select();
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
