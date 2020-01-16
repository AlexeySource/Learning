#include "glscene.h"
#include "cmath"

glScene::glScene(QWidget *parent)
    : QGLWidget(parent)
{

}


void glScene::initializeGL()
{
     glMatrixMode(GL_PROJECTION); // установка режима матрицы
     glLoadIdentity(); // загрузка матрицы
     //qglClearColor(Qt::white); // заполняем экран белым цветом
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // заполняем экран белым цветом


}


void glScene::paintGL()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очистка экрана

glColor3f(0.7,0.7,0.7);
DrawGrid(D);
DrawPoints();


}

void glScene::resizeGL(int weight, int high)
{
    qDebug()<<"w,h"<<weight<<high;
    glViewport(0,0,weight,high); // установка точки обзора
    //glOrtho(0.0f, weight, high, 0.0f, 0.0f, 1.0f);
    glOrtho(0.0f, w1, w1, 0.0f, 0.0f, 1.0f);
    // glOrtho(0.0f-100, weight+100, high+100, 0.0f-100, 0.0f, 1.0f); // расширенная область

}

void glScene::DrawGrid(double h)
{
glColor3f(0.7,0.7,0.7);
    glBegin(GL_LINES);
    for (int i = 0; i<w1; i+=h)
    {
        glVertex2f(i,0); glVertex2f(i,w1);
    }
    for (int i = 0; i<w1; i+=h)
    {
        glVertex2f(0,i); glVertex2f(w1,i);
    }
    glEnd();

glColor3f(0.8, 0.8, 0.8);


}

void glScene::DrawPoints()
{
    glColor3f(0.1,0.1,0.1);
    for (int i = 0; i<point.size(); i++)
    {
        drawCircle(point[i].x,point[i].y,D*0.2,15);
    }
}

void glScene::CoordsNorm()
{
    for (int i = 0; i<point.size(); i++)
    {

        point[i].x -= N*D/2;
        point[i].y -= N*D/2;
        qDebug()<<"coords00"<<point[i].x<<point[i].y;
    }

    for (int i = 0; i<point.size(); i++)
    {

        point[i].x *= per;
        point[i].y *= per;
        qDebug()<<"coords after calc"<<point[i].x<<point[i].y;
    }
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

void glScene::mousePressEvent(QMouseEvent *me)
{
    if(me->button()==Qt::LeftButton)
    {
        coords x1;
        qDebug()<<"click"<<me->x()/int(300/N)<<me->y()/int(300/N);
        qDebug()<< (me->x())/int(300/N) *int(300/N) +int(300/N)/2 << (me->y())/int(300/N) * int(300/N) + int(300/N)/2;
        x1.x = (me->x())/int(300/N) *D +D/2 ;
        x1.y = (me->y())/int(300/N) * D + D/2;
        point.push_back(x1);
        updateGL();

    }
}


