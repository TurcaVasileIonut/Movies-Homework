#include "AddCartConsole.h"


void GuiAddCart::initialize_console(){
	main_dialog = new QDialog;
	main_layout = new QVBoxLayout;
	main_dialog->setLayout(main_layout);

	addMovie = new QPushButton("Add movie");
	main_layout->addWidget(addMovie);
}

void GuiAddCart::load_movies(std::vector < Movie > movies){
	for(auto it : movies){
		QRadioButton* localButton = new QRadioButton(QString::fromStdString(it.string_movie()));
		main_layout->addWidget(localButton);
		radioButtons.push_back(localButton);
	}
}

void GuiAddCart::connect_signals(){
	QObject::connect(this->addMovie, &QPushButton::clicked, [&]() {
		int count_movies = movies.size();
		for(int i = 0 ; i < count_movies ; i++)
			if (this->radioButtons[i]->isChecked()) 
				srv.add_in_cart(movies[i].get_title(), movies[i].get_gen(), convert_number_to_string(movies[i].get_year()), movies[i].get_actor());
	});
	QObject::connect(this->addMovie, &QPushButton::clicked, main_dialog, &QDialog::close);
}

