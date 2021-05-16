#include "test_for_sim.h"

test_for_sim::test_for_sim(QWidget *parent) : QMainWindow(parent) {
    ui.setupUi(this);
    setCentralWidget(list);
}
