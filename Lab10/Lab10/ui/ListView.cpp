#include "ListView.h"

void ListView::init_ListView() {
	setLayout(layout);
	layout->addWidget(list);
	layout->addWidget(btn_remove);
}

void ListView::connect_signals() {
	QObject::connect(btn_remove, &QPushButton::clicked, this, [this]() {
		QMessageBox::information(this, "Titlu", "Mesaj");
	});
}

void ListView::reload_list(const std::vector<Oferta>& oferte) {
	list->clear();
	for (const auto& el : oferte) {
		auto text = el.get_denumire();
		auto item = new QListWidgetItem{QString::fromStdString(text)};
		list->addItem(item);
	}
}

void ListView::add_oferta() {

}
