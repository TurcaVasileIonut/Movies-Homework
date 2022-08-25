#include "MyTableModel.h"


MyTableModel::MyTableModel(const std::vector < Movie >& movies) : movies{ movies } {
}

int MyTableModel::rowCount(const QModelIndex& parent) const{
	return 5000;	
}

int MyTableModel::columnCount(const QModelIndex& parent) const{
	return 4;
}

QVariant MyTableModel::data(const QModelIndex& index, int role) const{
	if (index.row() >= movies.size())
		return QVariant{};
	if (role == Qt::DisplayRole) {
		Movie movie = movies[index.row()];
		if (index.column() == 0) {
			return QString::fromStdString(movie.get_title());
		}
		else if (index.column() == 1) {
			return QString::fromStdString(movie.get_gen());
		}
		else if (index.column() == 2) {
			return QString::number(movie.get_year());
		}else
			return QString::fromStdString(movie.get_actor());
	}
	if (role == Qt::FontRole) {
		QFont f;
		f.setItalic(1);
		f.setBold(1);
		return f;
	}
	return QVariant{};
}

void MyTableModel::setMovie(const std::vector<Movie>& movies){
	this->movies = movies;
	auto topLeft = createIndex(0, 0);
	auto bottom = createIndex(movies.size(), columnCount());
	emit dataChanged(topLeft, bottom);
}
