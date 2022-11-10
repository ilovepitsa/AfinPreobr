#include "cristall.h"


Cristall::Cristall(QWidget *parent)
    : QFrame(parent)
{
    // QAction* q=new QAction("&Выход",this);
    // QAction* open=new QAction("&Открыть",this);
    //QFrame * frame = new QFrame(this);
    //setCentralWidget(frame);
    // QMenu* file=menuBar()->addMenu("&Файл");
    //file->addAction(open);
    //file->addSeparator();
    //file->addAction(q);
    canvas=new Frame(this);
    canvas->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    canvas->setMinimumSize(1000,800);
    QHBoxLayout* hbox=new QHBoxLayout(this);
    hbox->setSpacing(3);
    hbox->addStretch(3);
    hbox->addWidget(canvas,0);
    QVBoxLayout *vbox=new QVBoxLayout();
    QGridLayout *grid1= new QGridLayout();
    vbox->setSpacing(1);
    // connect(q,&QAction::triggered,this,&Cristall::slotExit);

    QLabel *l1=new QLabel("Файл полигонов");
    QLabel *l2=new QLabel("Файл вершин");
    l1->setAlignment(Qt::AlignRight | Qt::AlignTop);
    l2->setAlignment(Qt::AlignRight | Qt::AlignTop);
    grid1->addWidget(l1,0,0);
    grid1->addWidget(l2,1,0);
    grid1->setAlignment(Qt::AlignTop);
    polLine=new QLineEdit();
    pointLine=new QLineEdit();
    connect(polLine,&QLineEdit::editingFinished,this,&Cristall::slotAddPolygons);
    connect(pointLine,&QLineEdit::editingFinished,this,&Cristall::slotAddPoints);
    grid1->addWidget(polLine,0,1);
    polLine->setFixedWidth(60);
    grid1->addWidget(pointLine,1,1);
    pointLine->setFixedWidth(60);
    QPushButton *openPolFile=new QPushButton("Выбрать файл",this);
    QPushButton *openPointFile=new QPushButton("Выбрать файл",this);
    connect(openPolFile,&QPushButton::clicked,this,&Cristall::slotAddPolygons);
    connect(openPointFile,&QPushButton::clicked,this,&Cristall::slotAddPoints);
    grid1->addWidget(openPolFile,0,2);
    grid1->addWidget(openPointFile,1,2);
    QPushButton *uploadFiles=new QPushButton("Загрузить",this);
    connect(uploadFiles,&QPushButton::clicked,this,&Cristall::slotUploadFiles);
    grid1->addWidget(uploadFiles,2,1);


    QGridLayout *grid2=new QGridLayout();
    QLabel *lblx=new QLabel("Угол x");
    QLabel *lbly=new QLabel("Угол y");
    QLabel *lblz=new QLabel("Угол z");
    lblx->setAlignment(Qt::AlignRight);
    lbly->setAlignment(Qt::AlignRight);
    lblz->setAlignment(Qt::AlignRight);
    lineAngleX=new QLineEdit();
    lineAngleY=new QLineEdit();
    lineAngleZ=new QLineEdit();
    lineAngleX->setFixedWidth(60);
    lineAngleY->setFixedWidth(60);
    lineAngleZ->setFixedWidth(60);
    QPushButton *btnX=new QPushButton("Step",this);
    QPushButton *btnY=new QPushButton("Step",this);
    QPushButton *btnZ=new QPushButton("Step",this);
    grid2->addWidget(lblx,0,0);
    grid2->addWidget(lbly,1,0);
    grid2->addWidget(lblz,2,0);
    grid2->addWidget(lineAngleX,0,1);
    grid2->addWidget(lineAngleY,1,1);
    grid2->addWidget(lineAngleZ,2,1);
    grid2->addWidget(btnX,0,2);
    grid2->addWidget(btnY,1,2);
    grid2->addWidget(btnZ,2,2);
    grid2->setAlignment(Qt::AlignTop);
    connect(btnX,&QPushButton::clicked,this,&Cristall::on_goStepX_clicked);
    connect(btnY,&QPushButton::clicked,this,&Cristall::on_goStepY_clicked);
    connect(btnZ,&QPushButton::clicked,this,&Cristall::on_goStepZ_clicked);
    connect(lineAngleX,&QLineEdit::editingFinished,this,&Cristall::slotChangeAngle);
    connect(lineAngleY,&QLineEdit::editingFinished,this,&Cristall::slotChangeAngle);
    connect(lineAngleZ,&QLineEdit::editingFinished,this,&Cristall::slotChangeAngle);


    QGridLayout *grid3=new QGridLayout();
    QLabel *lname=new QLabel("Масштаб");
    lname->setAlignment(Qt::AlignVCenter);
    grid3->addWidget(lname,0,1);
    QLabel *lbl1x=new QLabel("X");
    QLabel *lbl1y=new QLabel("Y");
    QLabel *lbl1z=new QLabel("Z");
    lbl1x->setAlignment(Qt::AlignRight);
    lbl1y->setAlignment(Qt::AlignRight);
    lbl1z->setAlignment(Qt::AlignRight);
    grid3->addWidget(lbl1x,1,0);
    grid3->addWidget(lbl1y,2,0);
    grid3->addWidget(lbl1z,3,0);
    lineScaleX=new QLineEdit();
    lineScaleY=new QLineEdit();
    lineScaleZ=new QLineEdit();
    lineScaleX->setFixedWidth(60);
    lineScaleY->setFixedWidth(60);
    lineScaleZ->setFixedWidth(60);
    grid3->addWidget(lineScaleX,1,1);
    grid3->addWidget(lineScaleY,2,1);
    grid3->addWidget(lineScaleZ,3,1);
    QPushButton *btn1X=new QPushButton("Scale X",this);
    QPushButton *btn1Y=new QPushButton("Scale Y",this);
    QPushButton *btn1Z=new QPushButton("Scale Z",this);
    connect(btn1X,&QPushButton::clicked,this,&Cristall::on_goScaleX_clicked);
    connect(btn1Y,&QPushButton::clicked,this,&Cristall::on_goScaleY_clicked);
    connect(btn1Z,&QPushButton::clicked,this,&Cristall::on_goScaleZ_clicked);
    grid3->addWidget(btn1X,1,2);
    grid3->addWidget(btn1Y,2,2);
    grid3->addWidget(btn1Z,3,2);
    grid3->setAlignment(Qt::AlignTop);

    QGridLayout *grid4=new QGridLayout();
    QLabel* lMoveName1=new QLabel("Смещение");

    // lMoveName1->setAlignment(Qt::AlignVCenter);
    grid4->addWidget(lMoveName1,0,1);
    QLabel* lMoveX=new QLabel("X");
    QLabel* lMoveY=new QLabel("Y");
    QLabel* lMoveZ=new QLabel("Z");
    grid4->addWidget(lMoveX,1,0);
    grid4->addWidget(lMoveY,1,1);
    grid4->addWidget(lMoveZ,1,2);
    //lMoveX->setAlignment(Qt::AlignCenter|Qt::AlignTop);
    //lMoveY->setAlignment(Qt::AlignCenter|Qt::AlignTop);
    //lMoveZ->setAlignment(Qt::AlignCenter|Qt::AlignTop);
    lineMoveX=new QLineEdit();
    lineMoveY=new QLineEdit();
    lineMoveZ=new QLineEdit();
    //  lineMoveX->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    //lineMoveY->setAlignment(Qt::AlignTop| Qt::AlignCenter);
    //lineMoveZ->setAlignment(Qt::AlignTop| Qt::AlignCenter);
    lineMoveX->setFixedWidth(60);
    lineMoveY->setFixedWidth(60);
    lineMoveZ->setFixedWidth(60);

    grid4->addWidget(lineMoveX,2,0);
    grid4->addWidget(lineMoveY,2,1);
    grid4->addWidget(lineMoveZ,2,2);
    grid4->setAlignment(Qt::AlignTop|Qt::AlignRight);
    QPushButton *btnMove=new QPushButton("Сместить");
    grid4->addWidget(btnMove,3,2,Qt::AlignLeft);

    connect(btnMove,&QPushButton::clicked,this,&Cristall::on_goMove_clicked);

    QGridLayout *grid5=new QGridLayout();
    QLabel *lReflectName=new QLabel("Отражение");
    grid5->addWidget(lReflectName,0,1);
    QPushButton *btnReflX=new QPushButton("Reflect X");
    QPushButton *btnReflY=new QPushButton("Reflect Y");
    QPushButton *btnReflZ=new QPushButton("Reflect Z");
    btnReflX->setFixedWidth(60);
    btnReflY->setFixedWidth(60);
    btnReflZ->setFixedWidth(60);
    grid5->addWidget(btnReflX,1,0);
    grid5->addWidget(btnReflY,1,1);
    grid5->addWidget(btnReflZ,1,2);
    grid5->setAlignment(Qt::AlignTop | Qt::AlignRight);
    connect(btnReflX,&QPushButton::clicked,this,&Cristall::on_goReflectX_clicked);
    connect(btnReflY,&QPushButton::clicked,this,&Cristall::on_goReflectY_clicked);
    connect(btnReflZ,&QPushButton::clicked,this,&Cristall::on_goReflectZ_clicked);

    vbox->addLayout(grid1);
    vbox->addLayout(grid2);
    vbox->addLayout(grid3);
    vbox->addLayout(grid4);
    vbox->addLayout(grid5);
    hbox->addLayout(vbox);
    setLayout(hbox);
}
Cristall::~Cristall()
{
}

