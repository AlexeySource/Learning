#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QImage imgforcheck("D:/Qt Projects/1MAG/k5_z1_IT/pic1.png");
    QImage imgforcheck2("D:/Qt Projects/1MAG/k5_z1_IT/pic2.png");
    QImage imgforcheck3("D:/Qt Projects/1MAG/k5_z1_IT/pic3.png");
    QImage imgforcheck4("D:/Qt Projects/1MAG/k5_z1_IT/pic4.png");
    ui->label_Img->setPixmap(QPixmap::fromImage(imgforcheck).scaled(130,130, Qt::KeepAspectRatio));
    ui->label_Img_2->setPixmap(QPixmap::fromImage(imgforcheck2).scaled(150,150, Qt::KeepAspectRatio));
    ui->label_Img_3->setPixmap(QPixmap::fromImage(imgforcheck3).scaled(150,150, Qt::KeepAspectRatio));
    ui->label_Img_4->setPixmap(QPixmap::fromImage(imgforcheck4).scaled(150,150, Qt::KeepAspectRatio));

}

MainWindow::~MainWindow()
{
    delete ui;
}



double MainWindow::Eps(QVector<QVector<double>> Image1, QVector<QVector<double>> Image2)
{
    double res=0;
    double sum1=0;
    double sum2=0;

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            sum1+= double((Image1[i][j]-Image2[i][j])*(Image1[i][j]-Image2[i][j]));
            sum2+= double(Image1[i][j]*Image1[i][j]);
        }
    }
    res=sum1/sum2;
    qDebug()<<res;
    return res;

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

double MainWindow::Energy2d(QVector<QVector<double>> & S)
{
    double summ = 0;
    for (int i = 0; i< S.size(); i++)
    {
        for (int j = 0; j< S.size(); j++)
        {
           summ += S[i][j] * S[i][j];
        }

    }
    return summ;
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


QVector<double> MainWindow::AddNoise(QVector<double>&Signal, double noise_procent, QVector<QVector<double>> & Signal2d)
{
    double E_s = Energy2d(Signal2d);
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
    //qDebug()<<"noise_energy: " << noise_energy;
    return N;
}


void MainWindow::gen_image()
{
    for (int i = 0; i<t.size(); i++)
    {
        t[i] = i;
    }
    int MaxElem = 0;

    if (ui->checkBox_img1->isChecked())
    {
        QImage img;
        if (ui->radioButton->isChecked())
        {
             img.load("D:/Qt Projects/1MAG/k5_z1_IT/pic1.png");
            qDebug()<<"1";
        }
        if (ui->radioButton_2->isChecked())
        {
            img.load("D:/Qt Projects/1MAG/k5_z1_IT/pic2.png");
            qDebug()<<"2";
        }
        if (ui->radioButton_3->isChecked())
        {
            img.load("D:/Qt Projects/1MAG/k5_z1_IT/pic3.png");
            qDebug()<<"3";
        }
        if (ui->radioButton_4->isChecked())
        {
            img.load("D:/Qt Projects/1MAG/k5_z1_IT/pic4.png");
            qDebug()<<"4";
        }

        Image.resize(img.width());
        for (int i = 0; i < img.height(); i++)
        {
            Image[i].resize(img.width());
        }
        N = img.height();
//        ui->label_Img->setPixmap(QPixmap::fromImage(img).scaled(150,150, Qt::KeepAspectRatio));
        img = img.mirrored(0,1);

        for(int i = 0; i < img.height(); i++)
        {
            for(int j = 0; j < img.width(); j++)
            {
                Image[i][j] = qRed(img.pixel(i,j))*0.3 + qGreen(img.pixel(i,j))*0.59 + qBlue(img.pixel(i,j))*0.11;
            }
        }
    }
    else
    {
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < N; j++)
            {
                Image[i][j] = A1*exp(-((((double(i)-X01)*(double(i)-X01))/(SigmaX1*SigmaX1)) + (((double(j)-Y01)*(double(j)-Y01))/(SigmaY1*SigmaY1))))
                            + A2*exp(-((((double(i)-X02)*(double(i)-X02))/(SigmaX2*SigmaX2)) + (((double(j)-Y02)*(double(j)-Y02))/(SigmaY2*SigmaY2))))
                            + A3*exp(-(((double(i)-X03)*(double(i)-X03)/(SigmaX3*SigmaX3)) + ((double(j)-Y03)*(double(j)-Y03)/(SigmaY3*SigmaY3))))
                            + A4*exp(-(((double(i)-X04)*(double(i)-X04)/(SigmaX4*SigmaX4)) + ((double(j)-Y04)*(double(j)-Y04)/(SigmaY4*SigmaY4))))
                            + A5*exp(-(((double(i)-X05)*(double(i)-X05)/(SigmaX5*SigmaX5)) + ((double(j)-Y05)*(double(j)-Y05)/(SigmaY5*SigmaY5))));
                if (Image[i][j] > MaxElem) MaxElem = Image[i][j];
            }
        }
    }


    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            ImageClear[i][j]= Image[i][j];
        }
    }
        qDebug()<<"img clear 12 12"<<ImageClear[12][12];

    for(int i = 0; i < N; i++)
    {
        Image[i]= AddNoise(Image[i],noise_procent, Image);
    }
    qDebug()<<"img noise 12 12"<<Image[12][12];

    ui->textEdit->setText(QString::number(Eps(ImageClear,Image)));



}

