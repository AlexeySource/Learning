#include "glscene.h"
//#include <GL/glut.h>
#include <cmath>


glScene::glScene(QWidget *parent)
    : QGLWidget(parent)
{

}

void glScene::drawCircle(double x, double y, double r, int amountSegments)
{

 glBegin(GL_LINE_LOOP);
 for(int i = 0; i < amountSegments; i++)
 {
  double angle = 2.0 * 3.1415926 * double(i) / double(amountSegments);

  double dx = r * cosf(angle);
  double dy = r * sinf(angle);

  glVertex2f(x + dx, y + dy);
}
 glEnd();

}

double glScene::Rasst(double coord1, double coord2)
{
    double res = coord1 - coord2;
    if (fabs(res) > 15*a)
    {
        res = res -  Sign(res)*30*a;
    }
    return res;
}


double glScene::Rasst1(double coord1, double coord2)
{
    double res = coord1 - coord2;

    if (fabs(res) > 15*a)
    {
        res = res - Sign(res)*30*a;
    }
    return double(res);
}

void glScene::Triangulation()
{

    dt = hdt *tau;
    qDebug()<<"--------------------------------------"<<N<<frames;
    coords X1;
    point.clear();
    point.squeeze();
    point.resize(0);
    point2.clear();
    point2.squeeze();
    point2.resize(frames);    
    point2[0].resize(0);

    VSredn.resize(frames);
    EnPot.clear();
    EnPot.squeeze();
    EnPot.resize(frames);
    EnKin.clear();
    EnKin.squeeze();
    EnKin.resize(frames);
    EnFull.resize(frames);
    TimeForEnergy.resize(frames);

    VModVKv.resize(frames);
    for (int i = 0; i<frames; i++)
    {
        VModVKv[i].resize(N);
    }

    EnPotChast.resize(frames);
    for (int i = 0; i<frames; i++)
    {
        EnPotChast[i].resize(N);
    }

    for (int t = 0; t<frames; t++)
    {
        EnKin[t]=0;
        EnPot[t]=0;
        EnFull[t]=0;
    }

    srand(time(NULL));

    X1.x = (double)rand()/RAND_MAX*29.5*a;
    X1.y = (double)rand()/RAND_MAX*29.5*a;
    X1.vx = (-1 + (2*(double)rand()/RAND_MAX*1))*vmax;
    X1.vy = (-1 + (2*(double)rand()/RAND_MAX*1))*vmax;
    X1.Fx = 0;
    X1.Fy = 0;
    X1.Ep = 0;
    X1.Ek = m*(X1.vx*X1.vx + X1.vy*X1.vy)/2;
    X1.v = sqrt(X1.vx*X1.vx + X1.vy*X1.vy);

    point.push_back(X1);
    point2[0].push_back(X1);

    while (point.size()<N)
    {
        X1.x= (double)rand()/RAND_MAX*29.5*a;
        X1.y= (double)rand()/RAND_MAX*29.5*a;
        X1.vx = (-1 + (2*(double)rand()/RAND_MAX*1))*vmax;
        X1.vy = (-1 + (2*(double)rand()/RAND_MAX*1))*vmax;
        X1.Fx = 0;
        X1.Fy = 0;
        X1.Ep = 0;
        X1.Ek = m*(X1.vx*X1.vx + X1.vy*X1.vy)/2;
        X1.v = sqrt(X1.vx*X1.vx + X1.vy*X1.vy);
        bool rast = true;

        for (int i = 0; i < point.size(); i++)
        {
            if (sqrt((X1.x-point[i].x)*(X1.x-point[i].x) + (X1.y-point[i].y)*(X1.y-point[i].y))<(0.9*a))
            {
                rast = false;
                break;
            }
        }

        if (rast == true)
        {
            point.push_back(X1);
            point2[0].push_back(X1);

        }
    }


    glEnable(GL_BLEND);
    glEnable(GL_POINT_SMOOTH);
    glColor3d(1,0,0);
    for (int i = 0; i < point.size(); i++)
     {
        point2[0][i].index = i;
        drawCircle(point2[0][i].x, point2[0][i].y, 0.45*a, 30);
        //qDebug()<<sqrt(point2[0][i].vx*point2[0][i].vx + point2[0][i].vy*point2[0][i].vy);
     }

    glDisable(GL_POINT_SMOOTH);

    qDebug()<<point2.size()<<point2[0].size();

    coords zap{0,0,0,0,0,0,0,0,0};

    for (int t = 1; t<frames; t++)
    {
        point2[t].resize(0);
        while (point2[t].size()<N)
        {
            point2[t].push_back(zap);
        }
    }

    qDebug()<<"dt"<<dt;
    BoolTriangulation = false;

}

