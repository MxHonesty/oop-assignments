#pragma once
#include <QAbstractTableModel>
#include "Produs.h"
#include <vector>
#include "Service.h"

class ProdusModel : public QAbstractTableModel {
private:
	vector<Produs> elems;
	Service& srv;

public:
	ProdusModel(Service& srv, QObject* parent = (QObject*)nullptr) : 
		srv{ srv }, elems{ srv.get_all() }, QAbstractTableModel{parent} {};

	// Returneaza numarul de linii din view.
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;

	int columnCount(const QModelIndex& parent = QModelIndex()) const override;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	void set_produse(vector<Produs>& new_elems);
};
