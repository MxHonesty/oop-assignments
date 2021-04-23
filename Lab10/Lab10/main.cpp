#include <QtWidgets/QApplication>
#include "Lab10.h"
#include "tests/tests.h"

int main(int argc, char *argv[]) {

    Testing::run_all_tests();

    QApplication a(argc, argv);
    Lab10 w;
    w.show();
    return a.exec();
}