double glScene::K(double r)
{
    double res;
    double r1= 1.1*a;
    double r2= 1.7*a;
    if (r <= r1)
    {
        res = 1;
    }
    if (r >= r1 && r <= r2)
    {
        res = (1 - pow(((r-r1)/(r1-r2))*((r-r1)/(r1-r2)),2));
    }
    if (r>=r2)
    {
        res = 0;
    }
    return res;
}



void glScene::verle()
{
   double a6 = pow(a, 6.0);

   for (int t = 0; t < frames ; t++)
   {
        for (int i = 0; i < N; i++)
        {


            point[i].x += point[i].vx*dt + (point[i].Fx/(2*m))*dt*dt;
            point[i].y += point[i].vy*dt + (point[i].Fy/(2*m))*dt*dt;

            if (point[i].x > 30*a)    point[i].x -= 30*a;
            if (point[i].x < 0)       point[i].x += 30*a;

            if (point[i].y > 30*a)      point[i].y -= 30*a;
            if (point[i].y < 0)         point[i].y += 30*a;

            double preFx = point[i].Fx;
            double preFy = point[i].Fy;

            point[i].Fx = 0;
            point[i].Fy = 0;
            point[i].Ep = 0;
            point[i].Ek = 0;

            for (int k = 0; k < N; k++)
            {
                if (k==i) continue;

                double r = sqrt(pow(Rasst(point[i].x,point[k].x),2)+pow(Rasst(point[i].y,point[k].y),2));

                double kf = K(r);
                if(kf == 0) continue;

                point[i].Fx += 12*D*a6 * (a6 / pow(r,6) - 1.) * Rasst(point[i].x, point[k].x) / pow(r,8) * kf;
                point[i].Fy += 12*D*a6 * (a6 / pow(r,6) - 1.) * Rasst(point[i].y, point[k].y) / pow(r,8) * kf;
//                r = a/r;
//                point[i].Ep += D*(pow(r,12) - 2*pow(r,6));
                point[i].Ep += 4*D*(pow((sigma/r),12) - pow((sigma/r),6))*kf;

            }

            point[i].vx += ((point[i].Fx + preFx)/(2*m))*dt;
            point[i].vy += ((point[i].Fy + preFy)/(2*m))*dt;
            point[i].v = sqrt(point[i].vx*point[i].vx + point[i].vy*point[i].vy);
        }

        for(int i(0); i < N; i++)
        {
            //point[i].Ek += m*(pow(point[i].vx,2) + pow(point[i].vy,2))/2;
            point[i].Ek += m*point[i].v*point[i].v/2;
        }
        point2[t] = point;
    }

    for (int t = 0; t < frames; t++)
    {
        for (int i = 0; i < N; i++)
        {
           EnKin[t] += point2[t][i].Ek/N*1.6*1.e19;
           EnPot[t] += point2[t][i].Ep/N*1.6*1.e19;
           EnFull[t] = EnKin[t] + EnPot[t];
        }
    }


    for (int i = 0; i < frames; i++)
    {
        TimeForEnergy[i]=i;
    }

    for (int i = 0; i < point.size(); i++)
     {
        drawCircle(point2[0][i].x, point2[0][i].y, 0.45*a, 30);
     }

    T=0;
    for (int i = 0; i < frames; i++)
    {
       T += EnKin[i]/frames/N/1.6/1.e19/(1.38*1.e-23);
    }
    qDebug()<<"T"<<T;
    BoolVerle = false;
}


