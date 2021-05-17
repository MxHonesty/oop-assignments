#include "CosSection.h"
#include "../errors/FileError.h"
#include <QtWidgets/qmessagebox.h>

void CosSection::connect_signals() {
	QObject::connect(btn_golire_cos, &QPushButton::clicked, this, [this]() {
		srv.golire_cos();
	});

	QObject::connect(btn_export, &QPushButton::clicked, this, [this]() {
		std::string filename = export_file->text().toStdString();
		try {
			srv.export_html_cos_fancy(filename);
			QMessageBox::information(this, "Succes", "Fisierul a fost creat cu succes");
		}
		catch (const FileError& e) {
			QMessageBox::warning(this, "Warning", e.what());
		}
	});

	QObject::connect(btn_random_cos, &QPushButton::clicked, this, [this]() {
		const size_t nr_elemente = srv.get_ref_all().size();
		const int numar = rand() % nr_elemente + 1;  // luam un int intre 1 si nr elemente.
		srv.adauga_random_cos(numar);
	});

	QObject::connect(btn_meniu_cos_lista, &QPushButton::clicked, this, [this]() {
		CosCRUDGUI* lista_cos = new CosCRUDGUI{ srv };
		lista_cos->showNormal();
	});
}

void CosSection::init() {
	setLayout(layout);
	layout->addWidget(btn_golire_cos);
	layout->addLayout(export_layout);

	export_form_layout->addRow("Fisier", export_file);
	export_layout->addLayout(export_form_layout);
	export_layout->addWidget(btn_export);

	layout->addWidget(btn_random_cos);
	layout->addWidget(btn_meniu_cos_lista);
}