void MainWindow::FUR_For_2D()
{
    cmplx*data_in_line1=new cmplx[N];
//    QVector<QVector<cmplx>> data_cmplx;
    data_cmplx.resize(N);
    for (int i = 0; i < N; i++)
    {
        data_cmplx[i].resize(N);
    }

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            data_in_line1[j].real = Image[i][j];
            data_in_line1[j].image = 0;
        }
        FUR(data_in_line1,N,-1);
        for(int j=0; j<N; j++)
        {
            data_cmplx[i][j].real = data_in_line1[j].real;
            data_cmplx[i][j].image = data_in_line1[j].image;
        }
    }

    for(int i = 0; i < N; i++)
    {

        for(int j = 0; j < N; j++)
        {
            data_in_line1[j].real = data_cmplx[j][i].real;
            data_in_line1[j].image = data_cmplx[j][i].image;
        }
        FUR(data_in_line1,N,-1);
        for(int j=0; j<N; j++)
        {
            data_cmplx[j][i].real = data_in_line1[j].real;
            data_cmplx[j][i].image = data_in_line1[j].image;
            SpectrImage[j][i]=sqrt(data_cmplx[j][i].real*data_cmplx[j][i].real+data_cmplx[j][i].image*data_cmplx[j][i].image);

//            SpectrImage[j][i]=sqrt(data_in_line1[j].real*data_in_line1[j].real+data_in_line1[j].image*data_in_line1[j].image);
        }
    }







    SpectrImageCentr = SpectrImageTransform(SpectrImage);



}

void MainWindow::FUR_For_2D_Obr()
{

    cmplx*data_in_line1=new cmplx[N];
    //QVector<QVector<cmplx>> data_cmplx;
//    data_cmplx.resize(N);
//    for (int i = 0; i < N; i++)
//    {
//        data_cmplx[i].resize(N);
//    }

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            data_in_line1[j].real = data_cmplx[i][j].real;
            data_in_line1[j].image = data_cmplx[i][j].image;
        }
        FUR(data_in_line1,N,1);
        for(int j=0; j<N; j++)
        {
            data_cmplx[i][j].real = data_in_line1[j].real;
            data_cmplx[i][j].image = data_in_line1[j].image;
        }
    }

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            data_in_line1[j].real = data_cmplx[j][i].real;
            data_in_line1[j].image = data_cmplx[j][i].image;
        }
        FUR(data_in_line1,N,1);
        for(int j=0; j<N; j++)
        {
            ImageRestored[j][i]=sqrt(data_in_line1[j].real*data_in_line1[j].real+data_in_line1[j].image*data_in_line1[j].image);
        }
    }
}

