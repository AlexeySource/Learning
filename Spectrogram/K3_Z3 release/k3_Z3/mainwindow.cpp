#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}





QVector<double> MainWindow::GaussRandom(int length)
{
    QVector <double> Res;

    for (int i = 0; i < length; i++)
    {
        double rand_i = 0;

        for (int k = 0; k < 12; k++)
        {
            rand_i += ((2 * (double)rand() / RAND_MAX) - 1);
        }

        double rand_norm_i = rand_i / 12;
        Res.push_back(rand_norm_i);
    }

    return  Res;
}

double MainWindow::Energy(QVector<double> & S)
{
    double summ = 0;
    for (int i = 0; i< S.size(); i++)
    {
        summ += S[i] * S[i];
    }
    return summ;
}

QVector<double> MainWindow::AddNoise(QVector<double>&Signal, double noise_procent)
{
    double E_s = Energy(Signal);
    QVector<double> noise = GaussRandom(Signal.size());
    double E_n = Energy(noise);


    double norm_koeff = sqrt(E_s * (noise_procent / 100.) / E_n);

    QVector<double> N;

    for (int i = 0; i < Signal.size(); i++)
    {
        double real = Signal[i]+ norm_koeff*noise[i];
        N.push_back(real);
    }

    noise_energy = E_n * norm_koeff * norm_koeff;
    qDebug()<<"noise_energy: " << noise_energy;
    return N;
}

double MainWindow::func_w_t_plus(double wx,double ax,int bx,double tx)
// tx - время текущее
// wx - начало отсчёта
// ax - тангенс угла наклона
{
    if (std::fmod(tx / (2 * bx),1) <= 0.5)
      return (ax*std::fmod(tx / (2 * bx),1) + wx);
     else
      return (ax*(1-std::fmod(tx / (2 * bx),1)) + wx);
}


double func_w_t(double wx,double ax, double tx)
{
    return ax*tx+wx;
}
////////////////////////////////////////////////////////
double MainWindow::func(double t) //для генерации сигнала
{
    double period = b;
    int n = floor(t / period);
    t -= n * period;
    double result = n * period / 2;
    if ((n % 2) == 0)
    {
        result += (t * t / period / 2);
    }
    else
    {
        result += (t - t * t / period / 2);
    }
    return result;
}

void MainWindow::nomer_1() //генерация сигнала. Это ЛЧМ-МОДУЛЯЦИЯ. Массив U[i] Это массив отсчетов сигнала!!
{
 t[0]=0;
 for(int i=0;i<N-1;i++)
 {
     t[i+1]=t[i]+1;
 }
 for(int i=0;i<N;i++)
 {
     lfm[i]=func(t[i]);
 }

 if (ui->checkBox_Sin->isChecked())
 {
     for (int i = 0; i < sig.size(); i++)
     {
         sig[i]=0;
         sig[i] = sig[i]
             + X(Amplituda1, Chastota1, i)
             + X(Amplituda2, Chastota2, i)
             + X(Amplituda3, Chastota3, i)
             + X(Amplituda4, Chastota4, i)
             + X(Amplituda5, Chastota5, i)
             + X(Amplituda6, Chastota6, i)
             + X(Amplituda7, Chastota7, i)
             + X(Amplituda8, Chastota8, i)
             + X(Amplituda9, Chastota9, i)
             + X(Amplituda10, Chastota10, i);
     }
 }
 else {
 for(int i=0;i<N;i++)
 {
     sig[i]=0;
     sig[i]+=A*sin(w1*t[i] + alpha*lfm[i]);
 }
}

 U = AddNoise(sig,noise_procent);
 /////////////////////////////////////////////////////////////////
}

void MainWindow::FUR(struct cmplx *data,int n,int is) //Сам алгоритм быстрого преобразования фурье
{

    int i,j,istep;
    int m,mmax;
    float r,r1,theta,w_r,w_i,temp_r,temp_i;
    float pi=3.1415926f;

    r=pi*is;
    j=0;
    for(i=0;i<n;i++)
    {
    if(i<j)
        {
        temp_r=data[j].real;
        temp_i=data[j].image;
          data[j].real=data[i].real;
          data[j].image=data[i].image;
            data[i].real=temp_r;
            data[i].image=temp_i;
        }
        m=n>>1;
        while(j>=m) { j-=m; m=(m+1)/2; }
        j+=m;
    }
        mmax=1;
        while(mmax<n)
        {
        istep=mmax<<1;
        r1=r/(float)mmax;
        for(m=0;m<mmax;m++)
            {
            theta=r1*m;
            w_r=(float)cos((double)theta);
            w_i=(float)sin((double)theta);
            for(i=m;i<n;i+=istep)
                {
                j=i+mmax;
                temp_r=w_r*data[j].real - w_i*data[j].image;
                temp_i=w_r*data[j].image + w_i*data[j].real;
                  data[j].real=data[i].real - temp_r;
                  data[j].image=data[i].image - temp_i;
                    data[i].real+=temp_r;
                    data[i].image+=temp_i;
                }
            }
        mmax=istep;
        }
        if(is>0)
             for(i=0;i<n;i++)
                 {
                 data[i].real/=(float)n;
                 data[i].image/=(float)n;
                 }


}


void MainWindow::FUR_FOR_WND(QVector<QVector<double>>okna, int N_INWND, int nmb_wnd)
{

    cmplx*data_in_wnd1=new cmplx[N_INWND];
    for(int i=0;i<N_INWND;i++)
    {
        data_in_wnd1[i].real=okna[nmb_wnd][i];
        data_in_wnd1[i].image=0;
    }
    FUR(data_in_wnd1,N_INWND,-1);
    for(int i=0;i<N_INWND;i++)
    {
    SpeCtr[i]=sqrt(data_in_wnd1[i].real*data_in_wnd1[i].real+data_in_wnd1[i].image*data_in_wnd1[i].image);
      t1[i]=t[i]/N_INWND;
    }

    int max = SpeCtr[0];
    for (int i = 0; i < SpeCtr.size(); ++i)
    {
        if (SpeCtr[i] > max)
        {
            max = SpeCtr[i];
        }
    }
    for (int i = 0; i < SpeCtr.size(); ++i)
    {
        SpeCtr[i]= SpeCtr[i]/max;
    }

    for (int i = 0; i < N_INWND*1; ++i)
    {
        okna_spectrov[nmb_wnd][i] = SpeCtr[i];
    }

}

