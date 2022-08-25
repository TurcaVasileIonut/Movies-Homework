#include "Console.h"
#include "Exceptions.h"

int get_command();

void print_opening_menu();

void print_user_menu();

void print_admin_menu();

void print_filter_menu();

void print_sort_menu();

void print_movies(std::vector < Movie >& movies);

void Console::run_admin_console() {
	while (true) {
		print_admin_menu();
		try {
			int command = get_command();
			switch (command) {
			case 1: {
				ui_print_all_elements();
				break;
			}
			case 2: {
				ui_add_element();
				break;
			}
			case 3: {
				ui_change();
				break;
			}
			case 4: {
				ui_remove();
				break;
			}
			case 5: {
				ui_check_movie_in_repo();
				break;
			}
			case 6: {
				ui_filter();
				break;
			}
			case 7: {
				ui_sort();
				break;
			}
			case 8: {
				ui_undo();
				break;
			}
			case 9:
				return;
			}
		}
		catch (std::string error) {
			std::cout << error << "\n";
		}
		catch (MovieInexistent& error) {
			std::cout << error.getMessage() << "\n";
		}
		catch (MovieExistent& error) {
			std::cout << error.getMessage() << "\n";
		}
		catch (InvalidMovie& error) {
			std::cout << error.getMessage() << "\n";
		}
		catch (InsuficientMovies& error) {
			std::cout << error.getMessage() << "\n";
		}
	}
}

void Console::run_user_console(){
	while (1) {
		print_user_menu();
		int command = get_command();
		try {
			switch (command)
			{
			case 1: {
				srv.clear_cart();
				break;
			}
			case 2: {
				ui_add_movie_in_cart();
				break;
			}
			case 3: {
				ui_generate_cart();
				break;
			}
			case 4: {
				ui_save_cart();
				break;
			}
			case 5: {
				return;
			}
			default:
				continue;
			}
		}
		catch (std::string error) {
			std::cout << error << "\n";
		}
		catch (MovieInexistent& error) {
			std::cout << error.getMessage() << "\n";
		}
		catch (MovieExistent& error) {
			std::cout << error.getMessage() << "\n";
		}
		catch (InvalidMovie& error) {
			std::cout << error.getMessage() << "\n";
		}
		catch (InsuficientMovies& error) {
			std::cout << error.getMessage() << "\n";
		}
		std::cout << "\nCart size: " << srv.cart_size() << "\n";
	}
}

void Console::ui_add_movie_in_cart(){
	std::string title = get_title_from_user();

	std::vector < Movie > movies = srv.filter_by_title(title);

	if (movies.empty()) {
		std::cout << "\nThere is no movie with that title! \n";
		return;
	}

	std::cout << "\nThe movies with that title are: \n";
	for (int i = 0; i < movies.size(); i++) {
		std::cout << i + 1 << ". " << movies[i].string_movie() << "\n";
	}
	std::cout << "Please select the movie you want to add in the cart.\n\n";
	int command = get_command() - 1;
	if (command >= movies.size()) {
		std::cout << "\nInvalid choice!\n";
		return;
	}
	srv.add_in_cart(movies[command].get_title(), movies[command].get_gen(), convert_number_to_string(movies[command].get_year()), movies[command].get_actor());
}

void Console::ui_generate_cart(){
	std::cout << "\n>>Please give the number of movies you want to add in the cart: ";
	std::string s;
	std::getline(std::cin, s);

	for (auto it : s) {
		if (it >= '0' && it <= '9') continue;
		std::string error = "Invalid input! ";
		throw error;
	}
	int command = convert_string_to_number(s);
	srv.add_random_movies_in_cart(command);
}

void Console::ui_save_cart(){
	std::cout << "Please enter the filename: ";
	std::string filename;
	std::getline(std::cin, filename);
	if (filename.size() < 1) {
		std::cout << "Invalid filename!\n";
		return;
	}
	srv.save_cart_in_csv(filename);
}

void Console::run_super_console() {
	while (1) {
		print_opening_menu();
		int command = get_command();
		try {
			switch (command)
			{
			case 1: {
				run_admin_console();
				break;
			}
			case 2: {
				run_user_console();
				break;
			}
			case 3: {
				return;
			}
			default:
				continue;
			}
		}
		catch (std::string error) {
			std::cout << error << "\n";
		}
		catch (MovieInexistent& error) {
			std::cout << error.getMessage() << "\n";
		}
		catch (MovieExistent& error) {
			std::cout << error.getMessage() << "\n";
		}
		catch (InvalidMovie& error) {
			std::cout << error.getMessage() << "\n";
		}
	}
}

