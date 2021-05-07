#include "FilterSection.h"
#include <QtWidgets/qmessagebox.h>

void FilterSection::init() {
	setLayout(layout);
	destinatie_layout->addWidget(destinatie);
	destinatie_layout->addWidget(btn_filtrare_destinatie);
	layout->addLayout(destinatie_layout);
	
	pret_min_layout->addRow("Pret minim", pret_min);
	pret_min_layout->addRow("Pret maxim", pret_max);
	pret_button_layout->addRow(btn_filtrare_pret);

	pret_layout_input->addLayout(pret_min_layout);;
	pret_layout_input->addLayout(pret_max_layout);
	pret_layout_input->addLayout(pret_button_layout);
	layout->addLayout(pret_layout_input);
}

void FilterSection::connect_signals() {
	QObject::connect(btn_filtrare_destinatie, &QPushButton::clicked, this, [this]() {
		std::string str_destinatie = destinatie->text().toStdString();
		emit filtrare_destinatie(str_destinatie);
	});

	QObject::connect(btn_filtrare_pret, &QPushButton::clicked, this, [this]() {
		auto str_pret_min = pret_min->text();
		auto str_pret_max = pret_max->text();

		bool ok_conversie1;
		const int pret_min = str_pret_min.toInt(&ok_conversie1);
		
		bool ok_conversie2;
		const int pret_max = str_pret_max.toInt(&ok_conversie2);

		if (ok_conversie1 == false || ok_conversie2 == false || pret_min < 0 || pret_max < 0 ||
			pret_min > pret_max) {
			QMessageBox::warning(this, "Warning", "Invalid Input");
		}
		else
			emit filtrare_pret(pret_min, pret_max);
	});
}
