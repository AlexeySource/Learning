#include "glscene.h"
#include "cmath"

glScene::glScene(QWidget *parent)
    : QGLWidget(parent)
{

}


void glScene::initializeGL()
{
     glMatrixMode(GL_PROJECTION); // СѓСЃС‚Р°РЅРѕРІРєР° СЂРµР¶РёРјР° РјР°С‚СЂРёС†С‹
     glLoadIdentity(); // Р·Р°РіСЂСѓР·РєР° РјР°С‚СЂРёС†С‹
     //qglClearColor(Qt::white); // Р·Р°РїРѕР»РЅСЏРµРј СЌРєСЂР°РЅ Р±РµР»С‹Рј С†РІРµС‚РѕРј
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Р·Р°РїРѕР»РЅСЏРµРј СЌРєСЂР°РЅ Р±РµР»С‹Рј С†РІРµС‚РѕРј


}


void glScene::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // РѕС‡РёСЃС‚РєР° СЌРєСЂР°РЅР°
    DrawGrid(D);
    if(bStart == true)    DrawPoints();


}

void glScene::resizeGL(int weight, int high)
{
    qDebug()<<"w,h"<<weight<<high;

    glViewport(0,0,weight,high); // СѓСЃС‚Р°РЅРѕРІРєР° С‚РѕС‡РєРё РѕР±Р·РѕСЂР°
    //glOrtho(0.0f, weight, high, 0.0f, 0.0f, 1.0f);
    glOrtho(0.0f, w1, 0.0f, h1, 0.0f, 1.0f);
    // glOrtho(0.0f-100, weight+100, high+100, 0.0f-100, 0.0f, 1.0f); // СЂР°СЃС€РёСЂРµРЅРЅР°СЏ РѕР±Р»Р°СЃС‚СЊ

}

void glScene::DrawGrid(double hGrid)
{

    glColor3f(0.75,0.75,0.75);
        glBegin(GL_LINES);
        for (int i = 0; i<w1; i+=hGrid)
        {
            glVertex2f(i,0); glVertex2f(i,w1);
        }
        for (int i = 0; i<h1; i+=hGrid)
        {
            glVertex2f(0,i); glVertex2f(w1,i);
        }
        glEnd();


}

void glScene::DrawPoints()
{


    glEnable(GL_POINT_SMOOTH);
    glPointSize(4);
       glBegin(GL_POINTS);
       glColor3f(0.1, 0.1, 0.1);

       for (int i = 0; i<point.size(); i++)  /////50
       {
           glVertex2f(point[i].x,point[i].y);
       }
       glEnd();
}



void glScene::GenStart()
{

    point.clear();
    point.squeeze();
    point.resize(0);
    isPoint.resize(w1+1);
    for (int i =0; i <isPoint.size(); i++)
    {
        isPoint[i].resize(h1+1);
    }

    int y =0;
    for (int i =0; i <isPoint.size(); i++)
    {
        for (int j =0; j <isPoint[0].size(); j++)
        {
            isPoint[i][j] = 0;
            y++;
        }
    }
    qDebug()<<"size"<<isPoint.size()<<isPoint[0].size()<<isPoint[0][20]<<y;



    coords x;
    for (int i =0; i <isPoint[0].size(); i++)
    {
        x.x = 0;
        x.y = i;
        point.push_back(x);
        isPoint[0][i] = true;
    }

//    for (int i =34; i <66; i++)
//    {
//        x.x = 0;
//        x.y = i;
//        point.push_back(x);
//        isPoint[0][i] = true;
//    }


   // qDebug()<<isPointint.size()<<isPointint[0].size();
    //qDebug()<<isPointint[0][0];

    ConcentrationOnX.resize(isPoint.size());

    bStart = true;
}


void glScene::GenStart1000()
{

    point.clear();
    point.squeeze();
    point.resize(0);
    isPoint.resize(w1+1);
    for (int i =0; i <isPoint.size(); i++)
    {
        isPoint[i].resize(1000+1);
    }

    int y =0;
    for (int i =0; i <isPoint.size(); i++)
    {
        for (int j =0; j <isPoint[0].size(); j++)
        {
            isPoint[i][j] = 0;
            y++;
        }
    }
    qDebug()<<"size"<<isPoint.size()<<isPoint[0].size()<<isPoint[0][20]<<y;

    coords x;
    for (int i =0; i <isPoint[0].size(); i++)
    {
        x.x = 0;
        x.y = i;
        point.push_back(x);
        isPoint[0][i] = true;
    }

    ConcentrationOnX.resize(isPoint.size());
    bStart = true;
}

