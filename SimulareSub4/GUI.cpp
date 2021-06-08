#include "GUI.h"
#include <qmessagebox.h>

GUI::GUI(QWidget* parent) : QWidget(parent), srv{} {
    ui.setupUi(this);
    init_state();
    connect_signals();
}

void GUI::init_state() {
    setLayout(layout);
    layout->addWidget(table);

    reload_table(srv.get_all());
    layout->addLayout(form);
    
    form->addRow("Id", edit_id);
    form->addRow("Descriere", edit_desc);
    form->addRow("Stare", edit_stare);
    form->addRow("Programatori", edit_programatori);
    layout->addWidget(btn_submit);

    layout->addLayout(form_cautare);
    form_cautare->addRow("Nume Cuatat", edit_search);
    layout->addWidget(btn_search);

}

void GUI::connect_signals() {
    QObject::connect(btn_submit, &QPushButton::clicked, this, [this]() {
        int id{ -1 };
        string descriere, stare;
        vector<string> programatori;

        bool ok = true;
        id = edit_id->text().toInt(&ok);
        if(ok == false) {
            QMessageBox::warning(this, "Warning",  "Integer conversion error");
        }

        // Separam stringul de programatori intr-un vector.
        std::istringstream in{ edit_programatori->text().toStdString() };
        string prog;
        getline(in, prog, ',');
        while (in.good()) {
            programatori.push_back(prog);
            getline(in, prog, ',');
        }

        try {
            srv.add_task(id, edit_desc->text().toStdString(), edit_stare->text().toStdString(),
                programatori);
        }
        catch (std::exception& e) {
            QMessageBox::warning(this, "Warning", e.what());
        }
        reload_table(srv.get_all());
    });

    QObject::connect(btn_search, &QPushButton::clicked, this, [this]() {
        reload_table(srv.get_programator(edit_search->text().toStdString()));
    });
}

void GUI::reload_table(const std::vector<Task>& new_tasks) {
    table->clear();
    int marime_rows = static_cast<int>(new_tasks.size());
    table->setRowCount(marime_rows);
    table->setColumnCount(4);

    int index = 0;
    for (const auto& tsk : new_tasks) {
        auto tsk_id = new QTableWidgetItem{QString::number(tsk.get_id())};
        auto tsk_desc = new QTableWidgetItem{QString::fromStdString(tsk.get_descriere())};
        auto tsk_stare = new QTableWidgetItem{QString::fromStdString(tsk.get_stare())};
        auto tsk_numar = new QTableWidgetItem{QString::number(tsk.get_programatori().size())};


        table->setItem(index, 0, tsk_id);
        table->setItem(index, 1, tsk_desc);
        table->setItem(index, 2, tsk_stare);
        table->setItem(index, 3, tsk_numar);

        index++;
    }
}