vector<double> MainWindow::gen_armodel(QVector<QVector<double>> okna, int nmb_wnd, vector<double> koeff)
{

    vector<double> SIGN = okna[nmb_wnd].toStdVector();
    vector<double>Res;
    Res.resize(SIGN.size());
    for (int i = 0; i < Res.size(); i++)
    {
        Res[i] = 0;
        if (i < koeff.size())
        {
            Res[i] = SIGN[i];
        }
        else
        {
            for (int j = 1; j < koeff.size(); j++)
            {
                Res[i] -= koeff[j] * Res[i - j];
            }

        }
    }
    return Res;
}

std::vector<std::vector<double>> MainWindow::gen_rxx(QVector<QVector<double>> okna, int nmb_wnd, int rxx_type, bool full_size)
{

    std::vector<double> SIGN = okna[nmb_wnd].toStdVector();
    std::vector<std::vector<double>> RXX;
    //QVector<QVector<double>> RXX;
    if (full_size)
    {
        RXX.resize(M);
        for (int i = 0; i < RXX.size(); i++)
        {
            RXX[i].resize(M);
        }
    }
    else
    {
        RXX.resize(i_on_porog + 1);
                for (int i = 0; i<RXX.size(); i++)
                {
                    RXX[i].resize(i_on_porog + 1);
                }
    }


    switch (rxx_type)
    {
        case 0://Это по теории с косинусами
        {
            for (int i = 0; i < RXX.size(); i++)
            {
                for (int j = 0; j < RXX[i].size(); j++)
                {
                    RXX[i][j] = 0.;
                    {
                        RXX[i][j] += Amplituda1 * Amplituda1 * cos(2.0 * M_PI * Chastota1 * abs(i - j)) / 2;
                        RXX[i][j] += Amplituda2 * Amplituda2 * cos(2.0 * M_PI * Chastota2 * abs(i - j)) / 2;
                        RXX[i][j] += Amplituda3 * Amplituda3 * cos(2.0 * M_PI * Chastota3 * abs(i - j)) / 2;
                        RXX[i][j] += Amplituda4 * Amplituda4 * cos(2.0 * M_PI * Chastota4 * abs(i - j)) / 2;
                        RXX[i][j] += Amplituda5 * Amplituda5 * cos(2.0 * M_PI * Chastota5 * abs(i - j)) / 2;
                        RXX[i][j] += Amplituda6 * Amplituda6 * cos(2.0 * M_PI * Chastota6 * abs(i - j)) / 2;
                        RXX[i][j] += Amplituda7 * Amplituda7 * cos(2.0 * M_PI * Chastota7 * abs(i - j)) / 2;
                        RXX[i][j] += Amplituda8 * Amplituda8 * cos(2.0 * M_PI * Chastota8 * abs(i - j)) / 2;
                        RXX[i][j] += Amplituda9 * Amplituda9 * cos(2.0 * M_PI * Chastota9 * abs(i - j)) / 2;
                        RXX[i][j] += Amplituda10 * Amplituda10 * cos(2.0 * M_PI * Chastota10 * abs(i - j)) / 2;
                    }
                    if ((i - j) == 0)
                    {
                        //RXX[i][j] += noise_energy;
                    }
                }
            }
            break;
        }
    case 1:// Оценка типа устойчивая.
            {
                for (int i = 0; i < RXX.size(); i++)
                {
                    for (int j = 0; j < RXX[i].size(); j++)
                    {
                        int tau = j - i;
                        for (int k = 0; k < M; k++)
                        {

                            if ((k + abs(tau)) < M)
                            {
                                RXX[i][j] += SIGN[k] * SIGN[k + abs(tau)];
                            }
                        }
                        RXX[i][j] /= (M);
                    }
                }
                break;
             }



            case 2:
            {
        for (int i = 0; i < RXX.size(); i++)
        {
            double RR = 0;
            for (int j = 0; j < RXX[i].size() - i; j++)
            {
            RR += SIGN[j]*SIGN[j+i];
            }
            RXX[0][i] = RR;
        }

        for (int i = 0; i < RXX.size(); i++)
        {
            for (int j = 0; j < RXX.size(); j++)
            {
                RXX[i][j]= RXX[0][abs(i-j)];
            }
        }
        break;
    }




}
    qDebug()<<"RXX[0].size "<<RXX[0].size();//signal<<signal.size();
    return RXX;
}



QVector<double> MainWindow::rxxFunc(QVector<double>data_in_wnd, int N_INWND)
{
    qDebug()<<"start rxx for fnd";

    QVector<double>rxx;
    rxx.resize(N_INWND);
    double sum = 0;
    for (int i = 0; i < N_INWND; i++)
    {
        rxx[i]=0;
    }

    //double rxxsm = 0;
    for (int m = 0; m < 32; ++m)
    {
        sum = 0;
        for(int i=0;i<(N_INWND-m);i++)
        {

           //rxxsm=U[i]*U[i+m];
          // rxx[m]+=rxxsm;
            sum+=data_in_wnd[i]*data_in_wnd[i+m];
        }
        rxx[m]=sum;
   rxx[m]/=(N_INWND-m);
    }
    qDebug()<<"rxx ready"<<rxx;

    for (int i = 0; i < N_INWND; i++)
    {
        data_in_wnd[i] = rxx[i];
    }
qDebug()<<"data ready"<<data_in_wnd;
return data_in_wnd;
}

 void MainWindow::rxxFunc_FOR_WND(QVector<QVector<double>>okna,int N_INWND, int nmb_wnd)
 {


     QVector<double>data_in_wnd=QVector<double>(N_INWND);
     for(int i=0;i<N_INWND;i++)
     {
         data_in_wnd[i]=okna[nmb_wnd][i];
     }
     qDebug()<<"data in wnd do rxx"<<data_in_wnd;
     rxxFunc(data_in_wnd,N_INWND);
     //for (int i = 0; i < N_INWND*1; ++i)
     {
         okna_rxx[nmb_wnd] = rxxFunc(data_in_wnd,N_INWND);
         qDebug()<<"data in wnd posle rxx"<<okna_rxx[nmb_wnd];
     }
 }

