#include "test_for_sim.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    test_for_sim w;
    w.show();
    return a.exec();
}
