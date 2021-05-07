#include "ListView.h"
#include "../errors/RepoError.h"

void ListView::init_ListView() {
	setLayout(main_layout);
	main_layout->addWidget(table);
	main_layout->addLayout(list_layout);
	main_layout->addWidget(sorting);
	main_layout->addWidget(filtering);

	list_layout->addWidget(list);
	list_layout->addLayout(button_layout);
	
	button_layout->addWidget(btn_add);
	button_layout->addWidget(btn_modify);
	button_layout->addWidget(btn_remove);
	button_layout->addWidget(btn_info);
	button_layout->addWidget(btn_undo);
	button_layout->addWidget(btn_refresh);
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

	QObject::connect(list, &QListWidget::itemDoubleClicked, this, [this]() {
		start_info_menu();
	});

	QObject::connect(btn_refresh, &QPushButton::clicked, this, [this]() {
		reload(srv.get_all());
	});
}

void ListView::connect_sorting_signals() {
	QObject::connect(sorting, &SortingSection::sortare_pret, this, [this](const bool crescator) {
		if (crescator) {
			reload(srv.sortare([](const Oferta& a, const Oferta& b) noexcept {
				return a.get_pret() < b.get_pret();
			}));
		}
		else {
			reload(srv.sortare([](const Oferta& a, const Oferta& b) noexcept {
				return a.get_pret() > b.get_pret();
			}));
		}
	});

	QObject::connect(sorting, &SortingSection::sortare_denumire, this, [this](const bool crescator) {
		if (crescator) {
			reload(srv.sortare([](const Oferta& a, const Oferta& b) {
				return a.get_denumire() < b.get_denumire();
			}));
		}
		else {
			reload(srv.sortare([](const Oferta& a, const Oferta& b) {
				return a.get_denumire() > b.get_denumire();
			}));
		}
	});

	QObject::connect(sorting, &SortingSection::sortare_tip, this, [this](const bool crescator) {
		if (crescator) {
			reload(srv.sortare([](const Oferta& a, const Oferta& b) {
				return a.get_tip() < b.get_tip();
			}));
		}
		else {
			reload(srv.sortare([](const Oferta& a, const Oferta& b) {
				return a.get_tip() > b.get_tip();
			}));
		}
	});
}

void ListView::connect_filtering_signals() {
	QObject::connect(filtering, &FilterSection::filtrare_destinatie, this, [this](std::string destinatie) {
		reload(srv.filtrare_destinatie(destinatie));
	});

	QObject::connect(filtering, &FilterSection::filtrare_pret, this, [this](int min, int max) {
		reload(srv.filtrare_pret(min, max));
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

void ListView::reload_table(const std::vector<Oferta>& oferte) {
	table->clear();
	int marime_rows = static_cast<int>(oferte.size());
	table->setRowCount(marime_rows);
	table->setColumnCount(4);
	int index = 0;
	for (const auto& el : oferte) {
		auto item_denumire = new QTableWidgetItem{QString::fromStdString(el.get_denumire())};
		auto item_destinatie = new QTableWidgetItem(QString::fromStdString(el.get_destinatie()));
		auto item_tip = new QTableWidgetItem(QString::fromStdString(el.get_tip()));
		auto item_pret = new QTableWidgetItem(QString::fromStdString(std::to_string(el.get_pret())));

		table->setItem(index, 0, item_denumire);
		table->setItem(index, 1, item_destinatie);
		table->setItem(index, 2, item_tip);
		table->setItem(index, 3, item_pret);
		index++;
	}
}

void ListView::reload(const std::vector<Oferta>& oferte) {
	reload_list(oferte);
	reload_table(oferte);
}

void ListView::remove_oferta_selectata() {
	auto selected = list->selectedItems();
	if (selected.isEmpty()) {
		QMessageBox::warning(this, "Warning", "No selection made");
	}
	else {
		int id = selected.at(0)->data(Qt::UserRole).toInt();
		srv.stergere(id);
		reload(srv.get_ref_all());
	}
}

void ListView::start_add_menu() {
	AddDialog dialog(srv, this);
	const auto return_value = dialog.exec();
	if (return_value == QDialog::Accepted) {
		reload(srv.get_ref_all());
	}
}

void ListView::start_modify_menu() {
	auto selected = list->selectedItems();
	if (selected.isEmpty()) {
		QMessageBox::warning(this, "Warning", "No selection made");
	}
	else {
		int id = selected.at(0)->data(Qt::UserRole).toInt();
		try {
			const auto& oferta = srv.cautare(id);
			ModifyDialog dialog{ srv, oferta, this };
			const int return_value = dialog.exec();
			if (return_value == QDialog::Accepted) {
				reload(srv.get_ref_all());
			}
		}
		catch (const RepoError& e) {
			QMessageBox::warning(this, "Warning", e.what());
		}
	}
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
	reload(srv.get_ref_all());
}