void glScene::GenStartCenter()
{

    point.clear();
    point.squeeze();
    point.resize(0);
    isPoint.resize(w1+1);
    for (int i =0; i <isPoint.size(); i++)
    {
        isPoint[i].resize(h1+1);
    }

    int y =0;
    for (int i =0; i <isPoint.size(); i++)
    {
        for (int j =0; j <isPoint[0].size(); j++)
        {
            isPoint[i][j] = 0;
            y++;
        }
    }
    qDebug()<<"size"<<isPoint.size()<<isPoint[0].size()<<isPoint[0][20]<<y;

    coords x;
    for (int i =0; i <isPoint[0].size(); i++)
    {
        x.x = 98;
        x.y = i;
        point.push_back(x);
        isPoint[0][i] = true;
    }
    for (int i =0; i <isPoint[0].size(); i++)
    {
        x.x = 99;
        x.y = i;
        point.push_back(x);
        isPoint[0][i] = true;
    }
    for (int i =0; i <isPoint[0].size(); i++)
    {
        x.x = 100;
        x.y = i;
        point.push_back(x);
        isPoint[0][i] = true;
    }
    for (int i =0; i <isPoint[0].size(); i++)
    {
        x.x = 101;
        x.y = i;
        point.push_back(x);
        isPoint[0][i] = true;
    }
    for (int i =0; i <isPoint[0].size(); i++)
    {
        x.x = 102;
        x.y = i;
        point.push_back(x);
        isPoint[0][i] = true;
    }

    ConcentrationOnX.resize(isPoint.size());
    bStart = true;
}

void glScene::InfinitySource()
{
    coords x1;
    for (int j =0; j <isPoint[0].size(); j++)
    {
        if (!isPoint[0][j])
        {
            x1.x = 0;
            x1.y = j;
            point.push_back(x1);
            isPoint[0][j] = true;
        }
    }
}

void glScene::Diffuzia()
{

    //coords x1;
    int size = point.size();
    qDebug()<<size;
    for (int i =0; i < size; i++)
    {
        MovePoint(point[i]);
        InfinitySource();
//        for (int j =0; j <isPoint[0].size(); j++)
//        {
//            if (!isPoint[0][j])
//            {
//                x1.x = 0;
//                x1.y = j;
//                point.push_back(x1);
//                isPoint[0][j] = true;
//            }
//        }
    }

    counter = 0;

    for (int i =0; i < isPoint.size(); i++)
    {
        for (int j =0; j < isPoint[0].size(); j++)
        {
            if (isPoint[i][j])
            {
                counter++;
            }
        }

        //логарифмический масштаб
//        if(counter!=0)
//        {
//           ConcentrationOnX[i] = log10(counter/isPoint[0].size());
//        }

        //линейный масштаб
        ConcentrationOnX[i] = (counter/isPoint[0].size());
//        ConcentrationOnX[0] = ((66-34)/isPoint[0].size());

        counter = 0;
    }
    //qDebug()<<ConcentrationOnX;
}



void glScene::Movefor()
{

}

void glScene::mousePressEvent(QMouseEvent *me)
{
    if(me->button()==Qt::LeftButton)
    {

        qDebug()<<"click"<<me->x()<<me->y();

    }
}

void glScene::MovePoint(coords &point)
{
    int a = 1 + rand() % 4;
    switch (a)
    {
    case 1:

        if (point.y == 100 && isPoint[point.x][0] == false)
        {
            isPoint[point.x][point.y]=false;
            point.y = 0;
            isPoint[point.x][point.y]=true;
        }
        else if (point.y != 100 && isPoint[point.x][point.y +1] == false)
        {
            isPoint[point.x][point.y]=false;
            point.y = point.y +1;
            isPoint[point.x][point.y]=true;
        }
         break;
    case 2:
        if (isPoint[point.x+1][point.y]==false)
        {
            isPoint[point.x][point.y]=false;
            point.x = point.x +1;
            isPoint[point.x][point.y]=true;
        }
        break;
    case 3:


        if (point.y == 0 && isPoint[point.x][100]==false)
        {
            isPoint[point.x][point.y]=false;
            point.y = 100;
            isPoint[point.x][point.y]=true;
        }
        else if (point.y != 0 && isPoint[point.x][point.y -1]==false)
        {
            isPoint[point.x][point.y]=false;
            point.y = point.y - 1;
            isPoint[point.x][point.y]=true;
        }
        break;
    case 4:
        if (point.x>1 && isPoint[point.x-1][point.y]==false)
        {
            isPoint[point.x][point.y]=false;
            point.x = point.x -1;
            isPoint[point.x][point.y]=true;
        }
        break;
    }
}
