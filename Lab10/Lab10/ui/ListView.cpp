#include "ListView.h"
#include "../errors/RepoError.h"


void ListView::init_model_view() {
	this->list_view = new QListView{ this };
	this->table_view = new QTableView{ this };
	this->oferte_model = new OfertaListModel{ srv.get_all(), this };
	
	table_view->setModel(oferte_model);
	list_view->setModel(oferte_model);
}

void ListView::init_ListView() {
	setLayout(main_layout);
	main_layout->addWidget(table_view);
	main_layout->addLayout(list_layout);
	main_layout->addLayout(sections_layout);

	sections_layout->addWidget(sorting);
	sections_layout->addWidget(filtering);
	sections_layout->addWidget(cosing);

	list_layout->addWidget(list_view);
	list_layout->addLayout(button_layout);
	list_layout->addLayout(cos_button_layout);
	
	button_layout->addWidget(btn_add);
	button_layout->addWidget(btn_modify);
	button_layout->addWidget(btn_remove);
	button_layout->addWidget(btn_info);
	button_layout->addWidget(btn_undo);
	button_layout->addWidget(btn_refresh);

	cos_button_layout->addWidget(btn_cos_adauga);
	cos_button_layout->addWidget(btn_cos_elimina);
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

	QObject::connect(btn_refresh, &QPushButton::clicked, this, [this]() {
		reload(srv.get_all());
	});

	QObject::connect(list_view->selectionModel(), &QItemSelectionModel::selectionChanged, this, [this]() {
		// Activam Dialog cu infomatii cand se schimba selectia.
		auto rez = get_selected_row(false);
		oferte_model->set_selected(rez.first);

		start_info_menu();
	});


	QObject::connect(btn_cos_adauga, &QPushButton::clicked, this, [this]() {
		auto rez = get_selected_id(true);
		int selected_id = rez.first;
		if (rez.second) {
			const auto& oferta = srv.cautare(selected_id);
			srv.adauga_cos(oferta.get_denumire());
		}
	});

	QObject::connect(btn_cos_elimina, &QPushButton::clicked, this, [this]() {
		auto selected = get_selected_id(true);
		if (selected.second) {
			int id = selected.first;
			const auto& oferta = srv.cautare(id);
			srv.sterge_din_cos(oferta.get_denumire());
		}
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

void ListView::reload(const std::vector<Oferta>& oferte) {
	oferte_model->set_oferte(oferte);
}

void ListView::remove_oferta_selectata() {
	auto selected = get_selected_id(true);

	if (selected.second) {
		int id = selected.first;
		srv.stergere(id);
		reload(srv.get_ref_all());
	}
}

void ListView::start_add_menu() {
	AddDialog dialog(srv, this);
	const auto return_value = dialog.exec();
	if (return_value == QDialog::Accepted) {
		reload(srv.get_all());
	}
}

void ListView::start_modify_menu() {
	auto selected = get_selected_id(true);

	if (selected.second) {
		int id = selected.first;
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
	auto selected = get_selected_id(true);
	
	if (selected.second) {
		int id = selected.first;
		try {
			const auto& oferta = srv.cautare(id);
			InfoDialog dialog{ oferta, true, this };
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

std::pair<int, bool> ListView::get_selected_id(const bool panic) {
	if (list_view->selectionModel()->selectedIndexes().isEmpty()) {
		if (panic) {
			QMessageBox::warning(this, "Warning", "No selection made");
		}
		return { 0, false };
	}
	else {
		const auto selected_index = list_view->selectionModel()->selectedIndexes().at(0);
		int id = selected_index.data(Qt::UserRole).toInt();
		return { id, true };
	}
}

std::pair<int, bool> ListView::get_selected_row(const bool panic) {
	if (list_view->selectionModel()->selectedIndexes().isEmpty()) {
		if (panic) {
			QMessageBox::warning(this, "Warning", "No selection made");
		}
		return { -1, false };
	}
	else {
		const auto selected_index = list_view->selectionModel()->selectedIndexes().at(0);
		int row = selected_index.row();
		return { row, true };
	}
}
