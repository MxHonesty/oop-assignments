#pragma once

#include <QtWidgets/QWidget>
#include "ui_GUI.h"
#include "Service.h"
#include <qboxlayout.h>
#include <qtablewidget.h>
#include <qformlayout.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include "TableWindow.h"
#include "Observer.h"

class GUI : public QWidget, public Observer {
    Q_OBJECT

public:
    GUI(QWidget *parent = Q_NULLPTR);

    // Reincarca lista
    void notify() override;

private:
    Ui::GUIClass ui;

    Service srv;

    // Initializeaza starea componentelor.
    void init_state();

    // Initializeaza starea pentru partea de adaugare.
    void init_add_state();

    // Initializeaza starea pentru partea de cautare.
    void init_cautare_state();

    // Metoda adauga task-ul dat de text-field-urile de mai jos.
    void add_task();

    // Conecteaza semnale.
    void connect_signals();

    // Reincarca tabelul cu elemente.
    void reload_table(const std::vector<Task>& new_tasks);

    QVBoxLayout* layout = new QVBoxLayout{ this };
    
    // Pentru Tabel
    QTableWidget* tabel = new QTableWidget{ this };

    // Pentru Adaugare
    QFormLayout* form_layout = new QFormLayout{ this };
    QPushButton* btn_submit = new QPushButton{ "Submit", this };
    QLineEdit* edit_id = new QLineEdit{ this };
    QLineEdit* edit_descriere = new QLineEdit{ this };
    QLineEdit* edit_stare = new QLineEdit{ this };
    // PRogramatori Adaugam 4 qlineedits. 
    // Asa respectam constrangerea de avea maxim 4 programatori.
    QHBoxLayout* programatori_layout = new QHBoxLayout{ this };
    QLineEdit* edit_prog1 = new QLineEdit{ this };
    QLineEdit* edit_prog2 = new QLineEdit{ this };
    QLineEdit* edit_prog3 = new QLineEdit{ this };
    QLineEdit* edit_prog4 = new QLineEdit{ this };

    // Functionalitatea 3 - Cautare dupa PRogramator.
    QHBoxLayout* cautare_layout = new QHBoxLayout{ this };
    QPushButton* btn_cautare = new QPushButton{"Cautare Nume Programator", this};
    QPushButton* btn_refresh = new QPushButton{"Refresh", this};
    QLineEdit* edit_cautare_programator = new QLineEdit{this};

    // Window-uri
    TableWindowOpen* table_open;
    TableWindowOpen* table_closed;
    TableWindowOpen* table_inprogress;
};
