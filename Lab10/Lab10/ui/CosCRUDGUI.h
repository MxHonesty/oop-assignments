#pragma once
#include <qwidget.h>
#include <vector>
#include "../domain/oferta.h"
#include "../service/ServiceOferta.h"
#include "../observer/observer.h"

#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>

class CosCRUDGUI : public QWidget, public Observer {
private:
	ServiceOferta& srv;

	QListWidget* list = new QListWidget{ this };
	QPushButton* btn_golire = new QPushButton{ "Golire", this };
	QPushButton* btn_random = new QPushButton{ "Random 3", this };
	QVBoxLayout* layout = new QVBoxLayout{ this };

	/** Init la layout. */
	void init_layout();

	/** Conectare semnale */
	void connect_signals();

	/** Starea initiala a listei. */
	void init_state();

	/** Reincarca elementele in lista. */
	void reload_list(const std::vector<Oferta>& elems);

public:
	
	CosCRUDGUI(ServiceOferta& service, QWidget* parent = (QWidget*)nullptr) : QWidget{ parent }, srv{service} {
		init_layout();
		connect_signals();
		init_state();
		srv.add_observer_to_cos(this);
		QWidget::setAttribute(Qt::WA_DeleteOnClose, true);
	};

	/** Apelata cand se modifica lista de cosuri. */
	void update() override;

	/** Dezabonam de la Observable */
	~CosCRUDGUI() {
		srv.remove_observer_from_cos(this);
	}
	
};
