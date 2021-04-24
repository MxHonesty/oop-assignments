#include "ListView.h"

void ListView::init_ListView() {
	setLayout(layout);
	layout->addWidget(list);
	layout->addWidget(btn_remove);
}

void ListView::connect_signals() {
	QObject::connect(btn_remove, &QPushButton::clicked, this, [this]() {
		//QMessageBox::information(this, "Titlu", "Mesaj");
		this->remove_oferta_selectata();
	});

	QObject::connect(list, &QListWidget::currentItemChanged, this, [this]() {
		
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

void ListView::add_oferta() {
	
}

void ListView::remove_oferta_selectata() {
	auto selected = list->selectedItems();
	if (selected.isEmpty()) {
		QMessageBox::warning(this, "Warning", "Nothing selected");
	}
	else {
		int id = selected.at(0)->data(Qt::UserRole).toInt();
		srv.stergere(id);
		reload_list(srv.get_ref_all());
	}
}
