#pragma once

#include <Qwidget>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlineedit.h>

/** Clasa pentru seciunea din meniu care gestioneaza operatiunile de filtrare. */
class FilterSection : public QWidget {
	Q_OBJECT

private:
	QVBoxLayout* layout = new QVBoxLayout{ this };
	
	QHBoxLayout* destinatie_layout = new QHBoxLayout();
	QLineEdit* destinatie = new QLineEdit{ this };
	QPushButton* btn_filtrare_destinatie = new QPushButton{ "Filtrare Destinatie", this };

	QVBoxLayout* pret_layout_input = new QVBoxLayout{ this };
	QFormLayout* pret_min_layout = new QFormLayout{ this };  // form layout min
	QFormLayout* pret_max_layout = new QFormLayout{ this };  // form layout max
	QLineEdit* pret_min = new QLineEdit{ this };
	QLineEdit* pret_max = new QLineEdit{ this };

	QFormLayout* pret_button_layout = new QFormLayout{ this };  // form layout max
	QPushButton* btn_filtrare_pret = new QPushButton{ "Filtrare Pret", this };

	/** Functie de initializare layout */
	void init();

	/** Functia de gestiune a semnallor. */
	void connect_signals();

public:

	/** Constructor pentru Sectiunea de filtru. */
	FilterSection(QWidget* parent = (QWidget*) nullptr) : QWidget{ parent } {
		init();
		connect_signals();
	};

signals:

	/** Semnal de filtrare destinatie */
	void filtrare_destinatie(std::string destinatie);

	/** Semnal de filtrare pret. */
	void filtrare_pret(int min, int max);
};
