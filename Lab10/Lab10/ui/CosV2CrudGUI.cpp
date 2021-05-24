#include "CosV2CrudGUI.h"

void CosV2CrudGUI::init_layout() {
	setLayout(layout);
	layout->addWidget(table);
	layout->addWidget(btn_golire);
	layout->addWidget(btn_random);
}

void CosV2CrudGUI::connect_signals() {
	QObject::connect(btn_golire, &QPushButton::clicked, this, [this]() {
		srv.golire_cos();
	});

	QObject::connect(btn_random, &QPushButton::clicked, this, [this]() {
		srv.adauga_random_cos(3);
	});
}

void CosV2CrudGUI::init_state() {
	update();
}

void CosV2CrudGUI::reload_list(const std::vector<Oferta>& elems) {
	table->clear();
	int marime_rows = static_cast<int>(elems.size());
	table->setRowCount(marime_rows);
	table->setColumnCount(4);
	int index = 0;
	for (const auto& el : elems) {
		auto item_denumire = new QTableWidgetItem{ QString::fromStdString(el.get_denumire()) };
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

void CosV2CrudGUI::update() {
	reload_list(srv.vector_cos());
}
