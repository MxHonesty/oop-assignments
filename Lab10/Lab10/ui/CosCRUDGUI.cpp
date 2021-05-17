#include "CosCRUDGUI.h"
#include <QtWidgets/qmessagebox.h>

void CosCRUDGUI::init_layout() {
	setLayout(layout);
	layout->addWidget(list);
	layout->addWidget(btn_golire);
	layout->addWidget(btn_random);
}

void CosCRUDGUI::connect_signals() {
	QObject::connect(btn_golire, &QPushButton::clicked, this, [this]() {
		srv.golire_cos();
	});

	QObject::connect(btn_random, &QPushButton::clicked, this, [this]() {
		srv.adauga_random_cos(3);
	});
}

void CosCRUDGUI::init_state() {
	update();
}

void CosCRUDGUI::reload_list(const std::vector<Oferta>& elems) {
	list->clear();
	for (const auto& el : elems) {
		auto text = el.get_denumire();
		auto item = new QListWidgetItem{ QString::fromStdString(text) };
		item->setData(Qt::UserRole, QString::number(el.get_id()));
		list->addItem(item);
	}
}

void CosCRUDGUI::update() {
	reload_list(srv.vector_cos());
}
