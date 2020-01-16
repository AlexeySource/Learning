#include "mainwindow.h"
#include "ui_mainwindow.h"

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


double MainWindow::Eps(QVector<QVector<int>> Image1, QVector<QVector<int>> Image2)
{
    double res=0;
    double sum1=0;
    double sum2=0;

    for(int i = int(w_size/2); i < Image1.size() -int(w_size/2); i++)
    {
        for(int j = int(w_size/2); j < Image1.size() -int(w_size/2); j++)
        {
            sum1+= double((Image1[i][j]-Image2[i][j])*(Image1[i][j]-Image2[i][j]));
            sum2+= double(Image1[i][j]*Image1[i][j]);
        }
    }
    res=sum1/sum2;
    //qDebug()<<res;
    return res;
}

double MainWindow::GetContast(QVector<QVector<int>> Image)
{
    double MaxBrightPixel = 0;
    double AverageBrightness = 0;
    for(int i = int(w_size/2); i < 512-int(w_size/2); i++)
    {
        for(int j = int(w_size/2); j < 512-int(w_size/2); j++)
        {
            if (Image[i][j] > MaxBrightPixel) MaxBrightPixel = Image[i][j];
            AverageBrightness +=double(Image[i][j])/512/512;
        }
    }
    //qDebug()<<"MaxBrightPixel"<<MaxBrightPixel;
    //qDebug()<<"AverageBrightness"<<AverageBrightness;
    double Sigma = 0;
    for(int i = int(w_size/2); i < 512-int(w_size/2); i++)
    {
        for(int j = int(w_size/2); j < 512-int(w_size/2); j++)
        {
            Sigma += (double(Image[i][j])-MaxBrightPixel)*(double(Image[i][j])-MaxBrightPixel)/512/512;
        }
    }
    //qDebug()<<"Sigma"<<Sigma<<"sqrt"<<sqrt(Sigma);
    double Contrast = 2*sqrt(Sigma)/MaxBrightPixel;
    //double Contrast = sqrt(Sigma);
    return Contrast;
}

QVector<QVector<int>> MainWindow::IncreaseBrighness(QVector<QVector<int> > Image)
{



    double k = ui->doubleSpinBox_k->value();
    double b = ui->doubleSpinBox_b->value();
    for(int i = 0; i < 512; i++)
    {
        for(int j = 0; j < 512; j++)
        {
            Image[i][j] = int(double(Image[i][j])*k+b);
            if (Image[i][j]>255) Image[i][j] = 255;

        }
    }

//    for(int i = 0; i < 512; i++)
//    {
//        for(int j = 0; j < 512; j++)
//        {
//            Image[i][j] = int(double(Image[i][j])*1.1);
//            if(Image[i][j]>255) Image[i][j] = 255;
//        }
//    }

    return Image;
}

QVector<QVector<int>> MainWindow::NormaliseImage(QVector<QVector<int>> Image)
{
    int MaxElem = 0;
    for(int i = 0; i < 512; i++)
    {
        for(int j = 0; j < 512; j++)
        {
            if (Image[i][j] > MaxElem) MaxElem = Image[i][j];
        }
    }
    for(int i = 0; i < 512; i++)
    {
        for(int j = 0; j < 512; j++)
        {
           Image[i][j]= 255*(double(Image[i][j])/MaxElem);
        }
    }
    return Image;
}



