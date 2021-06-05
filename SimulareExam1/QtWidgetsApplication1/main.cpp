#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include "Test.h"

int main(int argc, char *argv[])
{
    Test test;
    test.run_all_tests();

    Service srv;

    QApplication a(argc, argv);
    MainWindow w{ srv };
    w.show();
    return a.exec();
}