void MainWindow::ClearSpectr()
{
    SpectrImage[0][0] = 0;
//    data_cmplx[0][0].real = 0;
//    data_cmplx[0][0].image = 0;

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            SpectrImageCleared[i][j] = SpectrImage[i][j];
        }
    }
    SpectrEnergy00 = SpectrImage[0][0]*SpectrImage[0][0];
    SpectrEnergyFull = 0;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            SpectrEnergyFull += SpectrImage[i][j]*SpectrImage[i][j];
        }
    }

    qDebug()<< "SpectrEnergyFull"<<SpectrEnergyFull;



    int range = 0;
    double SpectrEnergy;
    do
    {
        SpectrEnergy = 0;
          for(int i = 0; i < range; i++)
          {
              for(int j = 0; j < range; j++)
              {
                  SpectrEnergy += SpectrImage[i][j]*SpectrImage[i][j];
              }
          }
          for(int i = N-1; i > N-1 - range; i--)
          {
              for(int j = N-1; j > N-1 - range; j--)
              {
                  SpectrEnergy += SpectrImage[i][j]*SpectrImage[i][j];
              }
          }
          for(int i = N-1; i > N-1 - range; i--)
          {
              for(int j = 0; j < range; j++)
              {
                  SpectrEnergy += SpectrImage[i][j]*SpectrImage[i][j];
              }
          }
          for(int i = 0; i < range; i++)
          {
              for(int j = N-1; j > N-1 - range; j--)
              {
                  SpectrEnergy += SpectrImage[i][j]*SpectrImage[i][j];
              }
          }

          range++;
    }
    while (SpectrEnergy < ClearProcent/100*SpectrEnergyFull);
    qDebug()<< "range"<<range;
    qDebug()<< "SpectrEnergy"<<SpectrEnergy;


    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(i>range && i<(N-range) || (j>range && j<(N-range)))
            {
                SpectrImageCleared[i][j] = 0;

                data_cmplx[i][j].real = 0;
                data_cmplx[i][j].image = 0;                
            }
        }
    }



    SpectrImageClearedCentr = SpectrImageTransform(SpectrImageCleared);
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
         if (i==(N/2+range) && j>N/2-range-1 && j<N/2+range+1)
         {
             SpectrImageClearedCentr[i+1][j] = 12;
         }
         if (i==(N/2-range) && j>N/2-range-1 && j<N/2+range+1)
         {
             SpectrImageClearedCentr[i-1][j] = 12;
         }
        }
    }

    // configure axis rect:
    ui->widget_2->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
    ui->widget_2->axisRect()->setupFullAxesBox(true);
    ui->widget_2->xAxis->setLabel("N");
    ui->widget_2->yAxis->setLabel("N");
    // set up the QCPColorMap:
    QCPColorMap *colorMap2 = new QCPColorMap(ui->widget_2->xAxis, ui->widget_2->yAxis);
    colorMap2->setInterpolate(1);
    colorMap2->data()->setSize(N, N); // we want the color map to have nx * ny data points
    colorMap2->data()->setRange(QCPRange(0, N), QCPRange(0, N)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
    // now we assign some data, by accessing the QCPColorMapData instance of the color map:

    for (int x=0; x<N; ++x)
    {
        for (int y=0; y<N; ++y)
        {
            double r = SpectrImageClearedCentr[x][y];
            colorMap2->data()->setCell(x, y, r);

        }
    }

    // add a color scale:
    QCPColorScale *colorScale2 = new QCPColorScale(ui->widget_2);
    ui->widget_2->plotLayout()->addElement(0, 1, colorScale2); // add it to the right of the main axis rect
    colorScale2->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)

    colorMap2->setColorScale(colorScale2); // associate the color map with the color scale
   // colorScale->axis()->setLabel("Magnetic Field Strength");
    // set the color gradient of the color map to one of the presets:
    colorMap2->setGradient(QCPColorGradient::gpGrayscale);
    // we could have also created a QCPColorGradient instance and added own colors to
    // the gradient, see the documentation of QCPColorGradient for what's possible.
    // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:
    colorMap2->setDataScaleType(QCPAxis::stLogarithmic);
    //colorMap2->set
    colorMap2->rescaleDataRange();
    // make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
    QCPMarginGroup *marginGroup2 = new QCPMarginGroup(ui->widget_2);
    ui->widget_2->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup2);
    colorScale2->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup2);
    // rescale the key (x) and value (y) axes so the whole color map is visible:
    ui->widget_2->xAxis->setRange(0, N);//Задаем начальное и конечное положения графику
    ui->widget_2->yAxis->setRange(0, N);//Задаем начальное и конечное положения графику
    ui->widget_2->rescaleAxes();
    ui->widget_2->replot();

}