void MainWindow::on_pushButton_Gen_Image_clicked()
{
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
    alpha = ui->doubleSpinBox_alpha->value();


    QImage img("Lenna1.png");
    ImageSrcIntPix.resize(img.width());
    for (int i = 0; i < img.width(); i++)
    {
        ImageSrcIntPix[i].resize(img.height());
    }
    VualMass.resize(img.width());
    for (int i = 0; i < img.width(); i++)
    {
        VualMass[i].resize(img.height());
    }

    ImgPlusVual.resize(img.width());
    for (int i = 0; i < img.width(); i++)
    {
        ImgPlusVual[i].resize(img.height());
    }


    for(int i = 0; i < img.width(); i++)
    {
        for(int j = 0; j < img.height(); j++)
        {
            QRgb rgb = img.pixel(i,j);            
            double color = 0.299*qRed(rgb) + 0.587*qGreen(rgb) + 0.114*qBlue(rgb);
            ImageSrcIntPix[i][j]=int(color);
        }
    }



    ImageSrcIntPix = NormaliseImage(ImageSrcIntPix);

    for(int i = 0; i < img.width(); i++)
    {
        for(int j = 0; j < img.height(); j++)
        {
            QRgb rgb = ImageSrcIntPix[i][j];
            rgb = qRgb(rgb, rgb, rgb);
            img.setPixel(i,j,rgb);
        }
    }
    ui->label_Img1->setPixmap(QPixmap::fromImage(img).scaled(256,256, Qt::KeepAspectRatio));
    ImageGauss.resize(img.width());
    for (int i = 0; i < img.width(); i++)
    {
        ImageGauss[i].resize(img.height());
    }

    double MaxElem = 0;
    for(int i = 0; i < img.width(); i++)
    {
        for(int j = 0; j < img.height(); j++)
        {
            ImageGauss[i][j] = A1*exp(-((((double(i)-X01)*(double(i)-X01))/(SigmaX1*SigmaX1)) + (((double(j)-Y01)*(double(j)-Y01))/(SigmaY1*SigmaY1))))
                        + A2*exp(-((((double(i)-X02)*(double(i)-X02))/(SigmaX2*SigmaX2)) + (((double(j)-Y02)*(double(j)-Y02))/(SigmaY2*SigmaY2))))
                        + A3*exp(-(((double(i)-X03)*(double(i)-X03)/(SigmaX3*SigmaX3)) + ((double(j)-Y03)*(double(j)-Y03)/(SigmaY3*SigmaY3))));
        }
    }
    for(int i = 0; i < img.width(); i++)
    {
        for(int j = 0; j < img.height(); j++)
        {
            if (ImageGauss[i][j] > MaxElem) MaxElem = ImageGauss[i][j];
        }
    }



    QImage vual(512,512,QImage::Format_RGB32);
    vual.fill(QColor(255, 255, 255, 255));
    for(int i = 0; i < 512; i++)
    {
        for(int j = 0; j < 512; j++)
        {
            int color = (int)(255*ImageGauss[i][j]/MaxElem);
            QRgb rgb = qRgb(color, color, color);
            vual.setPixel(i,j,rgb);

            rgb = vual.pixel(i,j);
            color = 0.299*qRed(rgb) + 0.587*qGreen(rgb) + 0.114*qBlue(rgb);
            VualMass[i][j]=int(color);
        }
    }

    //ui->label_Vual->setPixmap(QPixmap::fromImage(vual).scaled(256,256, Qt::KeepAspectRatio));
    ui->label_Vual->setPixmap(QPixmap::fromImage(img).scaled(256,256, Qt::KeepAspectRatio));

    for(int i = 0; i < img.width(); i++)
    {
        for(int j = 0; j < img.height(); j++)
        {
           ImgPlusVual[i][j]= ImageSrcIntPix[i][j]+VualMass[i][j]*alpha;
           if (ImgPlusVual[i][j]>255)  ImgPlusVual[i][j] = 255;
        }
    }

    ImgPlusVual = NormaliseImage(ImgPlusVual);

    QImage ImgVual(512,512,QImage::Format_RGB32);
    ImgVual.fill(QColor(255, 255, 255, 255));
    for(int i = 0; i < 512; i++)
    {
        for(int j = 0; j < 512; j++)
        {
            QRgb rgb = ImgPlusVual[i][j];
            rgb = qRgb(rgb, rgb, rgb);
            ImgVual.setPixel(i,j,rgb);
        }
    }
    //qDebug()<<vual.pixel(502,502) << vual.pixel(500,500);
    ui->label_Img1->setPixmap(QPixmap::fromImage(ImgVual).scaled(256,256, Qt::KeepAspectRatio));
    ui->textEdit_eps_orig_vual->setText(QString::number(Eps(ImageSrcIntPix,ImgPlusVual)));    

}




void MainWindow::on_pushButton_LinFilter_2_clicked()
{

    ImageSrcLinear = ImgPlusVual;

    int N =ui->spinBox_N->value();

    QVector<int> HN(N*N,1);

    QVector<int> vec;

    int cut = (N/2);
    double mask;
    double sumfiltr;

    for(int w = cut; w < ImageSrcLinear.size()-cut; w++)
    {
        for(int h = cut; h < ImageSrcLinear.size()-cut; h++)
        {
            for(int row = -1*cut; row <= cut; row++)
            {
                for(int column = -1*cut; column <= cut; column++)
                {
                    vec.push_back((ImageSrcLinear[w+row][h+column]));
                }
            }
            mask = 0;
            sumfiltr = 0;
            for(int i = 0; i < N*N; i++)
            {
                mask += vec[i]*HN[i];
                sumfiltr += HN[i];
            }
            ImageSrcLinear[w][h] = int(mask/sumfiltr);
            vec.clear();
        }
    }

    ImageForeMinus = ImageSrcLinear;

    QImage imgfiltred(512,512,QImage::Format_RGB32);
    for(int i = 0; i < imgfiltred.width(); i++)
    {
        for(int j = 0; j < imgfiltred.height(); j++)
        {
            QRgb rgb = ImageSrcLinear[i][j];
            rgb = qRgb(rgb, rgb, rgb);
            imgfiltred.setPixel(i,j,rgb);
        }
    }
    ui->label_Img2->setPixmap(QPixmap::fromImage(imgfiltred).scaled(256,256, Qt::KeepAspectRatio));

}

