#include "DeleteMovieConsole.h"

void GuiDeleteMovie::initialize_delete_console(){
	dialog = new QDialog;

	QFormLayout* deleteLayout = new QFormLayout;
	dialog->setLayout(deleteLayout);

	titleEdit = new QLineEdit;
	genEdit = new QLineEdit;
	yearEdit = new QLineEdit;
	actorEdit = new QLineEdit;

	deleteLayout->addRow(title, titleEdit);
	deleteLayout->addRow(gen, genEdit);
	deleteLayout->addRow(year, yearEdit);
	deleteLayout->addRow(actor, actorEdit);

	deleteButton = new QPushButton("Delete movie");
	deleteLayout->addWidget(deleteButton);
}

void GuiDeleteMovie::connect_signals(){
	QObject::connect(deleteButton, &QPushButton::clicked, this, &GuiDeleteMovie::delete_movie);
	QObject::connect(deleteButton, &QPushButton::clicked, dialog, &QDialog::close);
}

void GuiDeleteMovie::delete_movie(){
	try{
		std::string title = titleEdit->text().toStdString();
		std::string gen = genEdit->text().toStdString();
		std::string year = yearEdit->text().toStdString();
		std::string actor = actorEdit->text().toStdString();

		qDebug() << QString::fromStdString(title) << " " << QString::fromStdString(gen) << " " << QString::fromStdString(year) << " " << QString::fromStdString(actor);

		srv.srv_delete_movie(title, gen, year, actor);

		QMessageBox::information(dialog, "Info", QString::fromStdString("Movie deleted!"));
	}
	catch (MovieInexistent& error) {
		QMessageBox::warning(dialog, "Warning", QString::fromStdString(error.getMessage()));
	}
	catch (MovieExistent& error) {
		QMessageBox::warning(dialog, "Warning", QString::fromStdString(error.getMessage()));
	}
	catch (InvalidMovie& error) {
		QMessageBox::warning(dialog, "Warning", QString::fromStdString(error.getMessage()));
	}
}
