#include "ListView.h"
#include "../errors/RepoError.h"

void ListView::init_ListView() {
	setLayout(layout);
	layout->addWidget(list);
	layout->addLayout(button_layout);
	
	button_layout->addWidget(btn_add);
	button_layout->addWidget(btn_modify);
	button_layout->addWidget(btn_remove);
	button_layout->addWidget(btn_info);
	button_layout->addWidget(btn_undo);
}

void ListView::connect_signals() {
	QObject::connect(btn_remove, &QPushButton::clicked, this, [this]() {
		//QMessageBox::information(this, "Titlu", "Mesaj");
		this->remove_oferta_selectata();
	});

	QObject::connect(btn_add, &QPushButton::clicked, this, [this]() {
		start_add_menu();
	});

	QObject::connect(btn_undo, &QPushButton::clicked, this, [this]() {
		undo();
	});

	QObject::connect(btn_modify, &QPushButton::clicked, this, [this]() {
		start_modify_menu();
	});

	QObject::connect(btn_info, &QPushButton::clicked, this, [this]() {
		start_info_menu();
	});
}

void ListView::reload_list(const std::vector<Oferta>& oferte) {
	list->clear();
	for (const auto& el : oferte) {
		auto text = el.get_denumire();
		auto item = new QListWidgetItem{QString::fromStdString(text)};
		item->setData(Qt::UserRole, QString::number(el.get_id()));  // Pastram id-ul ca data.
		list->addItem(item);
	}
}

void ListView::remove_oferta_selectata() {
	auto selected = list->selectedItems();
	if (selected.isEmpty()) {
		QMessageBox::warning(this, "Warning", "No selection made");
	}
	else {
		int id = selected.at(0)->data(Qt::UserRole).toInt();
		srv.stergere(id);
		reload_list(srv.get_ref_all());
	}
}

void ListView::start_add_menu() {
	AddDialog dialog(srv, this);
	const auto return_value = dialog.exec();
	if (return_value == QDialog::Accepted) {
		reload_list(srv.get_ref_all());
	}
}

void ListView::start_modify_menu() {

}

void ListView::start_info_menu() {
	auto selected = list->selectedItems();
	if (selected.isEmpty()) {
		QMessageBox::warning(this, "Warning", "No selection made");
	}
	else {
		int id = selected.at(0)->data(Qt::UserRole).toInt();
		try {
			const auto& oferta = srv.cautare(id);
			InfoDialog dialog{ oferta, this };
			dialog.exec();
		}
		catch (const RepoError& e) {
			QMessageBox::warning(this, "Warning", e.what());
		}
	}
}

void ListView::undo() {
	srv.undo();
	reload_list(srv.get_ref_all());
}
