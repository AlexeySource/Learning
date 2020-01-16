#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "glscene.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->horizontalSlider->setRange(0,this->ui->Scene_widget->frames-1);

    timer = new QTimer();
        connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_N_spinbox_valueChanged(int arg1)
{
    this->ui->Scene_widget->N = arg1;
}

void MainWindow::on_N_spinbox_2_valueChanged(int arg1)
{
    this->ui->Scene_widget->vmax = arg1;
}

void MainWindow::on_doubleSpinBox_valueChanged(double arg1)
{
    this->ui->Scene_widget->hdt = arg1;
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    this->ui->Scene_widget->SliderMean = value;
    ui->textEdit->setText(QString::number(value));
}

void MainWindow::slotTimerAlarm()
{

    ui->horizontalSlider->setValue(counter);

    ui->widget->graph(0)->addData(this->ui->Scene_widget->TimeForEnergy[counter], this->ui->Scene_widget->EnKin[counter]);
    ui->widget->rescaleAxes();
    ui->widget->replot();

    ui->widget_2->graph(0)->addData(this->ui->Scene_widget->TimeForEnergy[counter], this->ui->Scene_widget->EnPot[counter]);
    ui->widget_2->rescaleAxes();
    //ui->widget_2->yAxis->setRange(-0.02,0.01);

    ui->widget_2->replot();

    ui->widget_3->graph(0)->addData(this->ui->Scene_widget->TimeForEnergy[counter], this->ui->Scene_widget->EnFull[counter]);
    ui->widget_3->rescaleAxes();
    ui->widget_3->replot();

    counter=counter+20;
    if(counter>=this->ui->Scene_widget->frames)
    {
        timer->stop();
        counter = 0;
    }
}

void MainWindow::on_pushButton_Animation_clicked()
{
    ui->widget->clearGraphs();//Если нужно, то очищаем все графики
    ui->widget->addGraph();//Создаем   график
    ui->widget->graph(0)->setPen(QColor(0, 0, 255));//задаем цвет точки
    ui->widget->graph(0)->setName(tr("EnKin"));
    ui->widget->legend->setVisible(1);
    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);//Для изменения Zoom графика
    ui->widget_2->clearGraphs();//Если нужно, то очищаем все графики
    ui->widget_2->addGraph();//Создаем   график
    ui->widget_2->graph(0)->setPen(QColor(0, 0, 255));//задаем цвет точки
    ui->widget_2->graph(0)->setName(tr("EnPot"));
    ui->widget_2->legend->setVisible(1);
    ui->widget_2->yAxis->setRange(-0.02,0.005);
    ui->widget_2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);//Для изменения Zoom графика
    ui->widget_3->clearGraphs();//Если нужно, то очищаем все графики
    ui->widget_3->addGraph();//Создаем   график
    ui->widget_3->graph(0)->setPen(QColor(0, 0, 255));//задаем цвет точки
    ui->widget_3->graph(0)->setName(tr("EnFull"));
    ui->widget_3->legend->setVisible(1);
    ui->widget_3->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);//Для изменения Zoom графика

    ui->widget->graph(0)->addData(0,0);
    ui->widget_2->graph(0)->addData(0,0);
    ui->widget_3->graph(0)->addData(0,0);
    timer->start(2);


}

void MainWindow::on_pushButton_Animation_stop_clicked()
{
    timer->stop();
    counter = 0;

}

void MainWindow::on_N_spinbox_frames_count_valueChanged(int arg1)
{
    this->ui->Scene_widget->frames = arg1;
    ui->horizontalSlider->setRange(0,arg1-1);

}

void MainWindow::on_pushButton_4_clicked()
{
//    this->ui->Scene_widget->BoolTriangulation = true;
//    // glScene::updateGL();
//    this->ui->Scene_widget->updateGL();
    this->ui->Scene_widget->Maxvell();

    iter.resize(ui->Scene_widget->IntMass.size());
    for (int i = 0; i < ui->Scene_widget->IntMass.size(); i++)
    {
        iter[i] = this->ui->Scene_widget->IntMass[i];
    }

    Fi1.resize(ui->Scene_widget->Fi.size());
    ui->widget_2->clearGraphs();//Если нужно, то очищаем все графики
    ui->widget_2->addGraph();//Создаем   график
    ui->widget_2->addGraph();//Создаем   график
    ui->widget_2->graph(0)->setPen(QColor(255, 0, 255));//задаем цвет точки
    ui->widget_2->graph(1)->setPen(QColor(0, 0, 255));//задаем цвет точки
    ui->widget_2->xAxis->setLabel("t");//Задаем название осей грфику
    ui->widget_2->yAxis->setLabel("x");//Задаем название осей грфику

    ui->widget_2->graph(0)->setData(iter, this->ui->Scene_widget->nsr);//Что и от чего стрить для x(t)

    ui->widget_2->graph(1)->setData(this->ui->Scene_widget->vi, this->ui->Scene_widget->Fi);//Что и от чего стрить для x(t)
    ui->widget_2->graph(0)->setName("Практич.");
    ui->widget_2->graph(1)->setName("Теоретич.");
    ui->widget_2->legend->setVisible(1);
    ui->widget_2->rescaleAxes();
    ui->widget_2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);//Для изменения Zoom графика
    ui->widget_2->replot();

}