void MainWindow::razb_na_okna()
{


    okna.resize(wnd_count);
    for(int j=0;j<wnd_count;j++)
    {
         okna[j].resize(N_INWND);
    }
    okna1.resize(wnd_count);
    for(int j=0;j<wnd_count;j++)
    {
         okna1[j].resize(N_INWND);
    }


    okna2.resize(wnd_count);
    for(int j=0;j<wnd_count;j++)
    {
         okna2[j].resize(N_INWND);
    }
    okna3.resize(wnd_count);
    for(int j=0;j<wnd_count;j++)
    {
         okna3[j].resize(N_INWND);
    }

    okna4.resize(wnd_count);
    for(int j=0;j<wnd_count;j++)
    {
         okna4[j].resize(N_INWND);
    }

    okna5.resize(wnd_count);
    for(int j=0;j<wnd_count;j++)
    {
         okna5[j].resize(N_INWND);
    }



    okna_spectrov.resize(wnd_count);
    for(int j=0;j<wnd_count;j++)
    {
         okna_spectrov[j].resize(N_INWND);
    }
    okna_rxx.resize(wnd_count);
    for(int j=0;j<wnd_count;j++)
    {
         okna_rxx[j].resize(N_INWND);
    }

    //разбиение на окна
    int temp_i=0;
    int temp_j=0;
    for (int i=0; i<N; i++) {
        if (i%N_INWND==0 && i)
        {
            temp_i++;
            temp_j=0;
        }
        okna[temp_i][temp_j++]=U[i];
    }

    qDebug()<<"N_INWND"<<N_INWND;
    qDebug()<<"wnd_count"<<wnd_count;
    qDebug()<<"okna_spectrov.size"<<okna_spectrov.size();
    //qDebug()<<"okna0 do fur"<<okna[0];



//    for (int i = 0; i < wnd_count; ++i)
//    {
//        FUR_FOR_WND(okna, N_INWND, i);
//        rxxFunc_FOR_WND(okna, N_INWND, i);
//    }

}

void MainWindow::method_select()
{
    if (ui->radioButton->isChecked())
    {
        for (int i = 0; i < wnd_count; ++i)
        {
            FUR_FOR_WND(okna, N_INWND, i);
            //rxxFunc_FOR_WND(okna, N_INWND, i);
        }
    }    
    if(ui->radioButton_2->isChecked())
    {
        for (int i = 0; i < wnd_count; ++i)
        {
            rxxFunc_FOR_WND(okna, N_INWND, i);
        }
        for (int i = 0; i < wnd_count; ++i)
        {
            FUR_FOR_WND(okna_rxx, N_INWND, i);
        }
    }

    if (ui->radioButton_3->isChecked())
    {
        ReadMtpWnds();
        CreateMtpWnds();
        for (int i = 0; i < wnd_count; ++i)
        {
            FUR_FOR_MtpWND(N_INWND, i);
        }
    }
    if (ui->radioButton_4->isChecked())
    {

    }
}

void MainWindow::on_pushButton_clicked()
{

    Amplituda1 = ui->doubleSpinBox->value();
    Amplituda2 = ui->doubleSpinBox_2->value();
    Amplituda3 = ui->doubleSpinBox_3->value();
    Amplituda4 = ui->doubleSpinBox_4->value();
    Amplituda5 = ui->doubleSpinBox_5->value();
    Amplituda6 = ui->doubleSpinBox_6->value();
    Amplituda7 = ui->doubleSpinBox_7->value();
    Amplituda8 = ui->doubleSpinBox_8->value();
    Amplituda9 = ui->doubleSpinBox_9->value();
    Amplituda10 = ui->doubleSpinBox_10->value();
    Chastota1 = ui->doubleSpinBox_11->value();
    Chastota2 = ui->doubleSpinBox_12->value();
    Chastota3 = ui->doubleSpinBox_13->value();
    Chastota4 = ui->doubleSpinBox_14->value();
    Chastota5 = ui->doubleSpinBox_15->value();
    Chastota6 = ui->doubleSpinBox_16->value();
    Chastota7 = ui->doubleSpinBox_17->value();
    Chastota8 = ui->doubleSpinBox_18->value();
    Chastota9 = ui->doubleSpinBox_19->value();
    Chastota10 = ui->doubleSpinBox_20->value();
    noise_procent = ui->doubleSpinBox_N1->value();
    //int notch = ui->otschety->value();
    //set_N(notch);
    N = ui->N_otsch->value();
    N_INWND = ui->N_WND_->value();
    wnd_count = N/N_INWND;
    w_t.resize(N);
    lfm.resize(N);
    t.resize(N);
    U.resize(N);
    sig.resize(N);
    SpeCtr.resize(N);
    t1.resize(N);
    Line.resize(N);
    alpha = ui->alpha1->value();
    //w0 = ui->W0->value();
    w1= ui->W1->value();
    b = ui->B->value();
    A = ui->Ampl->value();
    nomer_1();


    razb_na_okna();
    method_select();

    // Init vertical Line
    verticalLine1 = new QCPCurve (ui->widget->xAxis, ui->widget->yAxis);
    verticalLine2 = new QCPCurve (ui->widget->xAxis, ui->widget->yAxis);
    ui->widget->addPlottable(verticalLine1);// Adding a line on the canvas
    ui->widget->addPlottable(verticalLine2);// Adding a line on the canvas
+
    ui->widget->clearGraphs();//Если нужно, то очищаем все графики
    ui->widget->addGraph();//Создаем   график
    ui->widget->graph(0)->setPen(QColor(0, 0, 255));//задаем цвет точки
    ui->widget->xAxis->setLabel("t");//Задаем название осей грфику
    ui->widget->yAxis->setLabel("x");//Задаем название осей грфику
    ui->widget->graph(0)->setData(t, U);//Что и от чего стрить для x(t)    /// U[i] массив отсчетов сигнала
    double minY = U[0], maxY = U[0];
    double minX=-1,maxX=256;
    for (int i=1; i<N; i++)
     {
           if (U[i]<minY) minY = U[i]-0.5;
           if (U[i]>maxY) maxY = U[i]+0.5;
     }
    ui->widget->xAxis->setRange(minX, maxX);//Задаем начальное и конечное положения графику
    ui->widget->yAxis->setRange(minY, maxY );//Задаем начальное и конечное положения
    y[0] = minY-1;
    y[1] = maxY+1;
    x[0] = 0;
    x[1] = 0;
    x2[0] = 0;
    x2[1] = 0;
    y2[0] = minY-1;
    y2[1] = maxY+1;

//    verticalLine1->setData(x,y);
//    verticalLine1->setPen(QColor(1,1,1));

    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);//Для изменения Zoom графика
    ui->widget->replot();


    ui->widget_2->clearGraphs();//Если нужно, то очищаем все графики
    ui->widget_2->addGraph();//Создаем   график
    ui->widget_2->addGraph();//Создаем   график
    ui->widget_2->graph(0)->setPen(QColor(0, 0, 255));//задаем цвет точки
    ui->widget_2->graph(1)->setPen(QColor(255, 0, 0));//задаем цвет точки
    ui->widget_2->xAxis->setLabel("f");//Задаем название осей грфику
    ui->widget_2->yAxis->setLabel("A");//Задаем название осей грфику
//    if (ui->radioButton->isChecked())
//    {
//         ui->widget_2->graph(0)->setData(t1, okna_spectrov[0]);//Что и от чего стрить для x(t)
//    }
//    if(ui->radioButton_2->isChecked())
//    {
//        ui->widget_2->graph(0)->setData(t1, okna_rxx[0]);//Что и от чего стрить для x(t)
//    }
    ui->widget_2->graph(0)->setData(t1, okna_spectrov[0]);//Что и от чего стрить для x(t)

    //ui->widget_2->graph(1)->setData(t1, Line);//Что и от чего стрить для x(t)
