#pragma once
#include <qwidget.h>
#include "Service.h"
#include "Observer.h"
#include <qtablewidget.h>
#include <qlistwidget.h>
#include <qboxlayout.h>
#include <qpushbutton.h>

class TableWindowOpen : public QWidget, public Observer {
private:

	Service& srv;
	string stare_cautata;

	// Reincarca lista de elemente.
	void reload_list(const std::vector<Task>& new_tasks);

	QVBoxLayout* layout = new QVBoxLayout{ this };

	// Pentru Tabel
	QListWidget* list = new QListWidget{ this };

	QPushButton* btn_open = new QPushButton{"Open", this};
	QPushButton* btn_inprogress = new QPushButton{"In Progress", this};
	QPushButton* btn_closed = new QPushButton{"Closed", this};

	// Intializeaza layout si starea componentelor.
	void init_state();

	// Conecteaza semnale
	void connect_signals();

	// Ia Id-ul elementului selectat sau display la eroare.
	int get_selected_id_or_error();

public:

	// COnstructor
	// Primeste un string.
	// Acel string este starea pe care o arata aceasta lista.
	TableWindowOpen(Service& srv, const string& stare) : srv{ srv }, stare_cautata{stare} {
		srv.addObserver(this);
		init_state();
		connect_signals();
	};

	// Notificarea.
	void notify() override {
		auto toate = srv.get_all();
		vector<Task> bune;
		for (const auto& el : toate)
			if (el.get_stare() == stare_cautata)
				bune.push_back(el);

		reload_list(bune);
	};

};
