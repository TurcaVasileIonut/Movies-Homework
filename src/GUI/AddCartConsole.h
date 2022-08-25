#pragma once

#include <QPushButton>
#include <QtWidgets/QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include <QtWidgets/QTableWidget>
#include <QMessageBox>
#include <QHeaderView>
#include <QDialog>
#include <QRadioButton>
#include <QGroupBox>

#include "Domain.h"
#include "Service.h"


class GuiAddCart: public QWidget{
private:
	Service& srv;

	QDialog* main_dialog;
	QVBoxLayout* main_layout;
	QPushButton* addMovie;

	std::vector<QRadioButton*> radioButtons;
	std::vector<Movie>movies;

	/*
	 * Initialize the console
	 */
	void initialize_console();

	/*
	 * Load all movies with chosen title in the table
	 */
	void load_movies(std::vector < Movie > movies);

	/*
	 * Connect the signal of the button
	 */
	void connect_signals();

public:
	GuiAddCart() = delete;

	/*
	 * Constructor for AddCart console
	 */
	GuiAddCart(Service& srv, std::string& title) :srv{ srv }{
		initialize_console();
		movies = srv.filter_by_title(title);
		load_movies(movies);
		connect_signals();
		main_dialog->exec();
	};
};