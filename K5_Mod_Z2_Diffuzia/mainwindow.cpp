#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qcustomplot.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer();
        connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_GenStart_clicked()
{
    CountOfSteps = ui->spinBox_MC_StepsCount->value();
    ui->horizontalSlider->setRange(0,CountOfSteps-1);
    ui->Scene_widget->GenStart();    
    ui->Scene_widget->updateGL();
    step = 0;
    ConcentrationOnXAtStep.resize(CountOfSteps);
    for (int i =0; i <ConcentrationOnXAtStep.size(); i++)
    {
        ConcentrationOnXAtStep[i].resize(this->ui->Scene_widget->isPoint.size());
    }

    CoordX.resize(this->ui->Scene_widget->isPoint.size());

    for (int i =0; i <CoordX.size(); i++)
    {
        CoordX[i] =i;
    }
}

void MainWindow::on_pushButton_clicked()
{
    ui->Scene_widget->Diffuzia();
    //ui->Scene_widget->Diffuzia();
    ui->Scene_widget->updateGL();
    for (int i =0; i <ConcentrationOnXAtStep[0].size(); i++)
    {
        ConcentrationOnXAtStep[step][i] = this->ui->Scene_widget->ConcentrationOnX[i];
    }

    step++;
    //qDebug()<<step;
    ui->textEdit_ForStep->setText(QString::number(step));
    ui->horizontalSlider->setRange(0,step-1);

}

void MainWindow::on_pushButton_Animation_clicked()
{
    if (!timer->isActive())
    {
        timer->start(5);
    }
    else timer->stop();

}


void MainWindow::slotTimerAlarm()
{
    on_pushButton_clicked();   
    if (step == CountOfSteps) timer->stop();

}

void MainWindow::findPointsOnField(int x, int y, int n, QVector <QVector <bool> > &point, vector <coord_surface> &coord)
{
    int amountPoints(0);

    for (int xh(x); xh < x+n; ++xh)
        for (int yh(y);yh < y+n; ++yh)
            if(point[xh][yh]) ++amountPoints;

    int cx = int(x + floor(n/2.));
    int cy = int(y + floor(n/2.));
    int cz = amountPoints;
    coord_surface c(cx, cy, cz);

    coord.push_back(c);
}

void MainWindow::createArrayForCartD(double* x, double* y, double* z, int hight, int weight, vector <coord_surface> &coord)
{

    u_int k(0);
    for (int i(0); i < hight; ++i) {
        for (int j(0); j < weight; ++j) {
            x[i] = coord[i*weight+j].x;
            y[j] = coord[i*weight+j].y;
            z[i*weight+j] = coord[i*weight+j].z;
        }
    }
}