//void MainWindow::Interpolation()
//{



//}


//void MainWindow::Interpolation()
//{
//    for (int i = 0; i < N; i++)
//    {
//        for (int j = 0; j < N; j++)
//        {

//        }
//    }
//}

QVector<QVector<double> > MainWindow::SpectrImageTransform(QVector<QVector<double> > SpectrImage)
{

        QVector<QVector<double>> SpectrImageTmp;
        SpectrImageTmp.resize(N/2);
        for (int i = 0; i < SpectrImageTmp.size(); i++)
        {
            SpectrImageTmp[i].resize(N/2);
        }

        QVector<QVector<double>> res;
        res.resize(N/2);
        for (int i = 0; i < res.size(); i++)
        {
            res[i].resize(N/2);
        }


        for(int i = 0; i < N/2; i++)
        {
            for(int j = 0; j < N/2; j++)
            {
                SpectrImageTmp[i][j] = SpectrImage[i+N/2][j+N/2];
            }
        }

        for(int i = 0; i < N/2; i++)
        {
            for(int j = 0; j < N/2; j++)
            {
                SpectrImage[i+N/2][j+N/2] = SpectrImage[i][j];
            }
        }
        for(int i = 0; i < N/2; i++)
        {
            for(int j = 0; j < N/2; j++)
            {
                SpectrImage[i][j] = SpectrImageTmp[i][j];
            }
        }

        for(int i = 0; i < N/2; i++)
        {
            for(int j = 0; j < N/2; j++)
            {
                SpectrImageTmp[i][j] = SpectrImage[i+N/2][j];
            }
        }
        for(int i = 0; i < N/2; i++)
        {
            for(int j = 0; j < N/2; j++)
            {
                SpectrImage[i+N/2][j] = SpectrImage[i][j+N/2];
            }
        }
        for(int i = 0; i < N/2; i++)
        {
            for(int j = 0; j < N/2; j++)
            {
                SpectrImage[i][j+N/2] = SpectrImageTmp[i][j];
            }
        }
        return SpectrImage;
}

