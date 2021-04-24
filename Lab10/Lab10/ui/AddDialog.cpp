#include "AddDialog.h"

#include <string>
#include <QtWidgets/qmessagebox.h>

#include "../errors/ValidatorError.h"
#include "../errors/RepoError.h"

void AddDialog::init() {
	setModal(true);  // Setam dialog ca modal. Adica blocheaza input in alte ferestre.
	setLayout(main_layout);

	main_layout->addLayout(denumire_layout);
	main_layout->addLayout(destinatie_layout);
	main_layout->addLayout(tip_layout);
	main_layout->addLayout(pret_layout);
	main_layout->addWidget(btn_submit);
	main_layout->addWidget(btn_cancel);
	
	denumire_layout->addRow("Denumire", denumire);
	destinatie_layout->addRow("Destinatie", destinatie);
	tip_layout->addRow("Tip", tip);
	pret_layout->addRow("Pret", pret);
}

void AddDialog::add_oferta() {
	try {
		std::string str_denumire = denumire->text().toStdString();
		std::string str_destinatie = destinatie->text().toStdString();
		std::string str_tip = tip->text().toStdString();
		auto str_pret = pret->text();  // Folosim conversia din QString in int.

		bool ok_conversie;  // Determina daca conversia s-a efectuat cu succes.
		const int int_pret = str_pret.toInt(&ok_conversie);
		if (ok_conversie == false) {
			QMessageBox::warning(this, "Warning", "Invalid Input");
		}
		else {
			srv.adaugare(str_denumire, str_destinatie, str_tip, int_pret);
			done(QDialog::Accepted);
		}
	}
	catch (const ValidatorError& e) {
		QMessageBox::warning(this, "Warning", e.what());
	}
	catch (const RepoError& e) {
		QMessageBox::warning(this, "Warning", e.what());
	}
}

void AddDialog::connect_signals() {
	QObject::connect(btn_submit, &QPushButton::clicked, this, [this]() {
		add_oferta();
	});

	QObject::connect(btn_cancel, &QPushButton::clicked, this, [this]() {
		done(QDialog::Rejected);
	});

}
