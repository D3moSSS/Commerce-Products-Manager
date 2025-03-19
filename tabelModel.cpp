#include "tableModel.h"

int TableModel::rowCount(const QModelIndex&) const {
	return (int)prds.size();
}

int TableModel::columnCount(const QModelIndex&) const {
	return 4;
}

QVariant TableModel::data(const QModelIndex& index, int role) const {
	if (role == Qt::DisplayRole) {
		auto prd = prds[index.row()];
		if (index.column() == 0)
			return QString(QString::fromStdString(prd.getName()));
		else if (index.column() == 1)
			return QString(QString::fromStdString(prd.getProducer()));
		else if (index.column() == 2)
			return QString(QString::fromStdString(prd.getType()));
		else if (index.column() == 3)
			return QString(QString::fromStdString(std::to_string(prd.getPrice())));
	}
	return QVariant();
}

void TableModel::setProducts(const std::vector<Product>& prds2) {
	this->prds = prds2;
	auto topLeft = createIndex(0, 0);
	auto bottomRight = createIndex(rowCount(), columnCount());
	emit dataChanged(topLeft, bottomRight);
	emit layoutChanged();
}