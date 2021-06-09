#include "GUI.h"
#include <qmessagebox.h>

GUI::GUI(QWidget* parent) : QWidget(parent), srv{"data.txt"} {
    ui.setupUi(this);
    init_state();
    init_add_state();
    init_cautare_state();

    connect_signals();
    srv.addObserver(this);

    table_open = new TableWindowOpen{ srv, "open" };
    table_closed = new TableWindowOpen{ srv, "closed" };
    table_inprogress = new TableWindowOpen{ srv, "inprogress" };
    
    table_open->show();
    table_closed->show();
    table_inprogress->show();
}

void GUI::notify() {
    reload_table(srv.get_all());
}

void GUI::init_state() {
    setLayout(layout);
    layout->addWidget(tabel);
    reload_table(srv.get_all());

    layout->addLayout(form_layout);
    layout->addWidget(btn_submit);
    layout->addLayout(cautare_layout);
}

void GUI::init_add_state() {
    programatori_layout->addWidget(edit_prog1);
    programatori_layout->addWidget(edit_prog2);
    programatori_layout->addWidget(edit_prog3);
    programatori_layout->addWidget(edit_prog4);

    form_layout->addRow("Id", edit_id);
    form_layout->addRow("Descriere", edit_descriere);
    form_layout->addRow("Stare", edit_stare);
    form_layout->addRow("Programatori", programatori_layout);
}

void GUI::init_cautare_state() {
    cautare_layout->addWidget(edit_cautare_programator);
    cautare_layout->addWidget(btn_cautare);
    cautare_layout->addWidget(btn_refresh);
}

void GUI::add_task() {
    bool ok = true;
    int id = edit_id->text().toInt(&ok);
    if (ok == false) {  // Conversie esuata.
        QMessageBox::warning(this, "Warning", "Id invalid");
        return;
    }

    string descriere = edit_descriere->text().toStdString();
    string stare = edit_stare->text().toStdString();

    vector<string> prog;
    prog.push_back(edit_prog1->text().toStdString());
    prog.push_back(edit_prog2->text().toStdString());
    prog.push_back(edit_prog3->text().toStdString());
    prog.push_back(edit_prog4->text().toStdString());

    // Parcurgem si le includem intr-un nou vector doar pe cele care sunt nevide.
    vector<string> programatori;
    for (const auto& el : prog) {
        if (el != "") {
            programatori.push_back(el);
        }
    }

    if (programatori.size() == 0) {
        QMessageBox::warning(this, "Warning", "Trebuie cel putin un programator");
        return;
    }

    try {
        srv.add_task(id, descriere, stare, programatori);
    }
    catch (std::exception& e) {
        QMessageBox::warning(this, "Warning", e.what());
    }
}

void GUI::connect_signals() {
    QObject::connect(btn_submit, &QPushButton::clicked, this, [this]() {
        add_task();
        reload_table(srv.get_all());
    });

    QObject::connect(btn_cautare, &QPushButton::clicked, this, [this]() {
        std::string nume_cautat = edit_cautare_programator->text().toStdString();
        reload_table(srv.get_programtor(nume_cautat));
    });
    
    QObject::connect(btn_refresh, &QPushButton::clicked, this, [this]() {
        reload_table(srv.get_all());
    });
}

void GUI::reload_table(const std::vector<Task>& new_tasks) {
    tabel->clear();
    int marime_rows = static_cast<int>(new_tasks.size());

    tabel->setRowCount(marime_rows);
    tabel->setColumnCount(4);

    int index = 0;
    for (const auto& el : new_tasks) {
        auto tsk_id = new QTableWidgetItem{ QString::number(el.get_id()) };
        auto tsk_desc = new QTableWidgetItem{ QString::fromStdString(el.get_descriere()) };
        auto tsk_stare = new QTableWidgetItem{ QString::fromStdString(el.get_stare()) };
        auto tsk_nr_prog = new QTableWidgetItem{ QString::number(el.get_programatori().size()) };

        tabel->setItem(index, 0, tsk_id);
        tabel->setItem(index, 1, tsk_desc);
        tabel->setItem(index, 2, tsk_stare);
        tabel->setItem(index, 3, tsk_nr_prog);
        index++;
    }
}
