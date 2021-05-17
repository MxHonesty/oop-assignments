#include "Simulare.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Simulare w;
    w.show();
    return a.exec();
}