//    double minYSpeCtr = SpeCtr[0], maxYSpeCtr = SpeCtr[0];
//    double minXSpeCtr=-0.1,maxXSpeCtr=1.1;
//    for (int i=1; i<N; i++)
//     {
//           if (SpeCtr[i]<minYSpeCtr) minYSpeCtr = SpeCtr[i]-0.5;
//           if (SpeCtr[i]>maxYSpeCtr) maxYSpeCtr = SpeCtr[i]+0.5;
//     }
//     //ui->widget_2->rescaleAxes();
//    ui->widget_2->xAxis->setRange(minXSpeCtr, maxXSpeCtr);//Задаем начальное и конечное положения графику
//    ui->widget_2->yAxis->setRange(minYSpeCtr, maxYSpeCtr );//Задаем начальное и конечное положения
    ui->widget_2->rescaleAxes();
    ui->widget_2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);//Для изменения Zoom графика
    ui->widget_2->replot();
    ui->horizontalSlider->setRange(0,wnd_count-1);
    ui->horizontalSlider->setValue(0);
}







void MainWindow::on_pushButton_2_clicked()
{


    ui->customPlot->replot();
    // configure axis rect:
    ui->customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
    ui->customPlot->axisRect()->setupFullAxesBox(true);
    ui->customPlot->xAxis->setLabel("Time (s)");
    ui->customPlot->yAxis->setLabel("Frequency (Hz)");



    // set up the QCPColorMap:
    QCPColorMap *colorMap = new QCPColorMap(ui->customPlot->xAxis, ui->customPlot->yAxis);
    colorMap->setInterpolate(1);
    colorMap->data()->setSize(wnd_count,N_INWND); // we want the color map to have nx * ny data points
    colorMap->data()->setRange(QCPRange(0, wnd_count), QCPRange(0, N_INWND)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
    // now we assign some data, by accessing the QCPColorMapData instance of the color map:
    for (int x=0; x<wnd_count; ++x)
    {
       // qDebug()<<"okna_spectov[wnd_count][0]"<<okna_spectrov[x][0];
        for (int y=0; y<N_INWND; ++y)
        {
            double r = okna_spectrov[x][y];
            colorMap->data()->setCell(x, y, r);

        }
    }
   // qDebug()<<"okna_spectov[1][0]"<<okna_spectrov[1][0];




    // add a color scale:
    QCPColorScale *colorScale = new QCPColorScale(ui->customPlot);
    ui->customPlot->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect
    colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
    colorMap->setColorScale(colorScale); // associate the color map with the color scale
    //colorScale->axis()->setLabel("Magnetic Field Strength");

    // set the color gradient of the color map to one of the presets:
    colorMap->setGradient(QCPColorGradient::gpJet);
    // we could have also created a QCPColorGradient instance and added own colors to
    // the gradient, see the documentation of QCPColorGradient for what's possible.

    // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:
    colorMap->rescaleDataRange();

    // make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->customPlot);
    ui->customPlot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

    // rescale the key (x) and value (y) axes so the whole color map is visible:
    ui->customPlot->xAxis->setRange(0, wnd_count);//Задаем начальное и конечное положения графику

   ui->customPlot->yAxis->setRange(0, N_INWND*0.5 );//Задаем начальное и конечное положения
    ui->customPlot->rescaleAxes();
    ui->customPlot->replot();



    for (int x=0; x<TickValues.size(); ++x)
    {
        TickLabels[x] = QString::number(TickValues[x]*double(N_INWND));
    }


    QVector<double> Ticks;
    int i = 0;
    while(i<=N_INWND) {
        Ticks << i;
        i+=13;
    }

    QVector<QString> Labels;
    Labels << "0" << QString::fromUtf8("0.05") << QString::fromUtf8("0.1")
           << QString::fromUtf8("0.15") << QString::fromUtf8("0.2")
           << QString::fromUtf8("0.25") << QString::fromUtf8("0.3")
           << QString::fromUtf8("0.35") << QString::fromUtf8("0.4")
           << QString::fromUtf8("0.45") << QString::fromUtf8("0.5")
           << QString::fromUtf8("0.55") << QString::fromUtf8("0.6")
           << QString::fromUtf8("0.65") << QString::fromUtf8("0.7")
           << QString::fromUtf8("0.75") << QString::fromUtf8("0.8")
           << QString::fromUtf8("0.85") << QString::fromUtf8("0.9")
           << QString::fromUtf8("0.95") << QString::fromUtf8("1");

    ui->customPlot->yAxis->setAutoTicks(false); // выключаем автоматические отсчеты
    ui->customPlot->yAxis->setAutoTickLabels(false);
    ui->customPlot->yAxis->setTickVector(Ticks);  // задаем созданный нами вектор
    ui->customPlot->yAxis->setTickVectorLabels(Labels);



    ui->customPlot->xAxis->setAutoTicks(0);
    ui->customPlot->xAxis->setAutoTickLabels(false);
    // add your custom values and labels
    ui->customPlot->xAxis->setTickVector({0, 20, 40, 60, 80,100,120});
    ui->customPlot->xAxis->setTickVectorLabels(TickLabels);



    ui->customPlot->rescaleAxes();
    ui->customPlot->replot();
}



void MainWindow::on_horizontalSlider_valueChanged(int value)
{
//    if (ui->radioButton->isChecked())
//    {
//         ui->widget_2->graph(0)->setData(t1, okna_spectrov[value]);//Что и от чего стрить для x(t)
//    }
//    if(ui->radioButton_2->isChecked())
//    {
//        ui->widget_2->graph(0)->setData(t1, okna_rxx[value]);//Что и от чего стрить для x(t)
//    }
ui->widget_2->graph(0)->setData(t1, okna_spectrov[value]);//Что и от чего стрить для x(t)

    // Init vertical Line

    //verticalLine1->deleteLater();
    //verticalLine2->deleteLater();
    // creating a vector for the vertical line

    x[0] = value*N_INWND;
    x[1] = value*N_INWND;
    x2[0] = (value+1)*N_INWND;
    x2[1] = (value+1)*N_INWND;

    verticalLine1->setData(x,y);
    //verticalLine1->setBrush();
    QPen pen(Qt::black, 2, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);
    verticalLine1->setPen(pen);
    verticalLine2->setData(x2,y2);
    verticalLine2->setPen(pen);
    ui->widget->replot();
    ui->widget->repaint();
    ui->widget_2->replot();
    ui->widget_2->rescaleAxes();
}


void MainWindow::ReadMtpWnds()
{



    QFile file1("2561.txt");
    if (file1.open(QIODevice::ReadOnly))
    {
        QString a;
        QVector<QString> list;

        QStringList myList;
        QByteArray data;
        while(!file1.atEnd())
            {
            a = file1.readLine();
            mass1.push_back(a.trimmed().toDouble());
            }
            file1.close();
    }

    QFile file2("2562.txt");
    if (file2.open(QIODevice::ReadOnly))
    {
        QString a;
        QVector<QString> list;

        QStringList myList;
        QByteArray data;
        while(!file2.atEnd())
            {
            a = file2.readLine();
            mass2.push_back(a.trimmed().toDouble());
            }
            file2.close();
    }

    QFile file3("2563.txt");
    if (file3.open(QIODevice::ReadOnly))
    {
        QString a;
        QVector<QString> list;

        QStringList myList;
        QByteArray data;
        while(!file3.atEnd())
            {
            a = file3.readLine();
            mass3.push_back(a.trimmed().toDouble());
            }
            file3.close();
    }

    QFile file4("2564.txt");
    if (file4.open(QIODevice::ReadOnly))
    {
        QString a;
        QVector<QString> list;

        QStringList myList;
        QByteArray data;
        while(!file4.atEnd())
            {
            a = file4.readLine();
            mass4.push_back(a.trimmed().toDouble());
            }
            file4.close();
    }

    QFile file5("2565.txt");
    if (file5.open(QIODevice::ReadOnly))
    {
        QString a;
        QVector<QString> list;

        QStringList myList;
        QByteArray data;
        while(!file5.atEnd())
            {
            a = file5.readLine();
            mass5.push_back(a.trimmed().toDouble());
            }
            file5.close();
    }
}

void MainWindow::CreateMtpWnds()
{
    for (int j = 0; j<wnd_count; j++)
    {
        for (int i = 0; i<N_INWND; i++)
        {
            okna1[j][i] = okna[j][i]*mass1[i];
            okna2[j][i] = okna[j][i]*mass2[i];
            okna3[j][i] = okna[j][i]*mass3[i];
            okna4[j][i] = okna[j][i]*mass4[i];
            okna5[j][i] = okna[j][i]*mass5[i];
        }
    }
}


void MainWindow::FUR_FOR_MtpWND(/*QVector<QVector<double>>okna,*/int N_INWND, int nmb_wnd)
{

    QVector<double> SpeCtr1;
    QVector<double> SpeCtr2;
    QVector<double> SpeCtr3;
    QVector<double> SpeCtr4;
    QVector<double> SpeCtr5;
    QVector<double> SpeCtrSum;
    //QVector<double> SpeCtrSumOtd;
    SpeCtr1.resize(N_INWND);
    SpeCtr2.resize(N_INWND);
    SpeCtr3.resize(N_INWND);
    SpeCtr4.resize(N_INWND);
    SpeCtr5.resize(N_INWND);
    SpeCtrSum.resize(N_INWND);
    //SpeCtrSumOtd.resize(N_INWND);



    cmplx*data_in_mwnd1=new cmplx[N_INWND];
    for(int i=0;i<N_INWND;i++)
    {
        data_in_mwnd1[i].real=okna1[nmb_wnd][i];
        data_in_mwnd1[i].image=0;
    }
    FUR(data_in_mwnd1,N_INWND,-1);
    for(int i=0;i<N_INWND;i++)
    {
    SpeCtr1[i]=sqrt(data_in_mwnd1[i].real*data_in_mwnd1[i].real+data_in_mwnd1[i].image*data_in_mwnd1[i].image);
      t1[i]=t[i]/N_INWND;
    }


    cmplx*data_in_mwnd2=new cmplx[N_INWND];
    for(int i=0;i<N_INWND;i++)
    {
        data_in_mwnd2[i].real=okna2[nmb_wnd][i];
        data_in_mwnd2[i].image=0;
    }
    FUR(data_in_mwnd2,N_INWND,-1);
    for(int i=0;i<N_INWND;i++)
    {
    SpeCtr2[i]=sqrt(data_in_mwnd2[i].real*data_in_mwnd2[i].real+data_in_mwnd2[i].image*data_in_mwnd2[i].image);
      t1[i]=t[i]/N_INWND;
    }


    cmplx*data_in_mwnd3=new cmplx[N_INWND];
    for(int i=0;i<N_INWND;i++)
    {
        data_in_mwnd3[i].real=okna3[nmb_wnd][i];
        data_in_mwnd3[i].image=0;
    }
    FUR(data_in_mwnd3,N_INWND,-1);
    for(int i=0;i<N_INWND;i++)
    {
    SpeCtr3[i]=sqrt(data_in_mwnd3[i].real*data_in_mwnd3[i].real+data_in_mwnd3[i].image*data_in_mwnd3[i].image);
      t1[i]=t[i]/N_INWND;
    }


    cmplx*data_in_mwnd4=new cmplx[N_INWND];
    for(int i=0;i<N_INWND;i++)
    {
        data_in_mwnd4[i].real=okna4[nmb_wnd][i];
        data_in_mwnd4[i].image=0;
    }
    FUR(data_in_mwnd4,N_INWND,-1);
    for(int i=0;i<N_INWND;i++)
    {
    SpeCtr4[i]=sqrt(data_in_mwnd4[i].real*data_in_mwnd4[i].real+data_in_mwnd4[i].image*data_in_mwnd4[i].image);
      t1[i]=t[i]/N_INWND;
    }



    cmplx*data_in_mwnd5=new cmplx[N_INWND];
    for(int i=0;i<N_INWND;i++)
    {
        data_in_mwnd5[i].real=okna5[nmb_wnd][i];
        data_in_mwnd5[i].image=0;
    }
    FUR(data_in_mwnd5,N_INWND,-1);
    for(int i=0;i<N_INWND;i++)
    {
    SpeCtr5[i]=sqrt(data_in_mwnd5[i].real*data_in_mwnd5[i].real+data_in_mwnd5[i].image*data_in_mwnd5[i].image);
      t1[i]=t[i]/N_INWND;
    }


    for(int i=0;i<N_INWND;i++)
    {
        SpeCtrSum[i] = (SpeCtr1[i] + SpeCtr2[i] + SpeCtr3[i] + SpeCtr4[i] + SpeCtr5[i])/5;
    }


    cmplx*data_in_mwndSum=new cmplx[N_INWND];
    for(int i=0;i<N_INWND;i++)
    {
        data_in_mwndSum[i].real = (data_in_mwnd1[i].real + data_in_mwnd2[i].real + data_in_mwnd3[i].real + data_in_mwnd4[i].real + data_in_mwnd5[i].real)/5;
        data_in_mwndSum[i].image = (data_in_mwnd1[i].image + data_in_mwnd2[i].image + data_in_mwnd3[i].image + data_in_mwnd4[i].image + data_in_mwnd5[i].image)/5;;
    }
    for(int i=0;i<N_INWND;i++)
    {
    //SpeCtrSum[i]=sqrt(data_in_mwndSum[i].real*data_in_mwndSum[i].real+data_in_mwndSum[i].image*data_in_mwndSum[i].image);
        t1[i]=t[i]/N_INWND;
    }



    int max = SpeCtrSum[0];
    for (int i = 0; i < SpeCtrSum.size(); ++i)
    {
        if (SpeCtrSum[i] > max)
        {
            max = SpeCtrSum[i];
        }
    }
    for (int i = 0; i < SpeCtrSum.size(); ++i)
    {
        SpeCtrSum[i]= SpeCtrSum[i]/max;
    }


    for (int i = 0; i < N_INWND*1; ++i)
    {
        okna_spectrov[nmb_wnd][i] = SpeCtrSum[i];
    }


}

void MainWindow::BurgAlgorithm(vector<double> &coeffs, const vector<double> &x)
{
    // GET SIZE FROM INPUT VECTORS
    size_t N = x.size() - 1;
    size_t m = coeffs.size();

    // INITIALIZE Ak
    vector<double> Ak(m+1, 0.0);
    Ak[0] = 1.0;

    // INITIALIZE f and b
    vector<double> f(x);
    vector<double> b(x);

    // INITIALIZE Dk
    double Dk = 0.0;
    for (size_t j = 0; j<=N; j++)
    {
        Dk += 2.0 * f[j] * f[j];
    }
    Dk -= f[0] * f[0] + b[N] * b[N];

    // BURG RECURSION
    for (size_t k = 0; k<m; k++)
    {
        // COMPUTE MU
        double mu = 0.0;
        for (size_t n = 0; n<=N-k-1; n++)
        {
            mu += f[n+k+1] * b[n];
        }
        mu *= -2.0 / Dk;

        // UPDATE Ak
        for (size_t n = 0; n<=(k+1)/2; n++)
        {
            double t1 = Ak[n] + mu*Ak[k+1-n];
            double t2 = Ak[k+1-n] + mu*Ak[n];
            Ak[n] = t1;
            Ak[k+1-n] = t2;
        }

        // UPDATE f and b
        for (size_t n = 0; n<=N-k-1; n++)
        {
            double t1 = f[n+k+1] + mu*b[n];
            double t2 = b[n] + mu*f[n+k+1];
            f[n+k+1] = t1;
            b[n] = t2;
        }
        // UPDATE Dk
        Dk = (1.0-mu*mu)*Dk-f[k+1]*f[k+1]-b[N-k-1]*b[N-k-1];
    }
    // ASSIGN COEFFICIENTS
    coeffs.assign(++Ak.begin(), Ak.end());

}



void MainWindow::on_pushButton_3_clicked()
{

    ReadMtpWnds();

    qDebug()<<"Button down" << QCoreApplication:: applicationDirPath();




  //  qDebug()<<mass.size()<<mass;
    QVector<double> time;
    time.resize(N_INWND);
    for (int i = 0; i<time.size(); i++)
    {
        time[i]=i;
    }
    //qDebug()<<time.size()<<time;

    QVector<double> MtpWndSign;
    MtpWndSign.resize(N_INWND);

    qDebug()<< "okna[o]: " << okna[0];


        for (int i = 0; i<time.size(); i++)
        {
            MtpWndSign[i] = okna[0][i]*mass1[i];
        }


    qDebug()<< "MtpWndSign: "<< MtpWndSign.size() << MtpWndSign;
    QVector<double> SpeCtr1;
    SpeCtr1.resize(MtpWndSign.size());
    cmplx*data_in_mwnd1=new cmplx[MtpWndSign.size()];
    for(int i=0;i<MtpWndSign.size();i++)
    {
        data_in_mwnd1[i].real=MtpWndSign[i];
        data_in_mwnd1[i].image=0;
    }
    qDebug()<< "data in wnd: " << data_in_mwnd1[2].real << data_in_mwnd1[2].image;

    FUR(data_in_mwnd1,MtpWndSign.size(),-1);
    qDebug()<< "data in wnd: " << data_in_mwnd1[2].real << data_in_mwnd1[2].image;

    for(int i=0;i<MtpWndSign.size();i++)
    {
        SpeCtr1[i]=sqrt(data_in_mwnd1[i].real*data_in_mwnd1[i].real+data_in_mwnd1[i].image*data_in_mwnd1[i].image);
        time[i]=time[i]/time.size();
    }



    QVector<double> MtpWndSign2;
    MtpWndSign2.resize(N_INWND);

    qDebug()<< "okna[o]: " << okna[0];
    for (int i = 0; i<time.size(); i++)
    {
        MtpWndSign2[i] = okna[0][i]*mass2[i];
    }
    //FUR_FOR_WND(okna, N_INWND, 0);

    qDebug()<< "MtpWndSign: "<< MtpWndSign2.size() << MtpWndSign2;
    QVector<double> SpeCtr2;
    SpeCtr2.resize(MtpWndSign2.size());
    cmplx*data_in_mwnd2=new cmplx[MtpWndSign2.size()];
    for(int i=0;i<MtpWndSign2.size();i++)
    {
        data_in_mwnd2[i].real=MtpWndSign2[i];
        data_in_mwnd2[i].image=0;
    }
    qDebug()<< "data in wnd: " << data_in_mwnd2[2].real << data_in_mwnd2[2].image;

    FUR(data_in_mwnd2,MtpWndSign2.size(),-1);
    qDebug()<< "data in wnd: " << data_in_mwnd2[2].real << data_in_mwnd2[2].image;

    for(int i=0;i<MtpWndSign2.size();i++)
    {
        SpeCtr2[i]=sqrt(data_in_mwnd2[i].real*data_in_mwnd2[i].real+data_in_mwnd2[i].image*data_in_mwnd2[i].image);
        time[i]=time[i]/time.size();
    }





    QVector<double> MtpWndSign3;
    MtpWndSign3.resize(N_INWND);

    qDebug()<< "okna[o]: " << okna[0];
    for (int i = 0; i<time.size(); i++)
    {
        MtpWndSign3[i] = okna[0][i]*mass3[i];
    }
    //FUR_FOR_WND(okna, N_INWND, 0);

    qDebug()<< "MtpWndSign: "<< MtpWndSign3.size() << MtpWndSign3;
    QVector<double> SpeCtr3;
    SpeCtr3.resize(MtpWndSign3.size());
    cmplx*data_in_mwnd3=new cmplx[MtpWndSign3.size()];
    for(int i=0;i<MtpWndSign3.size();i++)
    {
        data_in_mwnd3[i].real=MtpWndSign3[i];
        data_in_mwnd3[i].image=0;
    }
    qDebug()<< "data in wnd: " << data_in_mwnd3[2].real << data_in_mwnd3[2].image;

    FUR(data_in_mwnd3,MtpWndSign3.size(),-1);
    qDebug()<< "data in wnd: " << data_in_mwnd3[2].real << data_in_mwnd3[2].image;

    for(int i=0;i<MtpWndSign3.size();i++)
    {
        SpeCtr3[i]=sqrt(data_in_mwnd3[i].real*data_in_mwnd3[i].real+data_in_mwnd3[i].image*data_in_mwnd3[i].image);
        time[i]=time[i]/time.size();
    }

    QVector<double> SpeCtrSum;
    SpeCtrSum.resize(SpeCtr1.size());
    for(int i=0;i<SpeCtrSum.size();i++)
    {
        SpeCtrSum[i]= (SpeCtr1[i] + SpeCtr2[i] + SpeCtr3[i])/3;
    }

    ui->widget_2->clearGraphs();//Если нужно, то очищаем все графики
    ui->widget_2->addGraph();//Создаем   график
    ui->widget_2->addGraph();//Создаем   график
    ui->widget_2->addGraph();//Создаем   график
    ui->widget_2->addGraph();//Создаем   график
    ui->widget_2->graph(0)->setPen(QColor(100, 0, 100));//задаем цвет точки
    ui->widget_2->graph(1)->setPen(QColor(100, 100, 0));//задаем цвет точки
    ui->widget_2->graph(2)->setPen(QColor(0, 100, 0));//задаем цвет точки
    ui->widget_2->graph(3)->setPen(QColor(255, 0, 0));//задаем цвет точки
    ui->widget_2->xAxis->setLabel("t");//Задаем название осей грфику
    ui->widget_2->yAxis->setLabel("U");//Задаем название осей грфику
    ui->widget_2->graph(0)->setData(t1, SpeCtr1);//Что и от чего стрить для x(t)
    ui->widget_2->graph(1)->setData(t1, SpeCtr2);//Что и от чего стрить для x(t)
    ui->widget_2->graph(2)->setData(t1, SpeCtr3);//Что и от чего стрить для x(t)
    ui->widget_2->graph(3)->setData(t1, SpeCtrSum);//Что и от чего стрить для x(t)
    ui->widget_2->rescaleAxes();
    ui->widget_2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);//Для изменения Zoom графика
    ui->widget_2->replot();


}

