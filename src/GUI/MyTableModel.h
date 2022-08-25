#pragma once

#include <QAbstractTableModel>
#include <qfont.h>
#include <qbrush.h>
#include <vector>

#include "Domain.h"

#ifndef MYTABLEMODEL
#define MYTABLEMODEL

class MyTableModel : public QAbstractTableModel {
private:
	std::vector<Movie> movies;
public:
	MyTableModel(const std::vector < Movie >& movies);

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;

	int columnCount(const QModelIndex& parent = QModelIndex()) const override;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	void setMovie(const std::vector < Movie >& movies);

};


#endif