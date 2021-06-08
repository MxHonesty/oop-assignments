#pragma once

#include <QtWidgets/QWidget>
#include <qtablewidget.h>
#include <qboxlayout.h>
#include <vector>
#include "Task.h"
#include "ui_GUI.h"
#include "Service.h"
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qformlayout.h>
#include "TableView.h"

class GUI : public QWidget
{
    Q_OBJECT

public:
    GUI(QWidget *parent = Q_NULLPTR);

    QVBoxLayout* layout = new QVBoxLayout{ this };
    QTableWidget* table = new QTableWidget{ this };

    // Pentru aduagare.
    QPushButton* btn_submit = new QPushButton{"Submit", this};
    QLineEdit* edit_id = new QLineEdit{this};
    QLineEdit* edit_desc = new QLineEdit{ this };
    QLineEdit* edit_stare = new QLineEdit{ this };
    QLineEdit* edit_programatori = new QLineEdit{ this };
    QFormLayout* form = new QFormLayout{ this };

    // Cautare
    QFormLayout* form_cautare = new QFormLayout{ this };
    QPushButton* btn_search = new QPushButton{ "Cauta", this };
    QLineEdit* edit_search = new QLineEdit{ this };

    // Cele trei ferestre
    TableViewOpen* open = new TableViewOpen{};
    TableViewClosed* closed = new TableViewClosed{};
    TableViewInProgress* progress = new TableViewInProgress{};

private:
    Ui::GUIClass ui;
    Service srv;

    void init_state();

    void connect_signals();

    void reload_table(const std::vector<Task>& new_tasks);
};
