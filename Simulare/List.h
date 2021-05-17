#pragma once

#include <qwidget.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qpushbutton.h>
#include "Service.h"
#include "Produs.h"
#include <vector>


class List : public QWidget {
private:

	Service srv;

	QListWidget* list = new QListWidget{ this };
	QVBoxLayout* layout = new QVBoxLayout{ this };
	QLineEdit* cap = new QLineEdit{ "Cap" };

	QPushButton* sort1 = new QPushButton{ "Sortare Stoc" };
	QPushButton* sort2 = new QPushButton{ "Sortare Tip" };

	void init();
	void connect_signals();
	void reload_list(std::vector<Produs> items);
public:

	List(QWidget* parent = (QWidget*) nullptr) : QWidget{ parent }, srv{} {
		init();
		connect_signals();
		reload_list(srv.get_all());
	}

};
