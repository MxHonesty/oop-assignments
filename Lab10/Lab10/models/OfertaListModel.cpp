#include "OfertaListModel.h"
#include <iostream>
#include <QBrush>


int OfertaListModel::rowCount(const QModelIndex& parent) const {
	std::cout << parent.isValid();
	return static_cast<int>(elems.size());
}

int OfertaListModel::columnCount(const QModelIndex& parent) const {
	std::cout<<parent.isValid();
	return 4;
}

QVariant OfertaListModel::data(const QModelIndex& index, int role) const {
	int row = index.row();
	int column = index.column();
	if (role == Qt::DisplayRole) {
		switch (column) {
		case 0:
			return QString::fromStdString(elems.at(row).get_denumire());
			break;
		case 1:
			return QString::fromStdString(elems.at(row).get_destinatie());
			break;
		case 2:
			return QString::fromStdString(elems.at(row).get_tip());
			break;
		case 3:
			return QString::number(elems.at(row).get_pret());
			break;
		}
	}

	if (role == Qt::UserRole) {
		return QString::number(elems.at(row).get_id());
	}

	return QVariant();
}

void OfertaListModel::set_oferte(const std::vector<Oferta>& oferte) {
	elems = oferte;
	QModelIndex topLeft = createIndex(0, 0);
	QModelIndex bottomRight = createIndex(rowCount(), columnCount()); 
	emit dataChanged(topLeft, bottomRight);
	emit layoutChanged();
}
