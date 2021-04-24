#pragma once
#include <QWidget>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qmessagebox.h>

#include "AddDialog.h"
#include "InfoDialog.h"
#include "ModifyDialog.h"
#include "SortingSection.h"

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

	QHBoxLayout* main_layout = new QHBoxLayout(this);  // Main layout

	QVBoxLayout* list_layout = new QVBoxLayout(this);  // Layout of the list-proper
	QListWidget* list = new QListWidget(this);  // Lista

	QPushButton* btn_remove = new QPushButton("&Remove", this);  // Buton de Stergere
	QPushButton* btn_add = new QPushButton("&Add", this);  // Buton de Adaugare
	QPushButton* btn_modify = new QPushButton("&Modify", this);  // Buton de Modificare
	QPushButton* btn_info = new QPushButton("&Info", this);  // Buton de informatii
	QPushButton* btn_undo = new QPushButton("&Undo", this);  // Buton de undo

	QHBoxLayout* button_layout = new QHBoxLayout(this);  // Layout pentru butoane.

	SortingSection* sorting = new SortingSection{ this };

	/** Initializeaza layout ListView */
	void init_ListView();

	/** Conecteaza signals pentru componente. */
	void connect_signals();

	/** Conecteazs semnalele de la seciunea de sortare. */
	void connect_sorting_signals();

	/** Reincarca elementele in lista. */
	void reload_list(const std::vector<Oferta>& oferte);

	/** Elimina oferta selectata actual.
		Daca nicio oferta nu este selectata, arata un warning.
	*/
	void remove_oferta_selectata();

	/** Functia introduce Dialogul de adaugare
		pentru datele de add.
	*/
	void start_add_menu();

	/** Porneste Dialogul de modificare pentru
		Oferta selectata.
	*/
	void start_modify_menu();

	/** Dialogul de informatii despre oferta curenta. */
	void start_info_menu();

	/** Executa functionalitatea de undo asupra listei. */
	void undo();

public:

	/** Constructor */
	ListView(ServiceOferta& service) : srv{ service } {
		init_ListView();
		connect_signals();
		connect_sorting_signals();  // Semnale pentru sortare.
		reload_list(srv.get_ref_all());
	};

};
