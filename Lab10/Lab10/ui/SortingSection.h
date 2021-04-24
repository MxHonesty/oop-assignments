#pragma once

#include <QWidget>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qcheckbox.h>

// https://doc.qt.io/qt-5/signalsandslots.html
class SortingSection : public QWidget {
	Q_OBJECT

private:

	QPushButton* btn_pret = new QPushButton{"Sortare &Pret", this};  // Buton sortare pret.
	QPushButton* btn_denumire = new QPushButton{"Sortare &Denumire", this};  // Buton sortare denumire.
	QPushButton* btn_tip = new QPushButton{"Sortare &Tip", this};  // Buton sortare Tip.

	QCheckBox* este_descrescator = new QCheckBox{"&Descrescator", this};

	QVBoxLayout* layout = new QVBoxLayout{this};  // Layout vertical

	/** Functia de initializare a layout-ului */
	void init();

	/** Functia de gestiune a semnalelor. */
	void connect_signals();

public:

	SortingSection(QWidget* parent = (QWidget*)nullptr) : QWidget{ parent } {
		init();
		connect_signals();
	};

signals:
	/** Semnal emis cand sortam dupa pret. */
	void sortare_pret(const bool crescator);

	/** Semnal emis cand sortam dupa denumire. */
	void sortare_denumire(const bool crescator);

	/** Semnal emis cand sortam dupa tip. */
	void sortare_tip(const bool crescator);
};