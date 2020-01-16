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

void MainWindow::on_pushButton_clicked()
{

    this->ui->Scene_widget->point.clear();
    this->ui->Scene_widget->updateGL();

}

void MainWindow::on_pushButton_2_clicked()
{

    lyambda = ui->doubleSpinBox_lyambda->value();
    this->ui->Scene_widget->per = ui->doubleSpinBox_Per->value()*lyambda;
    this->ui->Scene_widget->CoordsNorm();
}

void MainWindow::on_pushButton_GenField_clicked()
{

    point1.resize(ui->Scene_widget->point.size());
    for (int i = 0; i<ui->Scene_widget->point.size(); i++)
    {
        point1[i].x = ui->Scene_widget->point[i].x;
        point1[i].y = ui->Scene_widget->point[i].y;
    }

    QVector<double> xaxis;
    xaxis.resize(0);
    for (int i = -R; i<=0; i++)
    {
        xaxis.push_back(i);
    }
    for (int i = 1; i<=R; i++)
    {
        xaxis.push_back(i);
    }


    c = new SurfaceChart(650, 500);


    ////////double dataX[xaxis.size()];
    for (int i = 0; i<xaxis.size(); i++)
    {
        dataX[i] = xaxis[i];
    }
    ///////double dataY[xaxis.size()];
    for (int i = 0; i<xaxis.size(); i++)
    {
        dataY[i] = xaxis[i];
    }

    // The values at the grid points. In this example, we will compute the values using the formula
    // z = x * sin(y) + y * sin(x).
    /////double dataZ[(int)(sizeof(dataX) / sizeof(dataX[0])) * (int)(sizeof(dataY) / sizeof(dataY[0]))];
    for (int i = 0; i<xaxis.size(); i++)
    {
        dataZ[i] = 0;
    }

    for(int yIndex = 0; yIndex < (int)(sizeof(dataY) / sizeof(dataY[0])); ++yIndex)
    {
        double y = dataY[yIndex];
        for(int xIndex = 0; xIndex < (int)(sizeof(dataX) / sizeof(dataX[0])); ++xIndex)
        {
            double x = dataX[xIndex];
            if (x*x + y*y <= R * R)
            {
                dataZ[yIndex * (int)(sizeof(dataX) / sizeof(dataX[0])) + xIndex] = sqrt(R*R - x*x - y*y);

                double z1 = dataZ[yIndex * (int)(sizeof(dataX) / sizeof(dataX[0])) + xIndex];
                double re = 0;
                double im = 0;
                for (int i = 0; i<point1.size(); i++)
                {
                    double r = sqrt((x-point1[i].x)*(x-point1[i].x) + (y-point1[i].y)*(y-point1[i].y) + z1*z1);
                    re += cos(2 * 3.14*r / lyambda) / r;
                    im += sin(2 * 3.14*r / lyambda) / r;
                }
                double I = sqrt(re*re + im*im);
                dataZ[yIndex * (int)(sizeof(dataX) / sizeof(dataX[0])) + xIndex] = I;

            }
            else dataZ[yIndex * (int)(sizeof(dataX) / sizeof(dataX[0])) + xIndex] = 0;

        }
    }

    qDebug()<<sizeof(dataZ)/sizeof(dataZ[0]);
    // Create a SurfaceChart object of size 720 x 600 pixels
    //SurfaceChart *c = new SurfaceChart(720, 600);

    // Add a title to the chart using 20 points Times New Roman Italic font
    c->addTitle("Directional diagram", "timesi.ttf", 20);


    // Set the center of the plot region at (350, 280), and set width x depth x height to 360 x 360
    // x 270 pixels
    c->setPlotRegion(310, 240, 360, 360, 210);

    // Set the data to use to plot the chart
    c->setData(DoubleArray(dataX, (int)(sizeof(dataX) / sizeof(dataX[0]))), DoubleArray(dataY,
                                                                                        (int)(sizeof(dataY) / sizeof(dataY[0]))), DoubleArray(dataZ, (int)(sizeof(dataZ) / sizeof(
                                                                                                                                                               dataZ[0]))));

    //c->setData( vectorToArray(xaxis), vectorToArray(xaxis),DoubleArray(dataZ, (int)(sizeof(dataZ) / sizeof(dataZ[0]))));

    // Spline interpolate data to a 80 x 80 grid for a smooth surface
    c->setInterpolation(80, 80);

    c->setViewAngle(VertAngleValue,HorAngleValue);

    // Set surface grid lines to semi-transparent black (dd000000)
    //c->setSurfaceAxisGrid(0xdd000000);

    // Set contour lines to semi-transparent white (80ffffff)
    c->setContourColor(0x80ffffff);

    // Add a color axis (the legend) in which the left center is anchored at (645, 270). Set the
    // length to 200 pixels and the labels on the right side.
    c->setColorAxis(590, 270, Chart::Left, 200, Chart::Right)->setColorGradient();

    // Set the x, y and z axis titles using 10 points Arial Bold font
    c->xAxis()->setTitle("X", "arialbd.ttf", 10);
    c->yAxis()->setTitle("Y", "arialbd.ttf", 10);
    c->zAxis()->setTitle("A", "arialbd.ttf", 10);

    ui->graphicsView->setChart(c);

    //free up resources
    delete c;

}

