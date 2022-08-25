#include "TestService.h"

#include <iostream>

void test_sort_by_title();

void test_sort_by_actor();

void test_sort_by_year_and_gen();

void TestService::test_sorting() {
	test_sort_by_title();
	test_sort_by_actor();
	test_sort_by_year_and_gen();
}

void test_sort_by_title() {
	std::ofstream fout;
	fout.open("test_movies_file.csv");
	fout.close();
	FileRepoMovies repo_movies{ "test_movies_file.csv" };
	ValidatorMovie validator_movies;
	CartMovies cart_movies;
	Service srv{ repo_movies, cart_movies, validator_movies };
	srv.srv_add_movie("Spectre3", "Action", "2015", "D. Craig");
	srv.srv_add_movie("Spectre2", "Action", "2015", "D. Craig");
	srv.srv_add_movie("Spectre5", "Action", "2015", "D. Craig");
	srv.srv_add_movie("Spectre1", "Action", "2015", "D. Craig");
	srv.srv_add_movie("Spectre4", "Action", "2015", "D. Craig");

	std::vector < Movie > movies = srv.sorting(1);

	assert(movies.size() == 5);
	for (int i = 0; i < 5; i++) {
		std::string title = "Spectre";
		title += i + 1 + '0';
		assert(movies[i].get_title() == title);
		assert(movies[i].get_gen() == "Action");
		assert(movies[i].get_year() == 2015);
		assert(movies[i].get_actor() == "D. Craig");
	}
}

void test_sort_by_actor() {
	std::ofstream fout;
	fout.open("test_movies_file.csv");
	fout.close();
	FileRepoMovies repo_movies{ "test_movies_file.csv" };
	ValidatorMovie validator_movies;
	CartMovies cart_movies;
	Service srv{ repo_movies, cart_movies, validator_movies };
	srv.srv_add_movie("Spectre", "Action", "2015", "Daniel Craig0");
	srv.srv_add_movie("Spectre", "Action", "2015", "Daniel Craig1");
	srv.srv_add_movie("Spectre", "Action", "2015", "Daniel Craig4");
	srv.srv_add_movie("Spectre", "Action", "2015", "Daniel Craig2");
	srv.srv_add_movie("Spectre", "Action", "2015", "Daniel Craig3");

	std::vector < Movie > movies = srv.sorting(2);
	assert(movies.size() == 5);
	for (int i = 0; i < 5; i++) {
		std::string actor = "Daniel Craig";
		actor += i + '0';
		assert(movies[i].get_title() == "Spectre");
		assert(movies[i].get_gen() == "Action");
		assert(movies[i].get_year() == 2015);
		assert(movies[i].get_actor() == actor);
	}
}

void test_sort_by_year_and_gen() {
	std::ofstream fout;
	fout.open("test_movies_file.csv");
	fout.close();
	FileRepoMovies repo_movies{ "test_movies_file.csv" };
	ValidatorMovie validator_movies;
	CartMovies cart_movies;
	Service srv{ repo_movies, cart_movies, validator_movies };
	srv.srv_add_movie("Spectre", "Action2", "2015", "Daniel Craig");
	srv.srv_add_movie("Spectre", "Action2", "2016", "Daniel Craig");
	srv.srv_add_movie("Spectre", "Action3", "2015", "Daniel Craig");
	srv.srv_add_movie("Spectre", "Action1", "2016", "Daniel Craig");
	srv.srv_add_movie("Spectre", "Action1", "2015", "Daniel Craig");
	srv.srv_add_movie("Spectre", "Action", "2012", "Daniel Craig");

	std::vector < Movie > movies = srv.sorting(3);
	assert(movies.size() == 6);

	for (Movie movie : movies) {
		assert(movie.get_title() == "Spectre");
		assert(movie.get_actor() == "Daniel Craig");
	}

	assert(movies[0].get_gen() == "Action");
	assert(movies[1].get_gen() == "Action1");
	assert(movies[2].get_gen() == "Action2");
	assert(movies[3].get_gen() == "Action3");
	assert(movies[4].get_gen() == "Action1");
	assert(movies[5].get_gen() == "Action2");

	assert(movies[0].get_year() == 2012);
	assert(movies[1].get_year() == 2015);
	assert(movies[2].get_year() == 2015);
	assert(movies[3].get_year() == 2015);
	assert(movies[4].get_year() == 2016);
	assert(movies[5].get_year() == 2016);
}
