#include "TableWindow.h"
#include <qmessagebox.h>

void TableWindowOpen::reload_list(const std::vector<Task>& new_tasks) {
    list->clear();

    for (const auto& el : new_tasks) {
        string text = QString::number(el.get_id()).toStdString() + " " + el.get_descriere() + " " + el.get_stare();
        auto item = new QListWidgetItem{QString::fromStdString(text)};

        item->setData(Qt::UserRole, QString::number(el.get_id()));

        list->addItem(item);
    }
}

void TableWindowOpen::init_state() {
	setLayout(layout);

	layout->addWidget(list);
	layout->addWidget(btn_open);
	layout->addWidget(btn_closed);
	layout->addWidget(btn_inprogress);

    notify();
}

void TableWindowOpen::connect_signals() {
	QObject::connect(btn_open, &QPushButton::clicked, this, [this]() {
        int id = get_selected_id_or_error();
        if (id != -1) {
            srv.change_stare(id, "open");
        }
	});

	QObject::connect(btn_closed, &QPushButton::clicked, this, [this]() {
        int id = get_selected_id_or_error();
        if (id != -1) {
            srv.change_stare(id, "closed");
        }
	});

	QObject::connect(btn_inprogress, &QPushButton::clicked, this, [this]() {
        int id = get_selected_id_or_error();
        if (id != -1) {
            srv.change_stare(id, "inprogress");
        }
	});
}

int TableWindowOpen::get_selected_id_or_error() {
    auto selected = list->selectedItems();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Nu este nimic selectat");
        return -1;
    }

    int id = selected.at(0)->data(Qt::UserRole).toInt();
    return id;
}
