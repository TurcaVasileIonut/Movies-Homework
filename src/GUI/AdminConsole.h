#pragma once

#include <vector>
#include "Domain.h"
#include "Service.h"
#include "CartConsole.h"
#include "ChangeMovieConsole.h"
#include "DeleteMovieConsole.h"

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


class AdminConsole : public QWidget {
private:
	Service& srv;

	QLabel* titleLabel = new QLabel{ "Title: " };
	QLabel* genLabel = new QLabel{ "Gen: " };
	QLabel* yearLabel = new QLabel{ "Year: " };
	QLabel* actorLabel = new QLabel{ "Actor: " };

	QRadioButton* radioSrtTitle = new QRadioButton(QString::fromStdString("Title"));
	QRadioButton* radioSrtActor = new QRadioButton(QString::fromStdString("Actor"));
	QRadioButton* radioSrtYearGen = new QRadioButton(QString::fromStdString("Year + gen"));

	QLineEdit* titleEdit;
	QLineEdit* genEdit;
	QLineEdit* yearEdit;
	QLineEdit* actorEdit;

	QLineEdit* editFilterTitle;
	QLineEdit* editFilterYear;

	QPushButton* addButton;

	QPushButton* changeMovieButton;
	QPushButton* deleteMovieButton;

	QPushButton* filterTitleButton;
	QPushButton* filterYearButton;

	QPushButton* sortButton;

	QPushButton* resetDisplayButton;
	QPushButton* undoButton;

	QPushButton* cartButton;

	QTableWidget* table;

	/*
	 * Create all components from the admin console
	 */
	void intialize_admin_console();

	/*
	 *Create a form that will take a movie from user
	 */
	QWidget* create_add_form();

	/*
	 *Create a form that will manage all changes from the movie repo
	 */
	QWidget* create_change_form();

	/*
	 *Create a group that will manage filter by title
	 */
	QGroupBox* create_filter_by_title();

	/*
	 * Create a group that manage filter by year 
	 */
	QGroupBox* create_filter_by_year();

	/*
	 * Create a group that will manage sorting
	 */
	QGroupBox* create_sorting_group();

	/*
	 * Create the table where will be all movies from repo
	 */
	QWidget* create_right_table();

	/*
	 * Load all movies from file in repo in the console table
	 */
	void load_movies(std::vector < Movie > movies);

	/*
	 * Connect the buttons to signals
	 */
	void connect_signals();


public:

	AdminConsole() = delete;
	/*
	 * Constructor for the AdminConsole
	 */
	AdminConsole(Service& srv) : srv{ srv } {
		intialize_admin_console();
		load_movies(srv.get_all_from_repo());
		connect_signals();
	};

	/*
	* Add a new movie in list
	*/
	void gui_add_movie();

	/*
	* Open the window for change movie
	*/
	void gui_change_movie();

	/*
	* Open the window for delete movie
	*/
	void gui_delete_movie();

};
