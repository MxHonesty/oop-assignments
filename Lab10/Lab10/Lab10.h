#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lab10.h"

#include "service/ServiceOferta.h"
#include "ui/ListView.h"
#include <QtWidgets/qboxlayout.h>

#include <QtWidgets/qlistwidget.h>

/**
    Main Window-ul aplicatiei.
*/
class Lab10 : public QMainWindow {
    Q_OBJECT

public:
    Lab10(QWidget *parent = Q_NULLPTR);

private:
    Ui::Lab10Class ui;

    ServiceOferta srv;  // Service.
    ListView* list_view;

    /** Initializeaza layout-ul aplicatiei */
    void init();
};