void MainWindow::on_pushButton_LinFilter_3_clicked()
{
    ImageSrcLinear = ImgPlusVual;

    int N =ui->spinBox_N->value();
    QVector<QVector<double>> gausswnd;
    int n2 = ui->spinBox_N->value();
    gausswnd.resize(n2);
    for(int i = 0; i < n2; i++)
    {
        gausswnd[i].resize(n2);
    }

    double sigma = double(n2/2);
    //ui->doubleSpinBox_SigmaWnd->setValue(sigma);
    qDebug()<<"sigma"<<sigma;

    double center = n2/2;
    double gauss_summ = 0;

    for(int i = 0; i < n2; i++)
    {
        for(int j = 0; j < n2; j++)
        {
            gausswnd[i][j] = 1*exp(-((((double(i)-center)*(double(i)-center))/(sigma*sigma)) + (((double(j)-center)*(double(j)-center))/(sigma*sigma))));
        }
    }

    QVector<double> HGauss(n2*n2);
    for(int i = 0; i < n2; i++)
    {
        for(int j = 0; j < n2; j++)
        {
            HGauss[i*n2+j]=gausswnd[i][j];
        }
    }

    for(int i = 0; i < n2; i++)
    {
        qDebug()<<gausswnd[i];
        for(int j = 0; j < n2; j++)
        {
            gauss_summ += gausswnd[i][j];
        }
    }
    qDebug()<<HGauss;
    qDebug()<<"gauss_summ"<<gauss_summ;

    QVector<int> vec;

    int cut = (N/2);
    qDebug()<<"cut"<<cut;
    double mask;
    double sumfiltr;

    for(int w = cut; w < ImageSrcLinear.size()-cut; w++)
    {
        for(int h = cut; h < ImageSrcLinear.size()-cut; h++)
        {
            for(int row = -1*cut; row <= cut; row++)
            {
                for(int column = -1*cut; column <= cut; column++)
                {
                    vec.push_back((ImageSrcLinear[w+row][h+column]));
                }
            }
            mask = 0;
            sumfiltr = 0;
            for(int i = 0; i < N*N; i++)
            {
                mask += double(vec[i])*HGauss[i];
                sumfiltr += HGauss[i];
            }
            ImageSrcLinear[w][h] = int(mask/sumfiltr);
            vec.clear();
        }
    }

    ImageForeMinus = ImageSrcLinear;

    QImage imgfiltred(512,512,QImage::Format_RGB32);
    for(int i = 0; i < imgfiltred.width(); i++)
    {
        for(int j = 0; j < imgfiltred.height(); j++)
        {
            QRgb rgb = ImageSrcLinear[i][j];
            rgb = qRgb(rgb, rgb, rgb);
            imgfiltred.setPixel(i,j,rgb);
        }
    }
    ui->label_Img2->setPixmap(QPixmap::fromImage(imgfiltred).scaled(256,256, Qt::KeepAspectRatio));
}





void MainWindow::on_pushButton_MedFilter_2_clicked()
{

    QVector<QVector<int>> ImageSrcMedian = ImgPlusVual;


    int N =ui->spinBox_N->value();
    w_size = N;
    int cut = (N/2);
    qDebug()<<"cut"<<cut;

    QVector<int> vec;
    for(int w = cut; w < ImageSrcMedian.size()-cut; w++)
    {
        for(int h = cut; h < ImageSrcMedian.size()-cut; h++)
        {
            for(int row = -1*cut; row <= cut; row++)
            {
                for(int column = -1*cut; column <= cut; column++)
                {
                    vec.push_back((ImageSrcMedian[w+row][h+column]));
                }
            }

            qSort(vec.begin(),vec.end());
            ImageSrcMedian[w][h] = vec.at(N*N/2);
            vec.clear();
        }
    }

    ImageForeMinus = ImageSrcMedian;

    QImage imgfiltred(512,512,QImage::Format_RGB32);
    for(int i = 0; i < imgfiltred.width(); i++)
    {
        for(int j = 0; j < imgfiltred.height(); j++)
        {
            QRgb rgb = ImageSrcMedian[i][j];
            rgb = qRgb(rgb, rgb, rgb);
            imgfiltred.setPixel(i,j,rgb);
        }
    }
    ui->label_Img2->setPixmap(QPixmap::fromImage(imgfiltred).scaled(256,256, Qt::KeepAspectRatio));

}