void MainWindow::on_pushButton_Save1_clicked()
{
    QFile file("1.txt");
    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);
        for (int i = 0; i<this->ui->Scene_widget->nsr.size(); i++)
        {
            out<<this->ui->Scene_widget->nsr[i]<<"\r\n";
        }
    }
    file.close();

    iter1.resize(iter.size());
    for (int i = 0; i < iter.size(); i++)
    {
        iter1[i] = iter[i];
    }
    v1 = ui->Scene_widget->vmax;
    T1 = ui->Scene_widget->T;

    qDebug()<<"V1 ="<<v1<<"T1 ="<<T1;;
}
void MainWindow::on_pushButton_Save2_clicked()
{
    QFile file2("2.txt");
    if(file2.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file2);
        for (int i = 0; i<this->ui->Scene_widget->nsr.size(); i++)
        {
            out<<this->ui->Scene_widget->nsr[i]<<"\r\n";
        }
    }
    file2.close();
    iter2.resize(iter.size());
    for (int i = 0; i < iter.size(); i++)
    {
        iter2[i] = iter[i];
    }
    v2 = ui->Scene_widget->vmax;
    T2 = ui->Scene_widget->T;
    qDebug()<<"V2 ="<<v2<<"T2 ="<<T2;
}

void MainWindow::on_pushButton_Save3_clicked()
{
    QFile file3("3.txt");
    if(file3.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file3);
        for (int i = 0; i<this->ui->Scene_widget->nsr.size(); i++)
        {
            out<<this->ui->Scene_widget->nsr[i]<<"\r\n";
        }
    }
    file3.close();
    iter3.resize(iter.size());
    for (int i = 0; i < iter.size(); i++)
    {
        iter3[i] = iter[i];
    }
    v3 = ui->Scene_widget->vmax;
    T3 = ui->Scene_widget->T;
    qDebug()<<"V3 ="<<v3<<"T3 ="<<T3;
}

void MainWindow::on_pushButton_Plot3Maxwell_clicked()
{
    QVector<double> mass1;
    QVector<double> mass2;
    QVector<double> mass3;

    mass1.resize(0);
    mass2.resize(0);
    mass3.resize(0);

    QFile file11("1.txt");
    if (file11.open(QIODevice::ReadOnly))
    {
        QString a;
        while(!file11.atEnd())
            {
            a = file11.readLine();
            mass1.push_back(a.trimmed().toDouble());
            }
            file11.close();
    }

    QFile file22("2.txt");
    if (file22.open(QIODevice::ReadOnly))
    {
        QString a2;
        while(!file22.atEnd())
            {
            a2 = file22.readLine();
            mass2.push_back(a2.trimmed().toDouble());
            }
            file22.close();
    }

    QFile file33("3.txt");
    if (file33.open(QIODevice::ReadOnly))
    {
        QString a3;
        while(!file33.atEnd())
            {
            a3 = file33.readLine();
            mass3.push_back(a3.trimmed().toDouble());
            }
            file33.close();
    }


    ui->widget_3->clearGraphs();//Если нужно, то очищаем все графики
    ui->widget_3->addGraph();//Создаем   график
    ui->widget_3->addGraph();//Создаем   график
    ui->widget_3->addGraph();//Создаем   график
    ui->widget_3->graph(0)->setPen(QColor(255, 0, 0));//задаем цвет точки
    ui->widget_3->graph(1)->setPen(QColor(10, 100, 255));//задаем цвет точки
    ui->widget_3->graph(2)->setPen(QColor(55, 0, 55));//задаем цвет точки
    ui->widget_3->xAxis->setLabel("i");//Задаем название осей грфику
    ui->widget_3->yAxis->setLabel("n");//Задаем название осей грфику
    ui->widget_3->graph(0)->setData(iter1, mass1);//Что и от чего стрить для x(t)
    ui->widget_3->graph(1)->setData(iter2, mass2);//Что и от чего стрить для x(t)
    ui->widget_3->graph(2)->setData(iter3, mass3);//Что и от чего стрить для x(t)
    ui->widget_3->graph(0)->setName("vmax = " + (QString::number(v1)) + "  T = " + (QString::number(T1)));
    ui->widget_3->graph(1)->setName("vmax = " + (QString::number(v2)) + "  T = " + (QString::number(T2)));
    ui->widget_3->graph(2)->setName("vmax = " + (QString::number(v3)) + "  T = " + (QString::number(T3)));
    ui->widget_3->legend->setVisible(1);
    ui->widget_3->rescaleAxes();
    ui->widget_3->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);//Для изменения Zoom графика
    ui->widget_3->replot();

}

