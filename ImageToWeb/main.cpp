#include "ImageToWeb.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImageToWeb w;
    w.show();
    return a.exec();
}

