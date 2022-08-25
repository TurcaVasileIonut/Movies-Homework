#include "AdminConsole.h"
#include "AdminConsole.h"


void AdminConsole::intialize_admin_console() {

	//The layout of the main window
	QHBoxLayout* MainLayout = new QHBoxLayout;
	this->setLayout(MainLayout);
	
	//The layout from the left
	QWidget* left_widget = new QWidget;
	QVBoxLayout* left_layout = new QVBoxLayout;
	left_widget->setLayout(left_layout);
	MainLayout->addWidget(left_widget);

	QWidget* addingForm = create_add_form();
	left_layout->addWidget(addingForm);

	QWidget* changeForm = create_change_form();
	left_layout->addWidget(changeForm);

	// The layout from the right
	QWidget* right_widget = create_right_table();
	MainLayout->addWidget(right_widget);

	QGroupBox* filterTitleGroup = create_filter_by_title();

	QGroupBox* filterYearGroup = create_filter_by_year();

	left_layout->addWidget(filterTitleGroup);
	left_layout->addWidget(filterYearGroup);

	QGroupBox* sortingGroup = create_sorting_group();

	left_layout->addWidget(sortingGroup);

	resetDisplayButton = new QPushButton("Reset displayed movies");
	left_layout->addWidget(resetDisplayButton);

	undoButton = new QPushButton("Undo");
	left_layout->addWidget(undoButton);

	cartButton = new QPushButton("Make cart");
	left_layout->addWidget(cartButton);

}

QWidget* AdminConsole::create_add_form(){
	QWidget* addingForm = new QWidget;
	QFormLayout* layoutAddingForm = new QFormLayout;
	addingForm->setLayout(layoutAddingForm);

	titleEdit = new QLineEdit;
	genEdit = new QLineEdit;
	yearEdit = new QLineEdit;
	actorEdit = new QLineEdit;

	layoutAddingForm->addRow(titleLabel, titleEdit);
	layoutAddingForm->addRow(genLabel, genEdit);
	layoutAddingForm->addRow(yearLabel, yearEdit);
	layoutAddingForm->addRow(actorLabel, actorEdit);

	addButton = new QPushButton("Add movie");
	layoutAddingForm->addWidget(addButton);

	return addingForm;
}

QWidget* AdminConsole::create_change_form(){
	QWidget* changeForm = new QWidget;
	QHBoxLayout* layoutChangeForm = new QHBoxLayout;
	changeForm->setLayout(layoutChangeForm);

	changeMovieButton = new QPushButton("Change movie");
	layoutChangeForm->addWidget(changeMovieButton);

	deleteMovieButton = new QPushButton("Delete movie");
	layoutChangeForm->addWidget(deleteMovieButton);

	return changeForm;
}

QGroupBox* AdminConsole::create_filter_by_title(){
	QGroupBox* filterGroup = new QGroupBox(tr("Filter by title"));
	QFormLayout* group_layout = new QFormLayout;
	filterGroup->setLayout(group_layout);
	editFilterTitle = new QLineEdit();
	QLabel* labelFilter = new QLabel("Title ");

	filterTitleButton = new QPushButton("Filter Movies");
	group_layout->addRow(labelFilter, editFilterTitle);
	group_layout->addWidget(filterTitleButton);

	return filterGroup;
}

QGroupBox* AdminConsole::create_filter_by_year(){
	QGroupBox* filterGroup = new QGroupBox(tr("Filter by year"));
	QFormLayout* group_layout = new QFormLayout;
	filterGroup->setLayout(group_layout);
	editFilterYear = new QLineEdit();
	QLabel* labelFilter = new QLabel("Year ");

	filterYearButton = new QPushButton("Filter Movies");
	group_layout->addRow(labelFilter, editFilterYear);
	group_layout->addWidget(filterYearButton);

	return filterGroup;
}

QGroupBox* AdminConsole::create_sorting_group(){
	QGroupBox* group = new QGroupBox(tr("Sort"));
	QFormLayout* group_layout = new QFormLayout;
	group->setLayout(group_layout);

	group_layout->addWidget(radioSrtTitle);
	group_layout->addWidget(radioSrtActor);
	group_layout->addWidget(radioSrtYearGen);

	sortButton = new QPushButton("Sort");
	group_layout->addWidget(sortButton);

	return group;

}

