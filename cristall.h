#ifndef CRISTALL_H
#define CRISTALL_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QLineEdit>
#include "menu.h"
#include "frame.h"
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QMenuBar>
#include <QMenu>

class Cristall : public QFrame
{
    Q_OBJECT

public:
    Cristall(QWidget *parent = nullptr);
    ~Cristall();

private slots:


    void slotAddPolygons();
    void slotAddPoints();
    void slotUploadFiles();
    void slotExit();
    void slotChangeAngle();
    void on_goStepX_clicked();
    void on_goStepY_clicked();
    void on_goStepZ_clicked();
    void on_goScaleX_clicked();
    void on_goScaleY_clicked();
    void on_goScaleZ_clicked();
    void on_goMove_clicked();
    void on_goReflectX_clicked();
    void on_goReflectY_clicked();
    void on_goReflectZ_clicked();
private:
   // void createAngleGrid(QGridLayout* );
   // void createPathGrid(QGridLayout* );
   // void createScaleGrid(QGridLayout*);
    Frame* canvas;
    Menu* menu;
    QString pathPolygon;
    QString pathPoints;
    QLineEdit *polLine;
    QLineEdit * pointLine;
    QLineEdit *lineAngleX;
    QLineEdit *lineAngleY;
    QLineEdit *lineAngleZ;
    QLineEdit *lineScaleX;
    QLineEdit *lineScaleY;
    QLineEdit *lineScaleZ;
    QLineEdit *lineMoveX;
    QLineEdit *lineMoveY;
    QLineEdit *lineMoveZ;

};
#endif // CRISTALL_H