double MainWindow::X(double A, double f, double t)
{
    return A * sin(2 * M_PI *f*t);
}


int MainWindow::svd_hestenes(int m_m, int n_n, vector<vector<double>> &WNDM, vector<vector<double>> &U, vector<vector<double>> &V, vector<vector<double>> &SIGMA)
{
    U.resize(m_m);
    V.resize(m_m);
    SIGMA.resize(m_m);
    for (int i = 0; i<m_m; i++)
    {
        U[i].resize(m_m);
        V[i].resize(m_m);
        SIGMA[i].resize(m_m);
    }
    V.resize(m_m);

    double thr = 1.E-12f, nul = 1.E-16f;
    int n, m, i, j, l, k, lort, iter, in, ll, kk;
    double alfa, betta, hamma, eta, t, cos0, sin0, buf, s;
    n = n_n;
    m = m_m;
    for (i = 0; i<n; i++)
    {
        for (j = 0; j<n; j++)
        {
            if (i == j)
            {
                V[i][j] = 1.;
            }
            else
            {
                V[i][j] = 0.;
            }
        }
    }
    for (i = 0; i<m; i++)
    {
        for (j = 0; j<n; j++)
        {
            U[i][j] = WNDM[i][j];
        }
    }
    iter = 0;
    while (1)
    {
        lort = 0;
        iter++;
        for (l = 0; l<n - 1; l++)
        {
            for (k = l + 1; k<n; k++)
            {
                alfa = 0.; betta = 0.; hamma = 0.;
                for (i = 0; i<m; i++)
                {
                    alfa += U[i][l] * U[i][l];
                    betta += U[i][k] * U[i][k];
                    hamma += U[i][l] * U[i][k];
                }
                if (sqrt(alfa*betta) < nul)
                {
                    continue;
                }
                if (fabs(hamma) / sqrt(alfa*betta)<thr)
                {
                    continue;
                }
                lort = 1;
                eta = (betta - alfa) / (2.f*hamma);
                t = (double)((eta / fabs(eta)) / (fabs(eta) + sqrt(1. + eta*eta)));
                cos0 = (double)(1. / sqrt(1. + t*t));
                sin0 = t*cos0;
                for (i = 0; i<m; i++)
                {
                    buf = U[i][l] * cos0 - U[i][k] * sin0;
                    U[i][k] = U[i][l] * sin0 + U[i][k] * cos0;
                    U[i][l] = buf;
                    if (i >= n)
                    {
                        continue;
                    }
                    buf = V[i][l] * cos0 - V[i][k] * sin0;
                    V[i][k] = V[i][l] * sin0 + V[i][k] * cos0;
                    V[i][l] = buf;
                }
            }
        }
        if (!lort)
        {
            break;
        }
    }
    for (i = 0; i<n; i++)
    {
        s = 0.;
        for (j = 0; j<m; j++)
        {
            s += U[j][i] * U[j][i];
        }
        s = (double)sqrt(s);
        SIGMA[i][i] = s;
        if (s < nul)
        {
            continue;
        }
        for (j = 0; j<m; j++)
        {
            U[j][i] /= s;
        }
    }
    //======= Sortirovka ==============
    for (i = 0; i<n - 1; i++)
    {
        for (j = i; j<n; j++)
        {
            if (SIGMA[i][i]<SIGMA[j][j])
            {
                s = SIGMA[i][i];
                SIGMA[i][i] = SIGMA[j][j];
                SIGMA[j][j] = s;
                for (k = 0; k<m; k++)
                {
                    s = U[k][i];
                    U[k][i] = U[k][j];
                    U[k][j] = s;
                }
                for (k = 0; k<n; k++)
                {
                    s = V[k][i];
                    V[k][i] = V[k][j];
                    V[k][j] = s;
                }
            }
        }
    }
    return iter;
}
void MainWindow::kazf(vector<vector<double>> &a, vector<double> &b, vector<double> &x)
{
    int nn = b.size();
    int ny = a.size();

    // nn - количество неизвестных;  ny - количество уравнений
    float eps = 1.e-6f;
    //float s;
    int i, j, k;
    float s1, s2, fa1, t;
    vector<double> x1;
    x1.resize(x.size());

    x[0] = 0.5f;
    for (i = 1; i<nn; i++)  x[i] = 0.f;

    s1 = s2 = 1.f;
    do
    {
        for (i = 0; i < nn; i++) x1[i] = x[i];

        for (i = 0; i<ny; i++)
        {
            s1 = 0.0;
            s2 = 0.0;
            for (j = 0; j<nn; j++)
            {
                fa1 = a[i][j];
                s1 += fa1 * x[j];
                s2 += fa1 * fa1;
            }
            t = (b[i] - s1) / s2;
            for (k = 0; k<nn; k++)    x[k] += a[i][k] * t;
        }

        s1 = 0.0;
        s2 = 0.0;
        x[0] = 1.;
        for (i = 0; i<nn; i++)
        {
            s1 += (x[i] - x1[i]) * (x[i] - x1[i]);
            s2 += x[i] * x[i];
        }
        s1 = (float)sqrt(s1);
        s2 = (float)sqrt(s2);
    } while (s1 > eps*s2);
}


