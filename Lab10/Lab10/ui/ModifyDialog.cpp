#include "ModifyDialog.h"
#include "../errors/ValidatorError.h"
#include <QtWidgets/qmessagebox.h>
#include "../errors/RepoError.h"

void ModifyDialog::init() {
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

void ModifyDialog::modifica_oferta() {
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
			srv.modificare(oferta_de_modificat.get_id(), str_denumire, str_destinatie, str_tip, int_pret);
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

void ModifyDialog::connect_signals() {
	QObject::connect(btn_submit, &QPushButton::clicked, this, [this]() {
		modifica_oferta();
	});

	QObject::connect(btn_cancel, &QPushButton::clicked, this, [this]() {
		done(QDialog::Rejected);  // Exit from dialog.
	});
}

void ModifyDialog::setup_stare_initiala() {
	denumire->setText(QString::fromStdString(oferta_de_modificat.get_denumire()));
	destinatie->setText(QString::fromStdString(oferta_de_modificat.get_destinatie()));
	tip->setText(QString::fromStdString(oferta_de_modificat.get_tip()));
	pret->setText(QString::fromStdString(std::to_string(oferta_de_modificat.get_pret())));
}
