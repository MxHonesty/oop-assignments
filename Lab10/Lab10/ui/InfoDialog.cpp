#include "InfoDialog.h"

void InfoDialog::init() {
	setLayout(main_layout);

	main_layout->addLayout(denumire_layout);
	main_layout->addLayout(destinatie_layout);
	main_layout->addLayout(tip_layout);
	main_layout->addLayout(pret_layout);
	main_layout->addWidget(btn_submit);

	denumire_layout->addRow("Denumire", denumire);
	destinatie_layout->addRow("Destinatie", destinatie);
	tip_layout->addRow("Tip", tip);
	pret_layout->addRow("Pret", pret);

	denumire->setReadOnly(true);
	destinatie->setReadOnly(true);
	tip->setReadOnly(true);
	pret->setReadOnly(true);
}

void InfoDialog::connect_signals() {

	// Butonul inchide Dialogul
	QObject::connect(btn_submit, &QPushButton::clicked, this, [this]() {
		done(QDialog::Accepted);
	});
}

void InfoDialog::setup_initial_state() {
	denumire->setText(QString::fromStdString(oferta.get_denumire()));
	destinatie->setText(QString::fromStdString(oferta.get_destinatie()));
	tip->setText(QString::fromStdString(oferta.get_tip()));
	pret->setText(QString::fromStdString(std::to_string(oferta.get_pret())));
}
