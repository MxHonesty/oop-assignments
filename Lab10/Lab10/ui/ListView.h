#pragma once
#include <QWidget>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qmessagebox.h>

#include "../service/ServiceOferta.h"

class ListView : public QWidget {
	Q_OBJECT
private:
	ServiceOferta& srv;

	QVBoxLayout* layout = new QVBoxLayout(this);  // The Box layout
	QPushButton* btn_remove = new QPushButton("&Remove", this);  // Buton de remove
	QListWidget* list = new QListWidget(this);  // Lista

	void init_ListView();
	void connect_signals();
	void reload_list(const std::vector<Oferta>& oferte);
	void add_oferta();

public:

	/** Constructor */
	ListView(ServiceOferta& service) : srv{ service } {
		init_ListView();
		connect_signals();
		reload_list(srv.get_all());
	};

};
