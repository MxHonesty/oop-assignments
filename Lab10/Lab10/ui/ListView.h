#pragma once
#include <QWidget>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qtablewidget.h>

#include "AddDialog.h"
#include "InfoDialog.h"
#include "ModifyDialog.h"
#include "SortingSection.h"
#include "FilterSection.h"

#include "../service/ServiceOferta.h"
#include "CosSection.h"

/**
	Componenta ListView:
	Pastreaza referinta la srv si opereaza pe lista de elemente.
	Reprezinta compneneta basic pentru vizualizarea si lucrul
	asupra registrului de elemente.
*/
class ListView : public QWidget {
private:
	ServiceOferta& srv;

	int selected_row;

	QHBoxLayout* main_layout = new QHBoxLayout(this);  // Main layout

	QVBoxLayout* list_layout = new QVBoxLayout(this);  // Layout of the list-proper
	QListWidget* list = new QListWidget(this);  // Lista
	QTableWidget* table = new QTableWidget{ this };  // Tabel

	QPushButton* btn_remove = new QPushButton("&Remove", this);  // Buton de Stergere
	QPushButton* btn_add = new QPushButton("&Add", this);  // Buton de Adaugare
	QPushButton* btn_modify = new QPushButton("&Modify", this);  // Buton de Modificare
	QPushButton* btn_info = new QPushButton("&Info", this);  // Buton de informatii
	QPushButton* btn_undo = new QPushButton("&Undo", this);  // Buton de undo
	QPushButton* btn_refresh = new QPushButton("Refresh", this);  // Buton de refresh

	QHBoxLayout* button_layout = new QHBoxLayout(this);  // Layout pentru butoane.

	QHBoxLayout* cos_button_layout = new QHBoxLayout{ this };
	QPushButton* btn_cos_adauga = new QPushButton{ "Adauga in Cos", this };
	QPushButton* btn_cos_elimina = new QPushButton{ "Elimina din Cos", this };


	QHBoxLayout* sections_layout = new QHBoxLayout{ this };
	SortingSection* sorting = new SortingSection{ this };
	FilterSection* filtering = new FilterSection{ this };
	CosSection* cosing = new CosSection{ srv, this };


	/** Initializeaza layout ListView */
	void init_ListView();

	/** Conecteaza signals pentru componente. */
	void connect_signals();

	/** Conecteazs semnalele de la seciunea de sortare. */
	void connect_sorting_signals();

	/** Conecteaza semnalele de la seciunea de filtrare */
	void connect_filtering_signals();

	/** Reincarca elementele in lista. */
	void reload_list(const std::vector<Oferta>& oferte);

	/** Reincarca elementele in tabel. */
	void reload_table(const std::vector<Oferta>& oferte);

	/** Reincarca tabelul si lista. */
	void reload(const std::vector<Oferta>& oferte);

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
	ListView(ServiceOferta& service) : srv{ service }, selected_row{-1} {
		init_ListView();
		connect_signals();
		connect_sorting_signals();  // Semnale pentru sortare.
		connect_filtering_signals();
		reload(srv.get_ref_all());
	};

};
