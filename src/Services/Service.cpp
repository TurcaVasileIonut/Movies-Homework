#include "Service.h"


std::vector<Movie> Service::get_all_from_repo() {
	return repo_movies.get_all();
}


void Service::srv_add_movie(const std::string& title, const std::string& gen, const std::string& year, const std::string& actor) {
	validator_movie.validate_movie(title, gen, year, actor);

	Movie current_movie{ title, gen, convert_string_to_number(year), actor };
	repo_movies.push_back(current_movie);

	Actions.push_back(new UndoAdauga(repo_movies, current_movie));
}


void Service::srv_delete_movie(const std::string& title, const std::string& gen, const std::string& year, const std::string& actor) {
	validator_movie.validate_movie(title, gen, year, actor);

	Movie current_movie{ title, gen, convert_string_to_number(year), actor };
	int movie_pos = repo_movies.movie_adress(current_movie);
	cart_movies.remove_movie(movie_pos);

	repo_movies.delete_movie(current_movie);

	Actions.push_back(new UndoRemove(repo_movies, current_movie));
}


void Service::srv_change_movie(const std::string& title, const std::string& gen, const std::string& year, const std::string& actor, const std::string& new_title, const std::string& new_gen, const std::string& new_year, const std::string& new_actor) {
	validator_movie.validate_movie(title, gen, year, actor);
	validator_movie.validate_movie(new_title, new_gen, new_year, new_actor);

	Movie current_movie{ title, gen, convert_string_to_number(year), actor };
	Movie new_movie{ new_title, new_gen, convert_string_to_number(new_year), new_actor };

	repo_movies.change_movie(current_movie, new_movie);

	Actions.push_back(new UndoChange(repo_movies, current_movie, new_movie));
}

bool Service::search_movie(const std::string& title, const std::string& gen, const std::string& year, const std::string& actor) {
	validator_movie.validate_movie(title, gen, year, actor);
	Movie m{ title, gen, convert_string_to_number(year), actor};
	std::vector < Movie > movies = (this->repo_movies).search_movies(m);
	return (movies.size() > 0);
}

std::vector<Movie> Service::filter_by_title(const std::string& title) {
	if (title.length() < 1) {
		std::string error = "Invalid title length! ";
		throw InvalidMovie(error);
	}

	std::vector<Movie> result = (this->repo_movies).filter_by_title(title);
	return result;
}

std::vector<Movie> Service::filter_by_year(const std::string& year) {
	(this->validator_movie).is_number(year);

	return (this->repo_movies).filter_by_year(convert_string_to_number(year));
}

std::vector<Movie> Service::sorting(const int& criteria) {
	std::vector < Movie > movies = get_all_from_repo();

	if (criteria == 1)
		sort(movies.begin(), movies.end(), cmp_by_title);
	else
		if (criteria == 2)
			sort(movies.begin(), movies.end(), cmp_by_actor);
		else
			if (criteria == 3)
				sort(movies.begin(), movies.end(), cmp_by_year_and_gen);

	return movies;
}

void Service::undo(){
	if (Actions.empty())
		throw InsuficientMovies("The action history is empty! ");
	UndoActions* act = Actions.back();
	act->doUndo();
	Actions.pop_back();
	delete act;
}

int Service::cart_size() const{
	return cart_movies.size();
}

std::vector < Movie > Service::get_all_from_cart(){
	std::vector < Movie > movies;
	for (int it : cart_movies.get_all()) {
		movies.push_back(*(repo_movies.begin() + it));
	}
	return movies;
}

void Service::add_in_cart(const std::string& title, const std::string& gen, const std::string& year, const std::string& actor){
	Movie m{ title, gen, convert_string_to_number(year), actor};
	int it = this->repo_movies.movie_adress(m);
	cart_movies.push_back(it);
}

void Service::clear_cart(){
	cart_movies.clear();
}

void Service::add_random_movies_in_cart(const int& count){
	if (repo_movies.size() < count + cart_movies.size()) {
		std::string error = "There are less than ";
		error += convert_number_to_string(count);
		error += " movies in repo that are not in cart! ";
		throw InsuficientMovies(error);
	}

	std::vector < Movie > movies = repo_movies.get_all();
	std::vector < int > movies_in_cart = cart_movies.get_all();
	std::set < int > used;
	for (auto it : movies_in_cart)
		used.insert(it);
	for (int i = 1; i <= count; i++) {
		while (true) {
			std::mt19937 mt{ std::random_device{}() };
			std::uniform_int_distribution<> dist(0, repo_movies.size() - 1);
			int rndNr = dist(mt);	
				
			if (!used.count(rndNr)) {
				int it = repo_movies.movie_adress(movies[rndNr]);
				cart_movies.push_back(it);
				used.insert(it);
				break;
			}
		}

	}

}

void Service::save_cart_in_csv(std::string filename){
	std::ofstream fout;
	fout.open(filename);

	std::vector < int > movies_it = cart_movies.get_all();

	for (int it : movies_it)
		fout << (*(repo_movies.begin() + it)).get_title() << "," << (*(repo_movies.begin() + it)).get_gen() <<"," <<(*(repo_movies.begin() + it)).get_year() << "," << (*(repo_movies.begin() + it)).get_actor() << "\n";
	fout.close();
}

Service::~Service(){
	while (!Actions.empty()) {
		UndoActions* act = Actions.back();
		Actions.pop_back();
		delete act;
	}
}