void MainWindow::on_pushButtonGenImage_clicked()
{

    N = ui->doubleSpinBox_N->value();
    noise_procent = ui->doubleSpinBox_NoiseProcent->value();
    A1 = ui->doubleSpinBox_A1->value();
    X01 = ui->doubleSpinBox_X01->value();
    Y01 = ui->doubleSpinBox_Y01->value();
    SigmaX1 = ui->doubleSpinBox_SigmaX1->value();
    SigmaY1 = ui->doubleSpinBox_SigmaY1->value();
    A2 = ui->doubleSpinBox_A2->value();
    X02 = ui->doubleSpinBox_X02->value();
    Y02 = ui->doubleSpinBox_Y02->value();
    SigmaX2 = ui->doubleSpinBox_SigmaX2->value();
    SigmaY2 = ui->doubleSpinBox_SigmaY2->value();
    A3 = ui->doubleSpinBox_A3->value();
    X03 = ui->doubleSpinBox_X03->value();
    Y03 = ui->doubleSpinBox_Y03->value();
    SigmaX3 = ui->doubleSpinBox_SigmaX3->value();
    SigmaY3 = ui->doubleSpinBox_SigmaY3->value();
    A4 = ui->doubleSpinBox_A4->value();
    X04 = ui->doubleSpinBox_X04->value();
    Y04 = ui->doubleSpinBox_Y04->value();
    SigmaX4 = ui->doubleSpinBox_SigmaX4->value();
    SigmaY4 = ui->doubleSpinBox_SigmaY4->value();
    A5 = ui->doubleSpinBox_A5->value();
    X05 = ui->doubleSpinBox_X05->value();
    Y05 = ui->doubleSpinBox_Y05->value();
    SigmaX5 = ui->doubleSpinBox_SigmaX5->value();
    SigmaY5 = ui->doubleSpinBox_SigmaY5->value();



    t.resize(N);
    Image.resize(N);
    for (int i = 0; i < Image.size(); i++)
    {
        Image[i].resize(N);
    }
    ImageClear.resize(N);
    for (int i = 0; i < ImageClear.size(); i++)
    {
        ImageClear[i].resize(N);
    }
    ImageRestored.resize(N);
    for (int i = 0; i < ImageRestored.size(); i++)
    {
        ImageRestored[i].resize(N);
    }
    SpectrImage.resize(N);
    for (int i = 0; i < SpectrImage.size(); i++)
    {
        SpectrImage[i].resize(N);
    }
    SpectrImageCentr.resize(N);
    for (int i = 0; i < SpectrImageCentr.size(); i++)
    {
        SpectrImageCentr[i].resize(N);
    }
    SpectrImageCleared.resize(N);
    for (int i = 0; i < SpectrImageCleared.size(); i++)
    {
        SpectrImageCleared[i].resize(N);
    }

    qDebug()<<Image.size()<<Image[0].size();



    gen_image();
    FUR_For_2D();


    // configure axis rect:
    ui->widget->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
    ui->widget->axisRect()->setupFullAxesBox(true);
    ui->widget->xAxis->setLabel("N");
    ui->widget->yAxis->setLabel("N");
    // set up the QCPColorMap:
    QCPColorMap *colorMap = new QCPColorMap(ui->widget->xAxis, ui->widget->yAxis);
    colorMap->setInterpolate(0);
    colorMap->data()->setSize(N, N); // we want the color map to have nx * ny data points
    colorMap->data()->setRange(QCPRange(0, N), QCPRange(0, N)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
    // now we assign some data, by accessing the QCPColorMapData instance of the color map:
    //double x, y, z;
    for (int x=0; x<N; ++x)
    {
       // qDebug()<<"okna_spectov[wnd_count][0]"<<okna_spectrov[x][0];
        for (int y=0; y<N; ++y)
        {
            double r = Image[x][y];
            colorMap->data()->setCell(x, y, r);

        }
    }

    // add a color scale:
    QCPColorScale *colorScale = new QCPColorScale(ui->widget);
    ui->widget->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect
    colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
    colorMap->setColorScale(colorScale); // associate the color map with the color scale
   // colorScale->axis()->setLabel("Magnetic Field Strength");
    // set the color gradient of the color map to one of the presets:
    colorMap->setGradient(QCPColorGradient::gpGrayscale);
    // we could have also created a QCPColorGradient instance and added own colors to
    // the gradient, see the documentation of QCPColorGradient for what's possible.
    // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:
    colorMap->rescaleDataRange();
    // make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->widget);
    ui->widget->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    // rescale the key (x) and value (y) axes so the whole color map is visible:
    ui->widget->xAxis->setRange(0, N);//Задаем начальное и конечное положения графику
    ui->widget->yAxis->setRange(0, N);//Задаем начальное и конечное положения графику
    ui->widget->rescaleAxes();
    ui->widget->replot();
//////////////////////////////////////////////////////////


    // configure axis rect:
    ui->widget_2->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
    ui->widget_2->axisRect()->setupFullAxesBox(true);
    ui->widget_2->xAxis->setLabel("N");
    ui->widget_2->yAxis->setLabel("N");
    // set up the QCPColorMap:
    QCPColorMap *colorMap2 = new QCPColorMap(ui->widget_2->xAxis, ui->widget_2->yAxis);
    colorMap2->setInterpolate(1);
    colorMap2->data()->setSize(N, N); // we want the color map to have nx * ny data points
    colorMap2->data()->setRange(QCPRange(0, N), QCPRange(0, N)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
    // now we assign some data, by accessing the QCPColorMapData instance of the color map:
    //double x, y, z;
   // QImage img("путь");
    //QRgb p = img.pixel(x,y);
    //    qRed(p)+qGreen(p)+qBlue(p)
    for (int x=0; x<N; ++x)
    {

        for (int y=0; y<N; ++y)
        {
            double r = SpectrImageCentr[x][y];
            colorMap2->data()->setCell(x, y, r);

        }
    }

    // add a color scale:
    QCPColorScale *colorScale2 = new QCPColorScale(ui->widget_2);
    ui->widget_2->plotLayout()->addElement(0, 1, colorScale2); // add it to the right of the main axis rect
    colorScale2->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
    colorMap2->setColorScale(colorScale2); // associate the color map with the color scale
   // colorScale->axis()->setLabel("Magnetic Field Strength");
    // set the color gradient of the color map to one of the presets:
    colorMap2->setGradient(QCPColorGradient::gpGrayscale);
    // we could have also created a QCPColorGradient instance and added own colors to
    // the gradient, see the documentation of QCPColorGradient for what's possible.
    // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:
    colorMap2->rescaleDataRange();
    // make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
    QCPMarginGroup *marginGroup2 = new QCPMarginGroup(ui->widget_2);
    ui->widget_2->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup2);
    colorScale2->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup2);
    // rescale the key (x) and value (y) axes so the whole color map is visible:
    ui->widget_2->xAxis->setRange(0, N);//Задаем начальное и конечное положения графику
    ui->widget_2->yAxis->setRange(0, N);//Задаем начальное и конечное положения графику
    ui->widget_2->rescaleAxes();
    ui->widget_2->replot();


}



