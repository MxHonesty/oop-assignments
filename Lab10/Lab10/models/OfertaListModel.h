#pragma once

#include <QAbstractTableModel>
#include "../domain/oferta.h"
#include <vector>


class OfertaListModel : public QAbstractTableModel {
private:	
	std::vector<Oferta> elems;

public:
	// Constructor
	OfertaListModel(const std::vector<Oferta>& oferte, QObject* parent = (QObject*)nullptr) :
		QAbstractTableModel{ parent }, elems{oferte}{};

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;

	int columnCount(const QModelIndex& parent = QModelIndex()) const override;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	/** Updateaza lista de oferte */
	void set_oferte(const std::vector<Oferta>& oferte);
};
