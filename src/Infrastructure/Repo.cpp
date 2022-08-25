#include "Repo.h"
#include "Exceptions.h"
#include <iostream>


RepoMovies::RepoMovies(const RepoMovies& ot) {
	this->repo = ot.repo;
}

int RepoMovies::size() const{
	return int(repo.size());
}

std::vector < Movie > RepoMovies::get_all() const {
	return repo;
}

void RepoMovies::push_back(Movie& current_movie) {
	auto it = find(repo.begin(), repo.end(), current_movie);
	if (it != repo.end()) {
		throw MovieExistent("There is a movie with the new specs! ");
	}
	(this->repo).push_back(current_movie);
}


void RepoMovies::delete_movie(const Movie& current_movie) {
	auto it = repo.begin();
	it = find(repo.begin(), repo.end(), current_movie);

	if (it == repo.end()){
		std::string error = "Movie not found! ";
		throw MovieInexistent(error);
	}
	repo.erase(it);
}

void RepoMovies::change_movie(const Movie& current_movie, const Movie& new_movie) {
	auto it = find(repo.begin(), repo.end(), new_movie);

	if (it != repo.end()) {
		std::string error = "There is a movie with the new specs! ";
		throw MovieExistent(error);
	}

	it = find(repo.begin(), repo.end(), current_movie);

	if (it == repo.end()) {
		std::string error = "Movie not found! ";
		throw MovieInexistent(error);
	}

	*it = new_movie;
}

std::vector<Movie> RepoMovies::filter_by_title(const std::string& title) const{
	std::vector < Movie > results(repo.size());
	auto it = copy_if(repo.begin(), repo.end(), results.begin(), [title](Movie i) {return i.get_title() == title; });
	results.resize(std::distance(results.begin(), it));
	return results;
}

std::vector<Movie> RepoMovies::filter_by_year(const int& year) const{
	std::vector < Movie > results(repo.size());
	auto it = copy_if(repo.begin(), repo.end(), results.begin(), [year](Movie i) {return i.get_year() == year; });
	results.resize(std::distance(results.begin(), it));
	return results;
}

std::vector<Movie> RepoMovies::search_movies(const Movie &current_movie) const{
	std::vector < Movie > results(repo.size());
	auto it = copy_if(repo.begin(), repo.end(), results.begin(), [current_movie](Movie i) {return i == current_movie; });
	results.resize(std::distance(results.begin(), it));
	return results;
}

int RepoMovies::movie_adress(const Movie& movie){
	auto it = find(repo.begin(), repo.end(), movie);
	const int adress = it - repo.begin();
	return adress;
}

void FileRepoMovies::read_from_file(){
	std::ifstream fin;
	fin.open(this->filename);

	std::string input;
	while (getline(fin, input)) {

		std::string fields[4];
		for (int i = 0; i < 3; i++)
			fields[i] = get_first_field(input, char(','));
		fields[3] = input;

		Movie current_movie{ fields[0], fields[1], fields[2], fields[3] };

		repo.push_back(current_movie);
	}
	fin.close();
}

void FileRepoMovies::refresh_repo(){
	repo.clear();
	read_from_file();
}

void FileRepoMovies::write_back(){
	std::ofstream fout;
	fout.open(this->filename);
	for (auto it : repo)
		fout << it.get_title() << "," << it.get_gen() << "," << it.get_year() << "," << it.get_actor() << "\n";
	fout.close();
}

std::vector<Movie>::iterator FileRepoMovies::begin() {
	return repo.begin();
};

FileRepoMovies::FileRepoMovies(const FileRepoMovies& ot){
	this->repo = ot.repo;
	this->filename = ot.filename;
}

int FileRepoMovies::size(){
	refresh_repo();
	return RepoMovies::size();
}

std::vector<Movie> FileRepoMovies::get_all(){
	refresh_repo();
	return RepoMovies::get_all();
}

void FileRepoMovies::push_back(Movie& current_movie){
	refresh_repo();
	RepoMovies::push_back(current_movie);
	write_back();
}

void FileRepoMovies::delete_movie(const Movie& current_movie){
	refresh_repo();
	RepoMovies::delete_movie(current_movie);
	write_back();
}

void FileRepoMovies::change_movie(const Movie& current_movie, const Movie& new_movie){
	refresh_repo();
	RepoMovies::change_movie(current_movie, new_movie);
	write_back();
}

std::vector<Movie> FileRepoMovies::filter_by_title(const std::string& title){
	refresh_repo();
	return RepoMovies::filter_by_title(title);
}

std::vector<Movie> FileRepoMovies::filter_by_year(const int& year){
	refresh_repo();
	return RepoMovies::filter_by_year(year);
}

std::vector<Movie> FileRepoMovies::search_movies(const Movie& current_movie){
	refresh_repo();
	return RepoMovies::search_movies(current_movie);
}

int FileRepoMovies::movie_adress(const Movie& movie){
	refresh_repo();
	return RepoMovies::movie_adress(movie);
}
