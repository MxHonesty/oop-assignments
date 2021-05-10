#pragma once

#include <QtWidgets/qdialog.h>
#include <qformlayout.h>
#include <qlineedit.h>
#include <QtWidgets/qpushbutton.h>

#include "../service/ServiceOferta.h"

/** Dialog pentru introducerea unui element in
	registru.

	Signals:
		accepted: Executat atunci cand adaugarea a fost
				  efectuata cu succes. Daca inputul nu este
				  valid atunci se deschide o noua pagina
				  de warning cu specificarea problemei.
*/
class InfoDialog : public QDialog {
private:

	Oferta oferta;

	QLineEdit* denumire = new QLineEdit{ this };
	QLineEdit* destinatie = new QLineEdit{ this };
	QLineEdit* tip = new QLineEdit{ this };
	QLineEdit* pret = new QLineEdit{ this };

	QVBoxLayout* main_layout = new QVBoxLayout{};
	QFormLayout* denumire_layout = new QFormLayout();
	QFormLayout* destinatie_layout = new QFormLayout();
	QFormLayout* tip_layout = new QFormLayout();
	QFormLayout* pret_layout = new QFormLayout();

	QPushButton* btn_submit = new QPushButton{ "&Done" };

	/** Seteaza starea initiala a layout-ului. */
	void init();

	/** Set-up pentru semnale */
	void connect_signals();

	/** Adds the initial data. */
	void setup_initial_state();
public:

	/** Constructor */
	InfoDialog(const Oferta& of, const bool modal = true, QWidget* parent = (QWidget*)nullptr) :
		QDialog{ parent }, oferta{ of } {
		setModal(modal);
		init();
		connect_signals();
		setup_initial_state();
	};

};