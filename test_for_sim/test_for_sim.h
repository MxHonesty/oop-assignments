#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_test_for_sim.h"
#include "List.h"

class test_for_sim : public QMainWindow
{
    Q_OBJECT

public:
    test_for_sim(QWidget *parent = Q_NULLPTR);

private:
    Ui::test_for_simClass ui;

    List* list = new List{ this };
};
