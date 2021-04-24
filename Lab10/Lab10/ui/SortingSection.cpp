#include "SortingSection.h"

void SortingSection::init() {
	setLayout(layout);
	layout->addWidget(btn_pret);
	layout->addWidget(btn_denumire);
	layout->addWidget(btn_tip);
	layout->addWidget(este_descrescator);
}

void SortingSection::connect_signals() {
	QObject::connect(btn_pret, &QPushButton::clicked, this, [this]() {
		const auto descrescator = este_descrescator->isChecked();
		emit sortare_pret(!descrescator);  // Emitem true daca e crescator
	});

	QObject::connect(btn_denumire, &QPushButton::clicked, this, [this]() {
		const auto descrescator = este_descrescator->isChecked();
		emit sortare_denumire(!descrescator);  // Emitem true daca e crescator
	});

	QObject::connect(btn_tip, &QPushButton::clicked, this, [this]() {
		const auto descrescator = este_descrescator->isChecked();
		emit sortare_tip(!descrescator);  // Emitem true daca e crescator
	});
}
