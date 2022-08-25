#include "TestFileRepo.h"
#include "Exceptions.h"

#include <assert.h>

#include <iostream>

void TestFileRepo::run_all_tests_repo() {
	test_get_all();
	test_delete_a_movie();
	test_change_a_movie();
	test_filter_by_title();
	test_filter_by_year();
}


void TestFileRepo::test_get_all() {
	Movie m{ "No time to die", "Action", 2021, "Daniel Craig" };
	repo.push_back(m);
	Movie m1{ "Spectre", "Action2", 2015, "D. Craig" };
	repo.push_back(m1);
	std::vector < Movie > movies = repo.get_all();
	assert(movies.size() == 2);
	for (auto movie : movies) {
		if (movie.get_title() == "No time to die") {
			assert(movie.get_gen() == "Action");
			assert(movie.get_year() == 2021);
			assert(movie.get_actor() == "Daniel Craig");
			continue;
		}
		assert(movie.get_title() == "Spectre");
		assert(movie.get_gen() == "Action2");
		assert(movie.get_year() == 2015);
		assert(movie.get_actor() == "D. Craig");
	}
}

void TestFileRepo::test_delete_a_movie() {
	Movie m{ "No time to die", "Action", 2021, "Daniel Craig" };
	Movie m1{ "Spectre", "Action2", 2015, "D. Craig" };

	std::vector<Movie>movies = repo.get_all();
	assert(movies.size() == 2);

	repo.delete_movie(m);

	std::vector<Movie>movies2 = repo.get_all();
	assert(movies2.size() == 1);
	for (auto movie : movies2) {
		assert(movie.get_title() == "Spectre");
		assert(movie.get_gen() == "Action2");
		assert(movie.get_year() == 2015);
		assert(movie.get_actor() == "D. Craig");
	}

	try {
		repo.delete_movie(m);
	}
	catch (MovieInexistent error) {
		assert(error.getMessage() == "Movie not found! ");
	}

	std::vector<Movie>movies3 = repo.get_all();
	assert(movies3.size() == 1);
	for (auto movie : movies3) {
		assert(movie.get_title() == "Spectre");
		assert(movie.get_gen() == "Action2");
		assert(movie.get_year() == 2015);
		assert(movie.get_actor() == "D. Craig");
	}

	repo.push_back(m);
}

void TestFileRepo::test_change_a_movie() {
	std::vector < Movie > movies;
	Movie m{ "No time to die", "Action", 2021, "Daniel Craig" };
	Movie m1{ "Spectre", "Action2", 2015, "D. Craig" };
	Movie m2{ "Spectre", "Action2", 2016, "D. Craig" };
	Movie m3{ "Spectre2", "Action2", 2016, "D. Craig" };

	try {
		repo.change_movie(m2, m1);
	}
	catch (MovieExistent& error) {
		assert(error.getMessage() == "There is a movie with the new specs! ");
	}

	try {
		repo.change_movie(m2, m3);
	}
	catch (MovieInexistent& error) {
		assert(error.getMessage() == "Movie not found! ");
	}

	repo.change_movie(m, m2);
	std::vector <Movie>movies2 = repo.get_all();
	assert(movies2.size() == 2);
	for (auto movie : movies2) {
		assert(movie.get_title() == "Spectre");
		assert(movie.get_gen() == "Action2");
		assert(movie.get_year() == 2015 || movie.get_year() == 2016);
		assert(movie.get_actor() == "D. Craig");
	}

	try {
		repo.change_movie(m1, m2);
	}
	catch (MovieExistent& error) {
		assert(error.getMessage() == "There is a movie with the new specs! ");
	}
	std::vector < Movie > movies3 = repo.get_all();
	assert(movies3.size() == 2);
	for (auto movie : movies3) {
		if (movie.get_title() == "Spectre") {
			assert(movie.get_gen() == "Action2");
			assert(movie.get_year() == 2015 || movie.get_year() == 2016);
			assert(movie.get_actor() == "D. Craig");
		}
	}
	repo.change_movie(m2, m);
}

void TestFileRepo::test_filter_by_title() {
	Movie m{ "No time to die", "Action", 2021, "Daniel Craig" };
	Movie m1{ "Spectre", "Action2", 2015, "D. Craig" };

	std::vector < Movie > movies = repo.filter_by_title("No time to die");
	assert(movies.size() == 1);
	assert(movies[0] == m);

	movies = repo.filter_by_title("Spectre");
	assert(movies.size() == 1);
	assert(movies[0] == m1);

	movies = repo.filter_by_title("fas");
	assert(movies.size() == 0);
}

void TestFileRepo::test_filter_by_year() {
	Movie m{ "No time to die", "Action", 2021, "Daniel Craig" };
	Movie m1{ "Spectre", "Action2", 2015, "D. Craig" };

	std::vector < Movie > movies = repo.filter_by_year(2021);
	assert(movies.size() == 1);
	assert(movies[0] == m);

	movies = repo.filter_by_year(2015);
	assert(movies.size() == 1);
	assert(movies[0] == m1);

	movies = repo.filter_by_year(3232);
	assert(movies.size() == 0);
}