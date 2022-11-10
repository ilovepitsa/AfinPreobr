#include "menu.h"
#include <QMenu>
#include <QMenuBar>


Menu::Menu(QWidget *parent)
    : QMainWindow{parent}
{
    QAction* q=new QAction("&Выход",this);
    QAction* open=new QAction("&Открыть",this);
    QMenu *file;
    file=menuBar()->addMenu("&Файл");
    file->addAction(q);
    file->addAction(open);

    connect(q,&QAction::triggered,qApp,&QApplication::quit);
}
