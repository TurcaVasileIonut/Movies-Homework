#include "CartConsole.h"


void CartConsole::initialize_cart_console(){
	//The layout of the main window
	QHBoxLayout* main_layout = new QHBoxLayout;
	this->setLayout(main_layout);

	// The layout from the left
	QWidget* left_widget = new QWidget;
	QVBoxLayout* left_layout = new QVBoxLayout;
	left_widget->setLayout(left_layout);
	main_layout->addWidget(left_widget);

	left_layout->addWidget(create_add_form());

	left_layout->addWidget(create_generate_cart_form());

	left_layout->addWidget(create_export_cart_form());

	left_layout->addWidget(create_delete_all_form());

	left_layout->addWidget(create_draw_form());

	model = new MyTableModel(srv.get_all_from_cart());


	// The layout from the right
	QWidget* right_widget = new QWidget;
	QVBoxLayout* right_layout = new QVBoxLayout;
	right_widget->setLayout(right_layout);
	main_layout->addWidget(right_widget);

	right_layout->addWidget(create_table());

}

QTableView* CartConsole::create_table(){
	QTableView* table = new QTableView();
	table->horizontalHeader()->setStretchLastSection(true);
	table->setModel(model);
	return table;
}


QWidget* CartConsole::create_add_form(){
	QWidget* add_form = new QWidget;
	QFormLayout* form_layout = new QFormLayout;
	add_form->setLayout(form_layout);

	titleLabel = new QLabel{ "Title: " };
	titleEdit = new QLineEdit;

	form_layout->addRow(titleLabel, titleEdit);

	addMovie = new QPushButton("Search movie to add in cart");
	form_layout->addWidget(addMovie);


	return add_form;
}

QWidget* CartConsole::create_generate_cart_form(){
	QWidget* generate_widget = new QWidget;
	QFormLayout* generate_form = new QFormLayout;
	generate_widget->setLayout(generate_form);

	generateCartLabel = new QLabel("Number movies");
	generateCartEdit = new QLineEdit;
	generateCart = new QPushButton("Add random in cart");

	generate_form->addRow(generateCartLabel, generateCartEdit);
	generate_form->addWidget(generateCart);

	return generate_widget;
}

QWidget* CartConsole::create_export_cart_form(){
	QWidget* export_widget = new QWidget;
	QFormLayout* export_layout = new QFormLayout;
	export_widget->setLayout(export_layout);

	exportLabel = new QLabel("Filename");
	exportEdit = new QLineEdit;
	exportButton = new QPushButton("Export movies");

	export_layout->addRow(exportLabel, exportEdit);
	export_layout->addWidget(exportButton);

	return export_widget;
}

QWidget* CartConsole::create_delete_all_form() {
	QWidget* delete_widget = new QWidget;
	QFormLayout* delete_form = new QFormLayout;
	delete_widget->setLayout(delete_form);

	deleteAllMovies = new QPushButton("Empty cart");
	delete_form->addWidget(deleteAllMovies);

	return delete_widget;
}

QWidget* CartConsole::create_draw_form(){
	QWidget* draw_widget = new QWidget;
	QFormLayout* draw_form = new QFormLayout;
	draw_widget->setLayout(draw_form);

	drawCartContent = new QPushButton("Draw cart");
	draw_form->addWidget(drawCartContent);

	return draw_widget;
}

void CartConsole::update(){
	qDebug() << "Update called!\n";
	load_movies(srv.get_all_from_cart());
}

void CartConsole::connect_signals(){
	QObject::connect(addMovie, &QPushButton::clicked, this, &CartConsole::gui_add_movie);
	QObject::connect(generateCart, &QPushButton::clicked, this, &CartConsole::generate_random);
	QObject::connect(exportButton, &QPushButton::clicked, this, &CartConsole::export_movies);
	QObject::connect(deleteAllMovies, &QPushButton::clicked, this, &CartConsole::delete_movies);
	QObject::connect(drawCartContent, &QPushButton::clicked, [&]() {
			DrawCartGUI* drawner = new DrawCartGUI{ srv };
			drawner->show();
		});
}

void CartConsole::gui_add_movie(){
	try {
		std::string title = titleEdit->text().toStdString();
		GuiAddCart add_cart_dialog{ srv, title };
		cart.notify();
	}
	catch (MovieInexistent& error) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(error.getMessage()));
	}
	catch (InvalidMovie& error) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(error.getMessage()));
	}
}

void CartConsole::load_movies(std::vector<Movie> movies) {
	model->setMovie(movies);
}

void CartConsole::generate_random(){
	try {
		std::string number = generateCartEdit->text().toStdString();
		for (auto it : number) {
			if (it >= '0' && it <= '9') continue;
			std::string error = "Invalid input! ";
			throw error;
		}
		if(!number.size()){
			std::string error = "Invalid input! ";
			throw error;
		}
		srv.add_random_movies_in_cart(convert_string_to_number(number));
		QMessageBox::information(this, "Info", QString::fromStdString("Successfully added!"));
		load_movies(srv.get_all_from_cart());
	}
	catch (std::string error) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(error));
	}
	catch (MovieInexistent& error) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(error.getMessage()));
	}
	catch (MovieExistent& error) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(error.getMessage()));
	}
	catch (InvalidMovie& error) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(error.getMessage()));
	}
	catch (InsuficientMovies& error) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(error.getMessage()));
	}
}

void CartConsole::export_movies(){
	std::string filename = exportEdit->text().toStdString();
	srv.save_cart_in_csv(filename);
	QMessageBox::information(this, "Info", QString::fromStdString("Successfully exported!"));
}

void CartConsole::delete_movies(){
	srv.clear_cart();
	QMessageBox::information(this, "Info", QString::fromStdString("Successfully cleared!"));
	load_movies(srv.get_all_from_cart());
}

