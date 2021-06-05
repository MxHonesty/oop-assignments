#include "ProdusModel.h"
#include <qbrush.h>

int ProdusModel::rowCount(const QModelIndex& parent) const {
	return static_cast<int>(elems.size());
}

int ProdusModel::columnCount(const QModelIndex& parent) const {
	return 5;
}

QVariant ProdusModel::data(const QModelIndex& index, int role) const {
	int row = index.row();
	int column = index.column();
	if (role == Qt::DisplayRole) {
		switch (column) {
		case 0:
			return QString::fromStdString(elems.at(row).get_denumire());
			break;

		case 1:
			return QString::fromStdString(elems.at(row).get_tip());
			break;

		case 2:
			return QString::number(elems.at(row).get_id());
			break;

		case 3:
			return QString::number(elems.at(row).get_ca());
			break;

		case 4:
			return QString::number(elems.at(row).get_cn());
			break;
		}
	}

	if (role == Qt::UserRole) {
		return QString::number(elems.at(row).get_id());
	}

	if (role == Qt::BackgroundRole) {
		// Deteminam daca elementul are proprietatea pentru colorare in rosu
		if (srv.este_nevoie(elems.at(row).get_id())) {
			QBrush bg{Qt::red};
			return bg;
		}
	}
	
	
	return QVariant{};
}

void ProdusModel::set_produse(vector<Produs>& new_elems) {
	elems = new_elems;
	QModelIndex topLeft = createIndex(0, 0);
	QModelIndex bottomRight = createIndex(rowCount(), columnCount());
	emit dataChanged(topLeft, bottomRight);
	emit layoutChanged();
}
