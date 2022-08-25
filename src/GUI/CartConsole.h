#pragma once

#include <QPushButton>
#include <QRadioButton>
#include <QGroupBox>
#include <QtWidgets/QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include <QtWidgets/QTableWidget>
#include <QMessageBox>
#include <QHeaderView>
#include <QDialog>
#include <qtableview.h>

#include "MyTableModel.h"

#include "DrawCart.h"
#include "Service.h"
#include "AddCartConsole.h"
#include "Utils.h"

class CartConsole: public QWidget, public Observer{
private:
	Service& srv;
	CartMovies& cart;

	QLabel* titleLabel;
	QLineEdit* titleEdit;
	QPushButton* addMovie;

	QLabel* generateCartLabel;
	QLineEdit* generateCartEdit;
	QPushButton* generateCart;

	QLabel* exportLabel;
	QLineEdit* exportEdit;
	QPushButton* exportButton;

	QPushButton* deleteAllMovies;

	//QTableWidget* cartContentTable;

	QPushButton* drawCartContent;

	MyTableModel* model;

	void update() override;

	/*
	 * Create the console of the cart
	 */
	void initialize_cart_console();

	/*
	 * Return a table with 8 lines and 4 columns
	 */
	QTableView* create_table();

	/*
	 * Create the form where you add a movie in cart
	 */
	QWidget* create_add_form();

	/*
	 * Create the form that take a number n from user and add n random movies in cart
	 */
	QWidget* create_generate_cart_form();

	/*
	 * Create the form that take a filename from user and export all movies from cart
	 */
	QWidget* create_export_cart_form();

	/*
	 * Create the form that delete all movies from cart
	 */
	QWidget* create_delete_all_form();

	/*
	* Create the form that will open the drawing gui
	*/
	QWidget* create_draw_form();

	/*
	 * Connect all signals of the buttons
	 */
	void connect_signals();

	/*
	 * Load all movie from cart into the table
	 */
	void load_movies(std::vector<Movie> movies);

public:
	CartConsole() = delete;

	/*
	 * Constructor for the cart console
	 */
	CartConsole(Service& srv) : srv{ srv }, cart{ srv.get_cart() }{
		qDebug() << "The cart is " << &cart << "\n";
		initialize_cart_console();
		load_movies(srv.get_all_from_cart());
		connect_signals();
		cart.addObserver(this);
	};

	/*
	 * Start the console that has a table with all movies with chosen title
	 */
	void gui_add_movie();

	/*
	 * Take the number of movies from cart and add random movies in cart
	 */
	void generate_random();

	/*
	 * Take the filename name and export the movies
	 */
	void export_movies();

	/*
	 * Delete all movies from cart
	 */
	void delete_movies();
};