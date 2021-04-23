#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lab10.h"

#include "service/ServiceOferta.h"
#include "ui/ListView.h"
#include <QtWidgets/qboxlayout.h>

class Lab10 : public QMainWindow {
    Q_OBJECT

public:
    Lab10(QWidget *parent = Q_NULLPTR);

private:
    Ui::Lab10Class ui;

    ServiceOferta srv;  // Service.
    ListView* list_view = new ListView{ srv };
    QHBoxLayout* main_layout = new QHBoxLayout{this};

    void init();
};