double MainWindow::On_porog(vector<double>&S,double porog)
{

    int iter = 0;
    for (int i = 0; i < S.size(); i++)
    {
        if (S[i]>porog)
        {
            iter++;
        }
    }
    return iter;
}
vector<double> MainWindow::svobodn(vector<vector<double>>&S, int porog)
{
    vector<double>Res;
    Res.push_back(0.01*(S[0][0]));
    for (int i = 1; i < porog + 1; i++)
    {
        Res.push_back(0);
    }

    return Res;
}


void MainWindow::on_pushButton_4_clicked()
{

    vector<vector<double>> autocorrelation_matrix = gen_rxx(okna,0,2,true);
    vector<vector<double>> U, V, SIGMA;
    int iter = svd_hestenes(M, M, autocorrelation_matrix, U, V, SIGMA);
    eigen_values.clear();
        for (int i = 0; i < SIGMA.size(); i++)
        {
            eigen_values.push_back(SIGMA[i][i]);
        }
    QVector<double> Qeigen_values = QVector<double>::fromStdVector(eigen_values);
        qDebug()<<eigen_values<<eigen_values.size();
        qDebug()<<Qeigen_values<<Qeigen_values.size();

        ui->widget_3->clearGraphs();//Если нужно, то очищаем все графики
        ui->widget_3->addGraph();//Создаем   график
        ui->widget_3->graph(0)->setPen(QColor(0, 0, 255));//задаем цвет точки
        ui->widget_3->xAxis->setLabel("Singular counts");//Задаем название осей грфику
        ui->widget_3->yAxis->setLabel("Singular values");//Задаем название осей грфику
        ui->widget_3->graph(0)->setData(t, Qeigen_values);//Что и от чего стрить для x(t)
        ui->widget_3->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
        ui->widget_3->legend->setVisible(false);
        ui->widget_3->rescaleAxes();
        ui->widget_3->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);//Для изменения Zoom графика
        ui->widget_3->replot();
        porog = int(eigen_values[0]*0.029);
        qDebug()<<"porog"<<eigen_values[0]<<porog;
}