void MainWindow::createSurface()
{
    QVector <QVector <bool> > isPoint = ui->Scene_widget->isPoint;
    vector <coord_surface> coord;

    int sHight = isPoint.size() - 1;
    int sWeight = isPoint[0].size() - 1;
    int n = 5;

    for (int x(0); x < sHight; x+=n) //h = 100
            for (int y(0); y < sWeight; y+=n) //w =200
                 findPointsOnField(x, y, n, isPoint, coord);

    sHight/=n;
    sWeight/=n;

    double *chd_x = new double [u_int(sHight)];
    double *chd_y = new double [u_int(sWeight)];
    double *chd_z = new double [u_int(sHight*sWeight)];

    createArrayForCartD(chd_x, chd_y, chd_z, sHight, sWeight, coord);





    //

    c = new SurfaceChart(550, 350);

    c->addTitle("Directional diagram", "timesi.ttf", 20);


    // Set the center of the plot region at (350, 280), and set width x depth x height to 360 x 360
    // x 270 pixels
    c->setPlotRegion(275, 160, 300, 300, 140);

    double dataX[sHight];
    double dataY[sWeight];
    double dataZ[sHight*sWeight];
    for (int i = 0; i<sHight; i++)
    {
        dataX[i] = 2 + i*5;
    }
    for (int i = 0; i<sWeight; i++)
    {
        dataY[i] = 2 + i*5;
    }
    for (int i = 0; i<sHight*sWeight; i++)
    {
        dataZ[i] = chd_z[i];
    }




//-------ПРИМЕР ПРАВИЛЬНЫХ ДАННЫХ. С ЭТИМИ ДАННЫМИ ПОВЕРХНОСТЬ СТРОИТСЯ
    // Set the data to use to plot the chart
//    double dataX[] = {-10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//        double dataY[] = {-10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

        // The values at the grid points. In this example, we will compute the values using the formula
        // z = x * sin(y) + y * sin(x).
        //double dataZ[(int)(sizeof(dataX) / sizeof(dataX[0])) * (int)(sizeof(dataY) / sizeof(dataY[0]))];
//        for(int yIndex = 0; yIndex < (int)(sizeof(dataY) / sizeof(dataY[0])); ++yIndex) {
//            double y = dataY[yIndex];
//            for(int xIndex = 0; xIndex < (int)(sizeof(dataX) / sizeof(dataX[0])); ++xIndex) {
//                double x = dataX[xIndex];
//                dataZ[yIndex * (int)(sizeof(dataX) / sizeof(dataX[0])) + xIndex] = x * sin(y) + y * sin(
//                    x);
//            }
//        }

        // Set the data to use to plot the chart
            c->setData(DoubleArray(dataY, (int)(sizeof(dataY) / sizeof(dataY[0]))), DoubleArray(dataX,
                (int)(sizeof(dataX) / sizeof(dataX[0]))), DoubleArray(dataZ, (int)(sizeof(dataZ) / sizeof(
                dataZ[0]))));



//-----------ВОТ ТАК Я ПРОБОВАЛ ВЫВЕСТИ ЗНАЧЕНИЯ ТВОИХ МАССИВОВ. В ПЕРВОМ СЛУЧАЕ НИ НА ЧТО НЕ РУГАЕТСЯ (ОН ДОЛЖЕН РАБОТАТЬ С КОРРЕКТНЫМИ ДАНЫМИ)----------

//            c->setData(DoubleArray(chd_x, (int)(sizeof(chd_x) / sizeof(chd_x[0]))), DoubleArray(chd_y,
//                (int)(sizeof(chd_y) / sizeof(chd_y[0]))), DoubleArray(chd_z, (int)(sizeof(chd_z) / sizeof(
//                chd_z[0]))));

            //c->setData( chd_x, chd_y, chd_z);




    // Set the elevation and rotation angles to 20 and 30 degrees
    c->setViewAngle(30, angle);
    // Spline interpolate data to a 80 x 80 grid for a smooth surface
    c->setInterpolation(80, 80);

   // c->setViewAngle(VertAngleValue,HorAngleValue);

    // Set surface grid lines to semi-transparent black (dd000000)
    //c->setSurfaceAxisGrid(0xdd000000);

    // Set contour lines to semi-transparent white (80ffffff)
    c->setContourColor(0x80ffffff);

    // Add a color axis (the legend) in which the left center is anchored at (645, 270). Set the
    // length to 200 pixels and the labels on the right side.
    c->setColorAxis(590, 270, Chart::Left, 200, Chart::Right)->setColorGradient();


    c->xAxis()->setTitle("Y", "arialbd.ttf", 10);
    c->yAxis()->setTitle("X", "arialbd.ttf", 10);
    c->zAxis()->setTitle("Conc", "arialbd.ttf", 10);

    ui->graphicsView->setChart(c);

    //free up resources
    delete c;

}

void MainWindow::on_pushButton_Concentration_clicked()
{
    createSurface();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->widget->clearGraphs();//Если нужно, то очищаем все графики
    ui->widget->addGraph();//Создаем график
    ui->widget->graph(0)->setPen(QColor(255, 0, 0));//задаем цвет точки
    ui->widget->xAxis->setLabel("x");//Задаем название осей грфику
    ui->widget->yAxis->setLabel("Concentration");//Задаем название осей грфику
    ui->widget->graph(0)->setData(CoordX, ConcentrationOnXAtStep[value]);//Что и от чего стрить для x(t)
    ui->widget->graph(0)->setName("Conc");
    ui->widget->legend->setVisible(1);
    ui->widget->rescaleAxes();
    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);//Для изменения Zoom графика
    ui->widget->replot();
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    angle = value;
    on_pushButton_Concentration_clicked();
}

void MainWindow::on_pushButton_GenStart_1000_clicked()
{
    CountOfSteps = ui->spinBox_MC_StepsCount->value();
    ui->horizontalSlider->setRange(0,CountOfSteps-1);

    ui->Scene_widget->GenStart1000();
    ui->Scene_widget->updateGL();

    step = 0;
    ConcentrationOnXAtStep.resize(CountOfSteps);
    for (int i =0; i <ConcentrationOnXAtStep.size(); i++)
    {
        ConcentrationOnXAtStep[i].resize(this->ui->Scene_widget->isPoint.size());
    }

    CoordX.resize(this->ui->Scene_widget->isPoint.size());

    for (int i =0; i <CoordX.size(); i++)
    {
        CoordX[i] =i;
    }
}

void MainWindow::on_pushButton_GenStart_Ogran_clicked()
{
    CountOfSteps = ui->spinBox_MC_StepsCount->value();
    ui->horizontalSlider->setRange(0,CountOfSteps-1);

    ui->Scene_widget->GenStartCenter();
    ui->Scene_widget->updateGL();

    step = 0;
    ConcentrationOnXAtStep.resize(CountOfSteps);
    for (int i =0; i <ConcentrationOnXAtStep.size(); i++)
    {
        ConcentrationOnXAtStep[i].resize(this->ui->Scene_widget->isPoint.size());
    }

    CoordX.resize(this->ui->Scene_widget->isPoint.size());

    for (int i =0; i <CoordX.size(); i++)
    {
        CoordX[i] =i;
    }
}