QWidget* AdminConsole::create_right_table(){
	QWidget* right_widget = new QWidget;
	QVBoxLayout* right_layout = new QVBoxLayout;
	right_widget->setLayout(right_layout);

	int noLines = 8;
	int noColumns = 4;
	this->table = new QTableWidget{ noLines, noColumns };

	QStringList tableHeader;
	tableHeader << "Title" << "Gen" << "Year" << "Actor";
	this->table->setHorizontalHeaderLabels(tableHeader);
	this->table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	right_layout->addWidget(this->table);

	this->table->setSelectionBehavior(
		QAbstractItemView::SelectRows);
	this->table->setSelectionMode(
		QAbstractItemView::SingleSelection);

	return right_widget;
}


void AdminConsole::load_movies(std::vector<Movie> movies){
	this->table->clearContents();
	this->table->setRowCount(movies.size());

	int lineNumber = 0;
	for(auto& movie : movies){
		this->table->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(movie.get_title())));
		this->table->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(movie.get_gen())));
		this->table->setItem(lineNumber, 2, new QTableWidgetItem(QString::number(movie.get_year())));
		this->table->setItem(lineNumber, 3, new QTableWidgetItem(QString::fromStdString(movie.get_actor())));
		lineNumber++;
	}
}

void AdminConsole::connect_signals(){
	QObject::connect(addButton, &QPushButton::clicked, this, &AdminConsole::gui_add_movie);
	QObject::connect(changeMovieButton, &QPushButton::clicked, this, &AdminConsole::gui_change_movie);
	QObject::connect(deleteMovieButton, &QPushButton::clicked, this, &AdminConsole::gui_delete_movie);
	QObject::connect(filterTitleButton, &QPushButton::clicked, [&]()
	{
		std::string title = editFilterTitle->text().toStdString();
		load_movies(srv.filter_by_title(title));
	});
	QObject::connect(filterYearButton, &QPushButton::clicked, [&]()
	{
		std::string year = editFilterYear->text().toStdString();
		load_movies(srv.filter_by_year(year));
	});
	QObject::connect(resetDisplayButton, &QPushButton::clicked, [&]() {
		load_movies(srv.get_all_from_repo());
	});
	QObject::connect(sortButton, &QPushButton::clicked, [&](){
		if (radioSrtTitle->isChecked())
			load_movies(srv.sorting(1));
		else
			if (radioSrtActor->isChecked())
				load_movies(srv.sorting(2));
			else
				if (radioSrtYearGen->isChecked())
					load_movies(srv.sorting(3));

	});
	QObject::connect(undoButton, &QPushButton::clicked, [&](){
		try {
			srv.undo();
			load_movies(srv.get_all_from_repo());
		}
		catch(InsuficientMovies &err)
		{
			QMessageBox::warning(this, "Warning", QString::fromStdString(err.getMessage()));
		}
	});
	QObject::connect(cartButton, &QPushButton::clicked, [&](){
		CartConsole* cart_console = new CartConsole{srv};
		cart_console->show();
	});
}

void AdminConsole::gui_add_movie(){
	try{
		std::string title = titleEdit->text().toStdString();
		std::string gen = genEdit->text().toStdString();
		std::string year = yearEdit->text().toStdString();
		std::string actor = actorEdit->text().toStdString();

		titleEdit->clear();
		genEdit->clear();
		yearEdit->clear();
		actorEdit->clear();

		srv.srv_add_movie(title, gen, year, actor);

		QMessageBox::information(this, "Info", QString::fromStdString("Successfully added!"));

		load_movies(srv.get_all_from_repo());
	}
	catch(MovieExistent& err){
		QMessageBox::warning(this, "Warning", QString::fromStdString(err.getMessage()));
	}
	catch(InvalidMovie& err){
		QMessageBox::warning(this, "Warning", QString::fromStdString(err.getMessage()));
	}
}

void AdminConsole::gui_change_movie(){
	GuiChangeMovie change_movie_console{ srv };
	load_movies(srv.get_all_from_repo());
}

void AdminConsole::gui_delete_movie(){
	GuiDeleteMovie  delete_movie_console{ srv };
	load_movies(srv.get_all_from_repo());
}
