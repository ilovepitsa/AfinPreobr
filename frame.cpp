#include "frame.h"

Frame::Frame(QWidget *parent)
    : QFrame{parent}
{

    parent_w=parent;
   setStyleSheet("background-color:white;");
}

bool Frame::upload(QString initPathPolygons, QString initPathPoints)
{
    pathPolygons=initPathPolygons;
    pathPoints=initPathPoints;
    bool resFillPol=fillingDataPolygons();
    bool resFillPoint=fillingDataPoints();
    repaint();
    if(resFillPoint && resFillPol) return true;
    return false;
}

void Frame::drawFigure(QPainter* qp)
{

    for(int i=0;i<dataPolygons.size();i++)
    {
        QPointF points[dataPolygons[i].size()];
        for(int j=0;j<dataPolygons[i].size();j++)
        {
            points[j]=QPointF(dataPoints[dataPolygons[i][j]].x + 250, dataPoints[dataPolygons[i][j]].y+250);

        }
        qp->drawPolygon(points,dataPolygons[i].size());
    }
}

void Frame::rotateX()
{
    QMatrix4x4 R
            (1,0,0,0,
             0,cos(FiX),sin(FiX),0,
             0,-sin(FiX),cos(FiX),0,
             0,0,0,1
             );
    calculate(R);
    repaint();
}

void Frame::rotateY()
{
    QMatrix4x4 R
            (cos(FiY),0,-sin(FiY),0,
             0,1,0,0,
             sin(FiY),0,cos(FiY),0,
             0,0,0,1
             );
    calculate(R);
    repaint();
}

void Frame::rotateZ(QString dir)
{
    if(dir=="Left")
    {
        FiZ=abs(FiZ);
    }
    else
        if(FiZ>0) FiZ=-FiZ;
    QMatrix4x4 R
            (cos(FiZ),sin(FiZ),0,0,
             -sin(FiZ),cos(FiZ),0,0,
             0,0,1,0,
             0,0,0,1
             );
    calculate(R);
    repaint();
}

void Frame::scaleX(double val)
{
    QMatrix4x4 R
            (val,0,0,0,
             0,1,0,0,
             0,0,1,0,
             0,0,0,1);
    calculate(R);
    repaint();

}

void Frame::scaleY(double val)
{
    QMatrix4x4 R
            (1,0,0,0,
             0,val,0,0,
             0,0,1,0,
             0,0,0,1);
    calculate(R);
    repaint();
}

void Frame::scaleZ(double val)
{
    QMatrix4x4 R
            (1,0,0,0,
             0,1,0,0,
             0,0,val,0,
             0,0,0,1);
    calculate(R);
    repaint();
}

void Frame::moveToCoord(double x, double y, double z)
{
    QMatrix4x4 R
            (1,0,0,x,
             0,1,0,y,
             0,0,1,z,
             0,0,0,1);
    calculate(R);
    repaint();
}

void Frame::reflectX()
{
    QMatrix4x4 R
            (1,0,0,0,
             0,-1,0,0,
             0,0,1,0,
             0,0,0,1);
    calculate(R);
    repaint();
}

void Frame::reflectY()
{
    QMatrix4x4 R
            (-1,0,0,0,
             0,1,0,0,
             0,0,1,0,
             0,0,0,1);
    calculate(R);
    repaint();
}

void Frame::reflectZ()
{
    QMatrix4x4 R
            (1,0,0,0,
             0,1,0,0,
             0,0,-1,0,
             0,0,0,1);
    calculate(R);
    repaint();
}

void Frame::paintEvent(QPaintEvent *e)
{
    //Q_UNUSED(e);

    QPainter painter(this);
    QPen pen(Qt::black,1,Qt::DashLine,Qt::SquareCap,Qt::RoundJoin);
    painter.setPen(pen);
    drawFigure(&painter);
    QFrame::paintEvent(e);
}

void Frame::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        _p=event->pos();
        rotationX=_p.x()-250;
        rotationY=_p.y()-250;
    }
}

void Frame::mouseMoveEvent(QMouseEvent *e)
{
    if(!_p.isNull())
    {
        if(abs(rotationX - (e->position().x()-250))>5 && abs(rotationY-(e->position().y()-250))>5)
        {
            if(rotationX>(e->position().x()-250))
            {
                if(rotationY>(e->position().y()-250))
                {
                    FiX=abs(FiX);
                    rotateX();
                    if(FiY>0) FiY=-FiY;
                    rotateY();
                }
                else
                {
                    if(FiX>0) FiX=-FiX;
                    rotateX();
                    if(FiY>0) FiY=-FiY;
                    rotateY();
                }
            }
            else
            {
                if(rotationY>(e->position().y()-250))
                {
                    FiX=abs(FiX);
                    rotateX();
                    FiY=abs(FiY);
                    rotateY();
                }
                else
                {
                    if(FiX>0) FiX=-FiX;
                    rotateX();
                    FiY=abs(FiY);
                    rotateY();
                }

            }
            rotationX=e->position().x()-250;
            rotationY=e->position().y()-250;
        }
    }
}

void Frame::wheelEvent(QWheelEvent *event)
{
    if(event->angleDelta().y()>0)
    {
        rotateZLeft();
    }
    else
        rotateZRight();
}

bool Frame::fillingDataPolygons()
{
    dataPolygons.clear();
    QFile file(pathPolygons);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this," П", "Файл "+pathPolygons+" не найдет");
        return false;
    }
    while(!file.atEnd())
    {
        QStringList list;
        QString tmpStr= file.readLine();
        list=tmpStr.split(QRegularExpression(" "));
        QVector<int> tmpVec;
        for(int i=1;i<=list.at(0).toInt();i++)
        {
            tmpVec.push_back(list.at(i).toInt()-1);
        }
        dataPolygons.push_back(tmpVec);
    }
    file.close();
    return true;
}

bool Frame::fillingDataPoints()
{
    dataPoints.clear();
    QFile file(pathPoints);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this," П", "Файл "+pathPoints+" не найдет");
        return false;
    }
    while(!file.atEnd())
    {
        QStringList list;
        QString tmpStr= file.readLine();
        list=tmpStr.split(QRegularExpression(" "));
        dataPoints.push_back({100*list.at(0).toFloat(),100*list.at(1).toFloat(),100*list.at(2).toFloat()});
    }
    file.close();
    return true;
}

void Frame::rotateZLeft()
{
    rotateZ("Left");
}

void Frame::rotateZRight()
{
    rotateZ("Right");
}

void Frame::calculate(QMatrix4x4 &R)
{
    for(int i=0;i<dataPoints.size();i++)
    {
        QVector4D vectCoord(dataPoints[i].x,dataPoints[i].y,dataPoints[i].z,1);
        QVector4D result = R*vectCoord;
        dataPoints[i].x=result[0];
        dataPoints[i].y=result[1];
        dataPoints[i].z=result[2];
    }
}
