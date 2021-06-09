#include "GUI.h"
#include <QtWidgets/QApplication>
#include "Test.h"

int main(int argc, char *argv[])
{
    Test tst;
    tst.run_all_tests();

    QApplication a(argc, argv);
    GUI w;
    w.show();
    return a.exec();
}
