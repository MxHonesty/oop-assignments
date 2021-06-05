#pragma once

#include <QtWidgets/QWidget>
#include "ui_MainWindow.h"
#include <qlistview.h>
#include "ProdusModel.h"
#include <qboxlayout.h>
#include <qlineedit.h>
#include <qpushbutton.h>

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(Service& srv, QWidget *parent = Q_NULLPTR);

private:

    // Initializeaza starea elementelor.
    void init_state();

    // Conecteaza semnale
    void connect_signals();

    Ui::MainWindowClass ui;
    Service& srv;

    ProdusModel* model;
    QListView* list_view;
    QVBoxLayout* layout;

    QLineEdit* line;
    QPushButton* btn_sort_tip;
    QPushButton* btn_sort_ca;
    QPushButton* btn_refresh;
};
