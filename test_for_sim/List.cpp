#include "List.h"
#include <QtWidgets/qmessagebox.h>

void List::init_layout() {
	setLayout(layout);
	layout->addWidget(btn);
	layout->addLayout(form);
	form->addRow("Line", line);
}

void List::connect_signals() {
	QObject::connect(btn, &QPushButton::clicked, this, [this]() {
		QMessageBox::information(this, "TITLU?", "SALUT");
	});
}

void List::init_state() {
	line->setText("Default");
}
