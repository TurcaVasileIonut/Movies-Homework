#include "TestService.h"
#include <iostream>


void test_add_movie_feature_light_test();

void test_add_movie_feature_extended_test();

void test_add_movie_feature_throw_exception();

void TestService::test_add_movie_feature() {
	test_add_movie_feature_light_test();
	test_add_movie_feature_extended_test();
	test_add_movie_feature_throw_exception();
}

void test_add_movie_feature_light_test() {
	std::ofstream fout;
	fout.open("test_movie_file.csv");
	fout.close();
	FileRepoMovies repo_movies{ "test_movie_file.csv" };
	ValidatorMovie validator_movies;
	CartMovies cart_movies;
	Service srv{ repo_movies, cart_movies, validator_movies };

	srv.srv_add_movie("No time to die", "Action", "2021", "Daniel Craig");

	std::vector < Movie > movies = srv.get_all_from_repo();
	assert(movies.size() == 1);
	assert(movies[0].get_title() == "No time to die");
	assert(movies[0].get_gen() == "Action");
	assert(movies[0].get_year() == 2021);
	assert(movies[0].get_actor() == "Daniel Craig");
}

void test_add_movie_feature_extended_test() {
	std::ofstream fout;
	fout.open("test_movie_file.csv");
	fout.close();
	FileRepoMovies repo_movies{ "test_movie_file.csv" };
	ValidatorMovie validator_movies;
	CartMovies cart_movies;
	Service srv{ repo_movies, cart_movies, validator_movies };
	srv.srv_add_movie("No time to die", "Action", "2021", "Daniel Craig");
	srv.srv_add_movie("Spectre", "Action2", "2015", "D. Craig");

	std::vector < Movie > movies = srv.get_all_from_repo();
	for (auto movie : movies) {
		if (movie.get_title() == "No time to die") {
			assert(movie.get_gen() == "Action");
			assert(movie.get_year() == 2021);
			assert(movie.get_actor() == "Daniel Craig");
			continue;
		}
		if (movie.get_title() == "Spectre") {
			assert(movie.get_gen() == "Action2");
			assert(movie.get_year() == 2015);
			assert(movie.get_actor() == "D. Craig");

		}

	}
}

void test_add_movie_feature_throw_exception() {
	std::ofstream fout;
	fout.open("test_movie_file.csv");
	fout.close();
	FileRepoMovies repo_movies{ "test_movie_file.csv" };
	ValidatorMovie validator_movies;
	CartMovies cart_movies;
	Service srv{ repo_movies, cart_movies, validator_movies };
	try {
		srv.srv_add_movie("", "", "", "");
	}
	catch (InvalidMovie& msg) {
		assert(msg.getMessage() == "Invalid title length! Invalid gen length! Invalid year length! Invalid length of the main actor name! ");
	}

	srv.srv_add_movie("No time to die", "Action", "2021", "Daniel Craig");
	srv.srv_add_movie("Spectre", "Action2", "2015", "D. Craig");

	try {
		srv.srv_add_movie("", "", "", "");
	}
	catch (InvalidMovie& msg) {
		assert(msg.getMessage() == "Invalid title length! Invalid gen length! Invalid year length! Invalid length of the main actor name! ");
	}

	try {
		srv.srv_add_movie("", "", "a2", "");
	}
	catch (InvalidMovie& msg) {
		assert(msg.getMessage() == "Invalid title length! Invalid gen length! Found 1 characters that are not digits in the year entered! Invalid length of the main actor name! ");
	}

	srv.srv_add_movie("das", "das", "32", "das");
	try {
		srv.srv_add_movie("das", "das", "32", "das");
	}
	catch (MovieExistent& msg) {
		assert(msg.getMessage() == "There is a movie with the new specs! ");
	}
}
