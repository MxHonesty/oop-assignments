#pragma once
#include <QWidget>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qmessagebox.h>

#include "../service/ServiceOferta.h"

/**
	Componenta ListView:
	Pastreaza referinta la srv si opereaza pe lista de elemente.
	Reprezinta compneneta basic pentru vizualizarea si lucrul
	asupra registrului de elemente.
*/
class ListView : public QWidget {
private:
	ServiceOferta& srv;

	QVBoxLayout* layout = new QVBoxLayout(this);  // The Box layout
	QPushButton* btn_remove = new QPushButton("&Remove", this);  // Buton de remove
	QListWidget* list = new QListWidget(this);  // Lista

	/** Initializeaza layout ListView */
	void init_ListView();

	/** Conecteaza signals pentru componente. */
	void connect_signals();

	/** Reincarca elementele in lista. */
	void reload_list(const std::vector<Oferta>& oferte);

	/** Adauga oferta. */
	void add_oferta();

	/** Elimina oferta selectata actual.
		Daca nicio oferta nu este selectata, arata un warning.
	*/
	void remove_oferta_selectata();

public:

	/** Constructor */
	ListView(ServiceOferta& service) : srv{ service } {
		init_ListView();
		connect_signals();
		reload_list(srv.get_ref_all());
	};

};
