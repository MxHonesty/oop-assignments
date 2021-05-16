#pragma once
#include <qwidget.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>

class List : public QWidget{
private:

	QVBoxLayout* layout = new QVBoxLayout{ this };
	QPushButton* btn = new QPushButton{ "Press", this };
	QFormLayout* form = new QFormLayout{ this };
	QLineEdit* line = new QLineEdit{ "Line", this };


	void init_layout();
	void connect_signals();
	void init_state();
public:

	List(QWidget* parent = (QWidget*) nullptr) : QWidget{ parent } {
		init_layout();
		connect_signals();
		init_state();
	};
};

