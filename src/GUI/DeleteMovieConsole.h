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


class GuiDeleteMovie : public QWidget {
private:
	Service& srv;

	QDialog* dialog;

	QPushButton* deleteButton;

	QLabel* title = new QLabel("Title: ");
	QLabel* gen = new QLabel("Gen: ");
	QLabel* year = new QLabel("Year: ");
	QLabel* actor = new QLabel("Actor: ");

	QLineEdit* titleEdit;
	QLineEdit* genEdit;
	QLineEdit* yearEdit;
	QLineEdit* actorEdit;

	/*
	 * Create the console for changing a movie
	 */
	void initialize_delete_console();

	/*
	 * Connect the signals of the buttons
	 */
	void connect_signals();

	/*
	 * Change the old movie to the new movie using srv
	 */
	void delete_movie();

public:
	GuiDeleteMovie() = delete;

	/*
	 * The constructor of the GuiChangeMovie object
	 */
	GuiDeleteMovie(Service& srv) :srv{ srv } {
		initialize_delete_console();
		connect_signals();
		dialog->exec();
	}
};