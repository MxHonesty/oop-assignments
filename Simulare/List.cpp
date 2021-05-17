#include "List.h"

void List::init() {
	setLayout(layout);

	layout->addWidget(list);
	layout->addWidget(cap);
	layout->addWidget(sort1);
	layout->addWidget(sort2);
	cap->setDisabled(true);
}

void List::connect_signals() {
	QObject::connect(list, &QListWidget::itemClicked, this, [this]() {
		int selected = list->currentRow();
		auto item = list->item(selected);

		int id = item->data(Qt::UserRole).toInt();
		cap->setText(QString::number(srv.stoc_necesar(id)));
	});

	QObject::connect(sort1, &QPushButton::clicked, this, [this]() {
		reload_list(srv.sortare_stoc_desc());
	});

	QObject::connect(sort1, &QPushButton::clicked, this, [this]() {
		reload_list(srv.sortare_tip_crescator());
	});
}

void List::reload_list(std::vector<Produs> items) {
	list->clear();

	for (const auto& el : items) {
		auto text = el.get_denumire();
		auto item = new QListWidgetItem{ QString::fromStdString(text) };
		item->setData(Qt::UserRole, QString::number(el.get_id()));
		if (srv.nu_este_suficient(el.get_id())) {
			item->setBackground(Qt::red);
		}
		else {
			item->setBackground(Qt::green);
		}
		list->addItem(item);
	}
}
