#ifndef FRAME_H
#define FRAME_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QMatrix4x4>
#include <QMessageBox>
#include <QFile>
#include <QFrame>
#include <QtMath>
#include <QWheelEvent>
#include <QRegularExpression>
#include <QDebug>
#include <QtGui>

class Frame : public QFrame
{
    Q_OBJECT
public:
    explicit Frame(QWidget *parent = nullptr);
    QWidget *parent_w;
    bool upload(QString, QString);

    void setFiX(double initFiX){FiX = initFiX * M_PI / 180;};
    void setFiY(double initFiY){FiY = initFiY * M_PI / 180;};
    void setFiZ(double initFiZ){FiZ = initFiZ * M_PI / 180;};
    // Rotation
    void rotateX();
    void rotateY();
    void rotateZ(QString);
    // Scale
    void scaleX(double);
    void scaleY(double);
    void scaleZ(double);
    // Move
    void moveToCoord(double, double, double);
    // Reflect
    void reflectX();
    void reflectY();
    void reflectZ();

protected:
    virtual void paintEvent(QPaintEvent *) override;
    void drawFigure(QPainter *qp);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    double FiX = 0.07;
    double FiY = 0.07;
    double FiZ = 0.07;
    QString pathPolygons;
    QString pathPoints;
    //QPainter painter;
    QPoint _p;
    int rotationX;
    int rotationY;
    struct coord{
    float x, y, z;
    };

    QVector<QVector<int>> dataPolygons;
    QVector<coord> dataPoints;
    /* --------- Functions --------- */
    bool fillingDataPolygons();
    bool fillingDataPoints();
    void rotateZLeft();
    void rotateZRight();
    void calculate(QMatrix4x4 &);
signals:

};

#endif // FRAME_H