void MainWindow::on_pushButtonClearSpectr_clicked()
{
    ClearProcent = ui->doubleSpinBox_ClearProcent->value();
    //Image[0][0] = SpectrEnergy00;

    ClearSpectr();
}


void MainWindow::on_pushButton_RestoreImage_clicked()
{
qDebug()<<"restore";
//double res;
//for(int i = 0; i < N; i++)
//{
//    for(int j = 0; j < N; j++)
//    {
//        res+= (ImageClear[i][j]-Image[i][j]);//*(Image1[i][j]-Image2[i][j])/(Image1[i][j]*Image1[i][j]);
//    }
//}
//qDebug()<<ImageClear[12][12];



FUR_For_2D_Obr();
 ui->textEdit_2->setText(QString::number(Eps(ImageClear,ImageRestored)));


// configure axis rect:
ui->widget_3->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
ui->widget_3->axisRect()->setupFullAxesBox(true);
ui->widget_3->xAxis->setLabel("N");
ui->widget_3->yAxis->setLabel("N");
// set up the QCPColorMap:
QCPColorMap *colorMap3 = new QCPColorMap(ui->widget_3->xAxis, ui->widget_3->yAxis);
colorMap3->setInterpolate(1);
colorMap3->data()->setSize(N, N); // we want the color map to have nx * ny data points
colorMap3->data()->setRange(QCPRange(0, N), QCPRange(0, N)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
// now we assign some data, by accessing the QCPColorMapData instance of the color map:
//double x, y, z;
// QImage img("путь");
//QRgb p = img.pixel(x,y);
//    qRed(p)+qGreen(p)+qBlue(p)
for (int x=0; x<N; ++x)
{

    for (int y=0; y<N; ++y)
    {
        double r = ImageRestored[x][y];
        colorMap3->data()->setCell(x, y, r);

    }
}

// add a color scale:
QCPColorScale *colorScale3 = new QCPColorScale(ui->widget_3);
ui->widget_3->plotLayout()->addElement(0, 1, colorScale3); // add it to the right of the main axis rect
colorScale3->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
colorMap3->setColorScale(colorScale3); // associate the color map with the color scale
// colorScale->axis()->setLabel("Magnetic Field Strength");
// set the color gradient of the color map to one of the presets:
colorMap3->setGradient(QCPColorGradient::gpGrayscale);
// we could have also created a QCPColorGradient instance and added own colors to
// the gradient, see the documentation of QCPColorGradient for what's possible.
// rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:
colorMap3->rescaleDataRange();
// make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
QCPMarginGroup *marginGroup2 = new QCPMarginGroup(ui->widget_3);
ui->widget_3->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup2);
colorScale3->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup2);
// rescale the key (x) and value (y) axes so the whole color map is visible:
ui->widget_3->xAxis->setRange(0, N);//Задаем начальное и конечное положения графику
ui->widget_3->yAxis->setRange(0, N);//Задаем начальное и конечное положения графику
ui->widget_3->rescaleAxes();
ui->widget_3->replot();
}