void Cristall::slotAddPolygons()
{
    QString tmp= QFileDialog::getOpenFileName(0,"Choose file with polygons","","*txt");
    if(tmp.isEmpty())
    {

    }
    else
    {
        pathPolygon=tmp;
        polLine->setText(tmp);

    }
}

void Cristall::slotAddPoints()
{
    QString tmp= QFileDialog::getOpenFileName(0,"Choose file with polygons","","*txt");
    if(tmp.isEmpty())
    {
        QTextStream out(stdout);

    }
    else
    {
        pathPoints=tmp;
        pointLine->setText(tmp);
    }
}

void Cristall::slotUploadFiles()
{
    if(pathPolygon.isEmpty())
    {
        QMessageBox::warning(this,"Внимание!","Вы не выбрали файл");
        return;
    }
    if(pathPoints.isEmpty())
    {
        QMessageBox::warning(this,"Внимание!","Вы не выбрали файл");
        return;
    }
    canvas->upload(pathPolygon,pathPoints);

}

void Cristall::slotExit()
{
    this->close();
}

void Cristall::slotChangeAngle()
{
    canvas->setFiX(lineAngleX->text().toDouble());
    canvas->setFiX(lineAngleY->text().toDouble());
    canvas->setFiX(lineAngleZ->text().toDouble());
}



void Cristall::on_goStepX_clicked()
{
    canvas->rotateX();
}

void Cristall::on_goStepY_clicked()
{
    canvas->rotateY();
}

void Cristall::on_goStepZ_clicked()
{
    canvas->rotateZ("Right");
}

void Cristall::on_goScaleX_clicked()
{
    canvas->scaleX(lineScaleX->text().toDouble());
}

void Cristall::on_goScaleY_clicked()
{
    canvas->scaleY(lineScaleY->text().toDouble());
}

void Cristall::on_goScaleZ_clicked()
{
    canvas->scaleZ(lineScaleZ->text().toDouble());
}

void Cristall::on_goMove_clicked()
{
    canvas->moveToCoord(lineMoveX->text().toDouble(),lineMoveY->text().toDouble(),lineMoveZ->text().toDouble());
}

void Cristall::on_goReflectX_clicked()
{
    canvas->reflectX();
}

void Cristall::on_goReflectY_clicked()
{
    canvas->reflectY();
}

void Cristall::on_goReflectZ_clicked()
{
    canvas->reflectZ();
}



