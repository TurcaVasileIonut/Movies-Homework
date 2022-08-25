#pragma once

#include <vector>
#include "Domain.h"
#include "Service.h"

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


class GuiChangeMovie : public QWidget {
private:
	Service& srv;

	QDialog* dialog;

	QPushButton* changeButton;

	QLabel* old_title = new QLabel("Old title: ");
	QLabel* old_gen = new QLabel("Old gen: ");
	QLabel* old_year = new QLabel("Old year: ");
	QLabel* old_actor = new QLabel("Old actor: ");

	QLabel* new_title = new QLabel("New title: ");
	QLabel* new_gen = new QLabel("New gen: ");
	QLabel* new_year = new QLabel("New year: ");
	QLabel* new_actor = new QLabel("New actor: ");

	QLineEdit* new_titleEdit;
	QLineEdit* new_genEdit;
	QLineEdit* new_yearEdit;
	QLineEdit* new_actorEdit;

	QLineEdit* old_titleEdit;
	QLineEdit* old_genEdit;
	QLineEdit* old_yearEdit;
	QLineEdit* old_actorEdit;

	/*
	 * Create the console for changing a movie
	 */
	void initialize_change_console();

	/*
	 * Connect the signals of the buttons
	 */
	void connect_signals();

	/*
	 * Change the old movie to the new movie using srv
	 */
	void change_movie();

public:
	GuiChangeMovie() = delete;

	/*
	 * The constructor of the GuiChangeMovie object
	 */
	GuiChangeMovie(Service& srv) :srv{ srv } {
		initialize_change_console();
		connect_signals();
		dialog->exec();
	}
};