void MainWindow::on_pushButton_5_clicked()
{
    //porog = ui->doubleSpinBox_porog->value();
    i_on_porog = On_porog(eigen_values, porog);
    ui->textEdit->setText(QString::number(i_on_porog));
}

void MainWindow::on_pushButton_6_clicked()
{
    vector<vector<double>> autocorrelation_matrix = gen_rxx(okna,0,2, false);
    vector<double> free_part = svobodn(autocorrelation_matrix, i_on_porog);
    vector<double> koeffs;
    koeffs.resize(free_part.size());
    kazf(autocorrelation_matrix, free_part, koeffs);
    prediction = gen_armodel(okna, 0, koeffs);
    //qDebug()<<prediction;
    qDebug()<<"AR1: "<<koeffs;
    QVector<double> Qprediction = QVector<double>::fromStdVector(prediction);

    for (int i = 0; i<koeffs.size(); i++)
    {
        koeffs[i] = 0;
    }

    qDebug()<<"AR2: "<<koeffs;

    vector<double> data = U.toStdVector();
    BurgAlgorithm(koeffs,data);
    double a =1;
    auto iter = koeffs.cbegin();
    koeffs.emplace(iter, a);
    qDebug()<<"AR3: "<<koeffs;

    QVector<double> Par;
    QVector<double> f;
    f.resize(N_INWND);
    Par.resize(N_INWND);
    for (int i = 0; i < f.size(); i++)
    {
        f[i]= i/(double)N_INWND;
    }
    qDebug()<<"f: "<<f;


    QVector<double> x;
    QVector<double> y;
    x.resize(N_INWND);
    y.resize(N_INWND);
    for (int k = 0; k < koeffs.size(); k++)

    for (int j = 0; j < f.size(); j++)
    {
        double ff = 2*M_PI*f[j];
        double xx = 0.01;
        double yy = 0;
        for (int k = 0; k < koeffs.size(); k++)
        {
            xx += koeffs[k]*cos(ff*k);
            yy += koeffs[k]*sin(ff*k);
        }
        Par[j] = 1/sqrt(xx*xx + yy*yy);
    }

    int max = Par[0];
    for (int i = 0; i < Par.size(); ++i)
    {
        if (Par[i] > max)
        {
            max = Par[i];
        }
    }
    for (int i = 0; i < Par.size(); ++i)
    {
        Par[i]= Par[i]/max;
    }

    for (int j = 0; j < wnd_count*1; ++j)
    {
    for (int i = 0; i < N_INWND*1; ++i)
    {
        okna_spectrov[j][i] = Par[i];
    }
    }
    //qDebug()<<"Par: "<<Par;
    ui->widget_2->clearGraphs();//Если нужно, то очищаем все графики
    ui->widget_2->addGraph();//Создаем   график
    ui->widget_2->graph(0)->setPen(QColor(0, 0, 255));//задаем цвет точки
    ui->widget_2->xAxis->setLabel("f");//Задаем название осей грфику
    ui->widget_2->yAxis->setLabel("Par");//Задаем название осей грфику
    ui->widget_2->graph(0)->setData(f, Par);//Что и от чего стрить для x(t)
    ui->widget_2->rescaleAxes();
//  ui->widget_2->graph(0)->setData(t, Qprediction);//Что и от чего стрить для x(t)
//  ui->widget_2->xAxis->setRange(-2, 128);//Задаем начальное и конечное положения графику
//  ui->widget_2->yAxis->setRange(-10, 15 );//Задаем начальное и конечное положения
    ui->widget_2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);//Для изменения Zoom графика
    ui->widget_2->replot();
}
