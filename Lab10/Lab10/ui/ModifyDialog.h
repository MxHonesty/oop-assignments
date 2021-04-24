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
class ModifyDialog : public QDialog {
private:

	ServiceOferta& srv;
	Oferta oferta_de_modificat;

	QLineEdit* denumire = new QLineEdit{ this };
	QLineEdit* destinatie = new QLineEdit{ this };
	QLineEdit* tip = new QLineEdit{ this };
	QLineEdit* pret = new QLineEdit{ this };

	QVBoxLayout* main_layout = new QVBoxLayout{};
	QFormLayout* denumire_layout = new QFormLayout();
	QFormLayout* destinatie_layout = new QFormLayout();
	QFormLayout* tip_layout = new QFormLayout();
	QFormLayout* pret_layout = new QFormLayout();

	QPushButton* btn_submit = new QPushButton{ "&Submit" };
	QPushButton* btn_cancel = new QPushButton{ "&Cancel" };

	/** Seteaza starea initiala a layout-ului. */
	void init();

	/** Modifica oferta data cu cea citita.
		Inchide executia cu accepted daca inputul a fost validat si valoarea
		a fost introdusa.
		Inchide cu rejected daca elementul nu a fost valid.
	*/
	void modifica_oferta();

	/** Set-up pentru semnale */
	void connect_signals();

	void setup_stare_initiala();
public:

	/** Constructor */
	ModifyDialog(ServiceOferta& service, const Oferta& modificat, QWidget* parent = (QWidget*)nullptr) :
		QDialog{ parent }, srv{ service }, oferta_de_modificat{modificat} {
		init();
		connect_signals();
		setup_stare_initiala();
	};

};