#pragma once

#include <qwidget.h>
#include <vector>
#include "../domain/oferta.h"
#include "../service/ServiceOferta.h"
#include "../observer/observer.h"

#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>


class CosV2CrudGUI : public QWidget, public Observer {
private:
	ServiceOferta& srv;

	QTableWidget* table = new QTableWidget{ this };
	QPushButton* btn_golire = new QPushButton{ "Golire", this };
	QPushButton* btn_random = new QPushButton{ "Random 3", this };
	QVBoxLayout* layout = new QVBoxLayout{ this };

	/** Initializeaza layout */
	void init_layout();

	/** Conectare semnale */
	void connect_signals();
	
	/** Seteaza starea initiala a componentelor */
	void init_state();

	void reload_list(const std::vector<Oferta>& elems);

public:
	CosV2CrudGUI(ServiceOferta& service, QWidget* parent = (QWidget*)nullptr) : QWidget{ parent }, srv{ service } {
		init_layout();
		connect_signals();
		init_state();
		srv.add_observer_to_cos(this);
		QWidget::setAttribute(Qt::WA_DeleteOnClose, true);
	};

	/** Apelata cand se modifica lista de cosuri. */
	void update() override;

	/** Dezabonam de la Observable */
	~CosV2CrudGUI() {
		srv.remove_observer_from_cos(this);
	}
};