DoubleArray MainWindow::vectorToArray(std::vector<double>& v)
{
    return (v.size() == 0) ? DoubleArray() : DoubleArray(v.data(), (int)v.size());
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    HorAngleValue = value;
    c = new SurfaceChart(650, 500);
    c->addTitle("Directional diagram", "timesi.ttf", 20);
    // Set the center of the plot region at (350, 280), and set width x depth x height to 360 x 360
    // x 270 pixels
    c->setPlotRegion(310, 240, 360, 360, 210);
    // Set the data to use to plot the chart
    c->setData(DoubleArray(dataX, (int)(sizeof(dataX) / sizeof(dataX[0]))), DoubleArray(dataY,
                                                                                        (int)(sizeof(dataY) / sizeof(dataY[0]))), DoubleArray(dataZ, (int)(sizeof(dataZ) / sizeof(
                                                                                                                                                               dataZ[0]))));
    // Spline interpolate data to a 80 x 80 grid for a smooth surface
    c->setInterpolation(80, 80);
    c->setViewAngle(VertAngleValue,HorAngleValue);



    // Set contour lines to semi-transparent white (80ffffff)
    c->setContourColor(0x80ffffff);

    // Add a color axis (the legend) in which the left center is anchored at (645, 270). Set the
    // length to 200 pixels and the labels on the right side.
    c->setColorAxis(590, 270, Chart::Left, 200, Chart::Right)->setColorGradient();

    // Set the x, y and z axis titles using 10 points Arial Bold font
    c->xAxis()->setTitle("X", "arialbd.ttf", 10);
    c->yAxis()->setTitle("Y", "arialbd.ttf", 10);
    c->zAxis()->setTitle("A", "arialbd.ttf", 10);

    ui->graphicsView->setChart(c);

    //free up resources
    delete c;
}

void MainWindow::on_verticalSlider_valueChanged(int value)
{
    VertAngleValue = value;

    c = new SurfaceChart(650, 500);
    c->addTitle("Directional diagram", "timesi.ttf", 20);
    // Set the center of the plot region at (350, 280), and set width x depth x height to 360 x 360
    // x 270 pixels
    c->setPlotRegion(310, 240, 360, 360, 210);
    // Set the data to use to plot the chart
    c->setData(DoubleArray(dataX, (int)(sizeof(dataX) / sizeof(dataX[0]))), DoubleArray(dataY,
                                                                                        (int)(sizeof(dataY) / sizeof(dataY[0]))), DoubleArray(dataZ, (int)(sizeof(dataZ) / sizeof(
                                                                                                                                                               dataZ[0]))));
    // Spline interpolate data to a 80 x 80 grid for a smooth surface
    c->setInterpolation(80, 80);
    c->setViewAngle(VertAngleValue,HorAngleValue);


    // Set contour lines to semi-transparent white (80ffffff)
    c->setContourColor(0x80ffffff);

    // Add a color axis (the legend) in which the left center is anchored at (645, 270). Set the
    // length to 200 pixels and the labels on the right side.
    c->setColorAxis(590, 270, Chart::Left, 200, Chart::Right)->setColorGradient();

    // Set the x, y and z axis titles using 10 points Arial Bold font
    c->xAxis()->setTitle("X", "arialbd.ttf", 10);
    c->yAxis()->setTitle("Y", "arialbd.ttf", 10);
    c->zAxis()->setTitle("A", "arialbd.ttf", 10);

    ui->graphicsView->setChart(c);

    //free up resources
    delete c;
}