void print_opening_menu() {
	std::cout << "\n1.Admin console\n";
	std::cout << "2.User console\n";
	std::cout << "3.Exit\n\n";
}

void Console::ui_print_all_elements() {
	std::vector < Movie > movies = srv.get_all_from_repo();
	for (Movie movie : movies)
		std::cout << movie.string_movie() << "\n\n";
}

void Console::ui_add_element() {
	std::string title = get_title_from_user();
	std::string gen = get_gen_from_user();
	std::string year = get_year_from_user();
	std::string actor = get_actor_from_user();

	srv.srv_add_movie(title, gen, year, actor);

	std::cout << "\nSuccessfully added!\n\n";
}

void Console::ui_change() {
	std::cout << "Please give the old movie:\n";
	std::string title_old = get_title_from_user();
	std::string gen_old = get_gen_from_user();
	std::string year_old = get_year_from_user();
	std::string actor_old = get_actor_from_user();
	std::cout << "Please give the new movie:\n";
	std::string title_new = get_title_from_user();
	std::string gen_new = get_gen_from_user();
	std::string year_new = get_year_from_user();
	std::string actor_new = get_actor_from_user();

	srv.srv_change_movie(title_old, gen_old, year_old, actor_old, title_new, gen_new, year_new, actor_new);

	std::cout << "\nSuccessfully changed!\n\n";

}

void Console::ui_remove() {
	std::string title = get_title_from_user();
	std::string gen = get_gen_from_user();
	std::string year = get_year_from_user();
	std::string actor = get_actor_from_user();

	srv.srv_delete_movie(title, gen, year, actor);

	std::cout << "\nSuccessfully removed!\n\n";
}

void Console::ui_check_movie_in_repo() {
	std::string title = get_title_from_user();
	std::string gen = get_gen_from_user();
	std::string year = get_year_from_user();
	std::string actor = get_actor_from_user();

	if (srv.search_movie(title, gen, year, actor))
		std::cout << "\nThe movie is in repo!\n\n";
	else
		std::cout << "\nThe movie is not in the repo!\n\n";
}

void Console::ui_filter() {
	print_filter_menu();
	int command = get_command();
	if (command == 1) {
		std::string title = get_title_from_user();
		std::vector < Movie > movies = srv.filter_by_title(title);
		print_movies(movies);
		return;
	}
	if (command == 2) {
		std::string year = get_year_from_user();
		std::vector < Movie > movies = srv.filter_by_year(year);
		print_movies(movies);
		return;
	}
}

void Console::ui_sort() {
	print_sort_menu();
	std::vector < Movie > movies;
	int command = get_command();
	movies = srv.sorting(command);
	print_movies(movies);
}

void Console::ui_undo(){
	srv.undo();
	std::cout << "\nThe last command was undo\n\n";

}

void print_user_menu() {
	std::cout << "\n1.Empty cart\n";
	std::cout << "2.Add a movie by title\n";
	std::cout << "3.Add [n] random movies in cart\n";
	std::cout << "4.Save the cart in a [filename]\n";
	std::cout << "5.Exit\n";
}

void print_admin_menu() {
	std::cout << "\n1. Print all elements\n";
	std::cout << "2. Add a movie\n";
	std::cout << "3. Change a movie\n";
	std::cout << "4. Delete a movie\n";
	std::cout << "5. Check if movie is in repo\n";
	std::cout << "6. Filter\n";
	std::cout << "7. Sort\n";
	std::cout << "8. Undo\n";
	std::cout << "9. Exit\n\n";
}

void print_filter_menu() {
	std::cout << "\n\n1.Filter by title\n";
	std::cout << "2.Filter by year\n\n";
}

void print_sort_menu() {
	std::cout << "\n\n1.Sort title\n2.Sort by main actor\n3.Sort by year and gen\n";
}

void print_movies(std::vector < Movie >& movies) {
	std::cout << "\nThe movies are:\n";
	for (auto movie : movies)
		std::cout << movie.string_movie() << "\n";
}

int get_command() {
	std::cout << ">>>>Please give the command: ";
	std::string s;
	std::getline(std::cin, s);

	for (auto it : s) {
		if (it >= '0' && it <= '9') continue;
		std::string error = "Invalid input! ";
		throw error;
	}
	return convert_string_to_number(s);
}