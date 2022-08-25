#include "ChangeMovieConsole.h"


void GuiChangeMovie::initialize_change_console() {
	dialog = new QDialog;

	QFormLayout* changeLayout = new QFormLayout;
	dialog->setLayout(changeLayout);

	old_titleEdit = new QLineEdit;
	old_genEdit = new QLineEdit;
	old_yearEdit = new QLineEdit;
	old_actorEdit = new QLineEdit;
	new_titleEdit = new QLineEdit;
	new_genEdit = new QLineEdit;
	new_yearEdit = new QLineEdit;
	new_actorEdit = new QLineEdit;

	changeLayout->addRow(old_title, old_titleEdit);
	changeLayout->addRow(old_gen, old_genEdit);
	changeLayout->addRow(old_year, old_yearEdit);
	changeLayout->addRow(old_actor, old_actorEdit);

	changeLayout->addRow(new_title, new_titleEdit);
	changeLayout->addRow(new_gen, new_genEdit);
	changeLayout->addRow(new_year, new_yearEdit);
	changeLayout->addRow(new_actor, new_actorEdit);

	changeButton = new QPushButton("Change movie");
	changeLayout->addWidget(changeButton);
}

void GuiChangeMovie::connect_signals() {
	QObject::connect(changeButton, &QPushButton::clicked, this, &GuiChangeMovie::change_movie);
	QObject::connect(changeButton, &QPushButton::clicked, dialog, &QDialog::close);
}

void GuiChangeMovie::change_movie() {
	try {
		std::string old_title = old_titleEdit->text().toStdString();
		std::string old_gen = old_genEdit->text().toStdString();
		std::string old_year = old_yearEdit->text().toStdString();
		std::string old_actor = old_actorEdit->text().toStdString();

		std::string new_title = new_titleEdit->text().toStdString();
		std::string new_gen = new_genEdit->text().toStdString();
		std::string new_year = new_yearEdit->text().toStdString();
		std::string new_actor = new_actorEdit->text().toStdString();

		srv.srv_change_movie(old_title, old_gen, old_year, old_actor, new_title, new_gen, new_year, new_actor);

		QMessageBox::information(dialog, "Info", QString::fromStdString("Successfully changed!"));


	}
	catch (InvalidMovie& error) {
		QMessageBox::warning(dialog, "Warning", QString::fromStdString(error.getMessage()));
	}
	catch (MovieInexistent& error) {
		QMessageBox::warning(dialog, "Warning", QString::fromStdString(error.getMessage()));
	}
	catch (MovieExistent& error) {
		QMessageBox::warning(dialog, "Warning", QString::fromStdString(error.getMessage()));
	}

}