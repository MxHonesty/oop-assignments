#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Simulare.h"

#include "Service.h"
#include "List.h"

class Simulare : public QMainWindow
{
    Q_OBJECT

public:
    Simulare(QWidget *parent = Q_NULLPTR);

private:
    Ui::SimulareClass ui;

    List* lista = new List{ this };
};