void glScene::DrawSlider()
{
    for (int i = 0; i < point.size(); i++)
     {

        drawCircle(point2[SliderMean][i].x, point2[SliderMean][i].y, 0.45*a, 30);

     }
    BoolSlider = false;
}


void glScene::Maxvell()
{
    qDebug()<<"---Maxvell---";
    double vmax1 = 0;
    double tmp = 0;
    int TimeForV = 1000;
    for (int t = 0; t < TimeForV; t++)
    {
        for (int i = 0; i < N; i++)
        {
           // tmp = sqrt(point2[t][i].vx*point2[t][i].vx + point2[t][i].vy*point2[t][i].vy);
            tmp = point2[t][i].v;
            if (tmp > vmax1) vmax1 = tmp;
        }
    }
    qDebug()<<"Vmax: "<<vmax1;

    double hInt = 2*vmax1/50;

//    QVector<double> IntMass;
    IntMass.resize(0);
    for (double i = 0; i <= 50; i ++)
    {
        IntMass.push_back(i*hInt);
    }


    vi.resize(IntMass.size());
    for (int i = 0; i < vi.size(); i++)
    {
        vi[i] = i*hInt + hInt/2;
    }

    Fi.resize(vi.size());
    for (int i = 0; i < Fi.size(); i++)
    {
        Fi[i] = 0.16*2*vi[i]/vmax*exp(-vi[i]*vi[i]/vmax/vmax);
    }

//    QVector<QVector<double>> n;         //n(50,0);
    n.resize(frames - TimeForV);
    for (int i = 0; i < n.size(); i++)
    {
        n[i].resize(50);
    }
    for (int i = 0; i < n.size(); i++)
    {
        for (int k = 0; k < n[0].size(); k++)
        {
            n[i][k] = 0;
        }
    }

    for (int t = TimeForV; t < frames; t++)
    {
        for (int i = 0; i < N; i++)
        {
            for (int v = 1; v < 52; v++)
            {
                //double pv = sqrt(point2[t][i].vx*point2[t][i].vx + point2[t][i].vy*point2[t][i].vy);
                if (/*pv*/point2[t][i].v >=IntMass[v-1] && /*pv*/point2[t][i].v<=IntMass[v+1]) n[t-TimeForV][v]++;
            }
        }
    }

    nsr.resize(50);
    for (int i = 0; i < nsr.size(); i++)
    {
        nsr[i] = 0;
    }

    for (int t = 0; t < n.size(); t++)
    {
        for (int i = 0; i < n[0].size(); i++)
        {
            nsr[i]+=n[t][i]/n.size()/N;
        }
    }




}






void glScene::initializeGL()
{
    glMatrixMode(GL_PROJECTION); // установка режима матрицы
    glLoadIdentity(); // загрузка матрицы
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // заполняем экран белым цветом
}

void glScene::paintGL()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очистка экрана

if(BoolTriangulation == true) Triangulation();
if(BoolVerle == true) verle();
if(BoolSlider == true) DrawSlider();

}

void glScene::resizeGL(int weight, int high)
{
    qDebug()<<"w,h"<<weight<<high;
    glViewport(0,0,weight,high); // установка точки обзора
    glOrtho(0.0f, 30*a, 30*a, 0.0f, 0.0f, 1.0f);
    h1 = high;
    w1 = weight;
}

void glScene::slot_VerleButton()
{

    BoolVerle = true;
    updateGL();
}

void glScene::slot_Slider()
{
    BoolSlider = true;
    updateGL();
}

void glScene::slot_TriangulationButton()
{
    BoolTriangulation = true;
    updateGL();
}

void glScene::slot_CountOfPoints()
{

}
