#pragma once
#include <QAbstractTableModel>
#include "Product.h"
class TableModel : public QAbstractTableModel {
public:
	std::vector<Product> prds;
	TableModel(const std::vector<Product>& prds) : prds{ prds } {};
	/**
	* number of rows
	*/
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	/**
	* number of columns
	*/
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	/**
	* Value at a given position
	*/
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	void setProducts(const std::vector<Product>& prds2);
};