void MainWindow::on_pushButton_clicked()
{

    w_size = ui->spinBox_N->value();

    ImageAfterMinus.resize(512);
    for(int i = 0; i < ImageAfterMinus.size(); i++)
    {
        ImageAfterMinus[i].resize(512);
    }


    double mu = ui->doubleSpinBox_mu->value();

    for(int i = 0; i < 512; i++)
    {
        for(int j = 0; j < 512; j++)
        {
            ImageAfterMinus[i][j] = (double(ImgPlusVual[i][j]) - mu * double(ImageForeMinus[i][j]));
            if (ImageAfterMinus[i][j]<0) ImageAfterMinus[i][j] = 0;
        }
    }



    ImageAfterMinus = NormaliseImage(ImageAfterMinus);

    QImage imgfiltred(512,512,QImage::Format_RGB32);
    for(int i = 0; i < imgfiltred.width(); i++)
    {
        for(int j = 0; j < imgfiltred.height(); j++)
        {
            QRgb rgb = ImageAfterMinus[i][j];
            rgb = qRgb(rgb, rgb, rgb);
            imgfiltred.setPixel(i,j,rgb);
        }
    }

    ui->label_ImgMinus->setPixmap(QPixmap::fromImage(imgfiltred).scaled(256,256, Qt::KeepAspectRatio));
    ui->textEdit_eps_orig_filtered->setText(QString::number(Eps(ImageSrcIntPix,ImageAfterMinus)));


    ui->textEdit_Contraste_Orig->setText(QString::number(GetContast(ImageSrcIntPix)));
    ui->textEdit_Contraste_ImgPlusVual->setText(QString::number(GetContast(ImgPlusVual)));
    ui->textEdit_Contraste_Restored->setText(QString::number(GetContast(ImageAfterMinus)));
    ui->textEdit_Difference_Contraste->setText(QString::number(fabs(GetContast(ImageSrcIntPix)-GetContast(ImageAfterMinus))));

}


void MainWindow::on_pushButton_IncreaseBrightness_clicked()
{

    on_pushButton_clicked();
    ImageAfterMinus = IncreaseBrighness(ImageAfterMinus);
    ImageAfterMinus = NormaliseImage(ImageAfterMinus);
    QImage imgfiltred(512,512,QImage::Format_RGB32);
    for(int i = 0; i < imgfiltred.width(); i++)
    {
        for(int j = 0; j < imgfiltred.height(); j++)
        {
            QRgb rgb = ImageAfterMinus[i][j];
            rgb = qRgb(rgb, rgb, rgb);
            imgfiltred.setPixel(i,j,rgb);
        }
    }

    ui->label_ImgMinus->setPixmap(QPixmap::fromImage(imgfiltred).scaled(256,256, Qt::KeepAspectRatio));
    ui->textEdit_Contraste_Restored->setText(QString::number(GetContast(ImageAfterMinus)));
    ui->textEdit_Difference_Contraste->setText(QString::number(fabs(GetContast(ImageSrcIntPix)-GetContast(ImageAfterMinus))));

}



void MainWindow::on_pushButton_analise_clicked()
{

 t.resize(100);
    for(int i=0;i<t.size();i++)
    {
        t[i]=i;
    }

    ui->widget->clearGraphs();//Если нужно, то очищаем все графики
    ui->widget->addGraph();//Создаем   график
    ui->widget->graph(0)->setPen(QColor(0, 0, 255));//задаем цвет точки
    ui->widget->graph(0)->setName(tr("Contraste"));
    ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
    //ui->widget->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->widget->legend->setVisible(1);
    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);//Для изменения Zoom графика
    ui->widget->xAxis->setTickStep(1);
    //ui->widget->graph(0)->addData(0,0);

    for(int i=0;i<21;i++)
    {


        ui->spinBox_N->setValue(3+2*i);
        on_pushButton_MedFilter_2_clicked();
        on_pushButton_clicked();
        double data = ui->textEdit_Contraste_Restored->toPlainText().toDouble();
        qDebug()<<"contrast"<<data;
        ui->widget->graph(0)->addData(ui->spinBox_N->value(), data);
        ui->widget->rescaleAxes();
        ui->widget->replot();
    }
}
