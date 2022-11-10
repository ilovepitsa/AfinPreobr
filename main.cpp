#include "cristall.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Cristall w;
    w.move(300,0);
    w.resize(1000,1000);
    w.show();
    return a.exec();
}