void MainWindow::on_pushButton_LoadImage_clicked()
{


    QImage img("D:/Qt Projects/1MAG/k5_z1_IT/pic1.png");
    Image.resize(img.width());
    for (int i = 0; i < img.height(); i++)
    {
        Image[i].resize(img.width());
    }
    N = img.height();
    ui->label_Img->setPixmap(QPixmap::fromImage(img).scaled(150,150, Qt::KeepAspectRatio));
    img = img.mirrored(0,1);

    qDebug()<<img.height()<<img.width();
    for(int i = 0; i < img.height(); i++)
    {
        for(int j = 0; j < img.width(); j++)
        {
            Image[i][j] = qRed(img.pixel(i,j))*0.3 + qGreen(img.pixel(i,j))*0.59 + qBlue(img.pixel(i,j))*0.11;
        }
    }


    // configure axis rect:
    ui->widget->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
    ui->widget->axisRect()->setupFullAxesBox(true);
    ui->widget->xAxis->setLabel("N");
    ui->widget->yAxis->setLabel("N");
    // set up the QCPColorMap:
    QCPColorMap *colorMap = new QCPColorMap(ui->widget->xAxis, ui->widget->yAxis);
    colorMap->setInterpolate(0);
    colorMap->data()->setSize(N, N); // we want the color map to have nx * ny data points
    colorMap->data()->setRange(QCPRange(0, N), QCPRange(0, N)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
    // now we assign some data, by accessing the QCPColorMapData instance of the color map:
    //double x, y, z;
    for (int x=0; x<N; ++x)
    {
       // qDebug()<<"okna_spectov[wnd_count][0]"<<okna_spectrov[x][0];
        for (int y=0; y<N; ++y)
        {
            double r = Image[x][y];
            colorMap->data()->setCell(x, y, r);

        }
    }

    // add a color scale:
    QCPColorScale *colorScale = new QCPColorScale(ui->widget);
    ui->widget->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect
    colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
    colorMap->setColorScale(colorScale); // associate the color map with the color scale
   // colorScale->axis()->setLabel("Magnetic Field Strength");
    // set the color gradient of the color map to one of the presets:
    colorMap->setGradient(QCPColorGradient::gpGrayscale);
    // we could have also created a QCPColorGradient instance and added own colors to
    // the gradient, see the documentation of QCPColorGradient for what's possible.
    // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:
    colorMap->rescaleDataRange();
    // make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->widget);
    ui->widget->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    // rescale the key (x) and value (y) axes so the whole color map is visible:
    ui->widget->xAxis->setRange(0, N);//Задаем начальное и конечное положения графику
    ui->widget->yAxis->setRange(0, N);//Задаем начальное и конечное положения графику
    ui->widget->rescaleAxes();
    ui->widget->replot();
}
