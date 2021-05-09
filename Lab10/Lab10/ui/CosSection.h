#pragma once

#include "../service/ServiceOferta.h"
#include <Qwidget>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qformlayout.h>

/** Clasa pentru sectiunea de Cos. 
	Momentan contine doar Golire cos si Export
*/
class CosSection : public QWidget {
	Q_OBJECT

private:

	ServiceOferta& srv;

	// Layout principa vertical.
	QVBoxLayout* layout = new QVBoxLayout{ this };

	// Buton Golire cos.
	QPushButton* btn_golire_cos = new QPushButton{ "Golire Cos", this };

	// Text input si buton pentru Exportare.
	QHBoxLayout* export_layout = new QHBoxLayout{ this };
	QFormLayout* export_form_layout = new QFormLayout{ this };
	QLineEdit* export_file = new QLineEdit{ this };
	QPushButton* btn_export = new QPushButton{ "Export Cos", this };

	// Sectiunea de cos random.
	QPushButton* btn_random_cos = new QPushButton{ " Seed Cos Data ", this };

	/** Metoda de initializare a layout-urilor */
	void init();

	/** Metoda de initializare a semnalelor. */
	void connect_signals();
public:

	CosSection(ServiceOferta& service, QWidget* parent = (QWidget*) nullptr) : QWidget{ parent }, srv{service} {
		init();
		connect_signals();
	}
};