#include "TestService.h"
#include "Exceptions.h"

#include <iostream>

void test_change_movie_feature_light_test(Service srv);

void test_change_movie_feature_extended_test(Service srv);

void test_change_movie_feature_throw_exception(Service srv);

void test_change_movie_feature_undo(Service srv);

void TestService::test_change_movie_feature() {
	test_change_movie_feature_light_test(srv);
	test_change_movie_feature_extended_test(srv);
	test_change_movie_feature_throw_exception(srv);
	test_change_movie_feature_undo(srv);
}

void test_change_movie_feature_light_test(Service srv) {
	std::ofstream fout("test_movie_file.csv");
	fout.close();
	srv.srv_add_movie("No time to die", "Action", "2021", "Daniel Craig");
	std::vector < Movie > movies = srv.get_all_from_repo();
	assert(movies.size() == 1);
	assert(movies[0].get_title() == "No time to die");
	assert(movies[0].get_gen() == "Action");
	assert(movies[0].get_year() == 2021);
	assert(movies[0].get_actor() == "Daniel Craig");


	srv.srv_change_movie("No time to die", "Action", "2021", "Daniel Craig", "Spectre", "Action2", "2015", "D. Craig");

	std::vector < Movie > movies2 = srv.get_all_from_repo();
	assert(movies2[0].get_title() == "Spectre");
	assert(movies2[0].get_gen() == "Action2");
	assert(movies2[0].get_year() == 2015);
	assert(movies2[0].get_actor() == "D. Craig");
}

void test_change_movie_feature_extended_test(Service srv) {
	std::ofstream fout("test_movie_file.csv");
	fout.close();
	srv.srv_add_movie("No time to die", "Action", "2021", "Daniel Craig");
	srv.srv_add_movie("Spectre", "Action2", "2015", "D. Craig");

	std::vector < Movie > movies = srv.get_all_from_repo();
	assert(movies.size() == 2);
	assert(movies[0].get_title() == "No time to die");
	assert(movies[0].get_gen() == "Action");
	assert(movies[0].get_year() == 2021);
	assert(movies[0].get_actor() == "Daniel Craig");

	srv.srv_change_movie("No time to die", "Action", "2021", "Daniel Craig", "Spectre2", "Action2", "2015", "D. Craig");

	std::vector < Movie > movies2 = srv.get_all_from_repo();
	for (auto movie : movies2) {
		assert(movie.get_title() == "Spectre2" || movie.get_title() == "Spectre");
		assert(movie.get_gen() == "Action2");
		assert(movie.get_year() == 2015);
		assert(movie.get_actor() == "D. Craig");
	}


}

void test_change_movie_feature_throw_exception(Service srv) {
	std::ofstream fout("test_movie_file.csv");
	fout.close();
	srv.srv_add_movie("No time to die", "Action", "2021", "Daniel Craig");
	srv.srv_add_movie("Spectre", "Action2", "2015", "D. Craig");

	try {
		srv.srv_change_movie("Spectre2", "Action", "2021", "Daniel Craig", "Spec", "Drama", "32", "The Rock");
	}
	catch (MovieInexistent& error) {
		assert(error.getMessage() == "Movie not found! ");
	}

	try {
		srv.srv_change_movie("Spectre2", "Action", "2021", "Daniel Craig", "No time to die", "Action", "2021", "Daniel Craig");
	}
	catch (MovieExistent& error) {
		assert(error.getMessage() == "There is a movie with the new specs! ");
	}
}

void test_change_movie_feature_undo(Service srv){
	std::ofstream fout("test_movie_file.csv");
	fout.close();
	srv.srv_add_movie("No time to die", "Action", "2021", "Daniel Craig");
	std::vector < Movie > movies = srv.get_all_from_repo();
	assert(movies.size() == 1);
	assert(movies[0].get_title() == "No time to die");
	assert(movies[0].get_gen() == "Action");
	assert(movies[0].get_year() == 2021);
	assert(movies[0].get_actor() == "Daniel Craig");


	srv.srv_change_movie("No time to die", "Action", "2021", "Daniel Craig", "Spectre", "Action2", "2015", "D. Craig");

	std::vector < Movie > movies2 = srv.get_all_from_repo();
	assert(movies2[0].get_title() == "Spectre");
	assert(movies2[0].get_gen() == "Action2");
	assert(movies2[0].get_year() == 2015);
	assert(movies2[0].get_actor() == "D. Craig");

	srv.undo();
	movies = srv.get_all_from_repo();
	assert(movies.size() == 1);
	assert(movies[0].get_title() == "No time to die");
	assert(movies[0].get_gen() == "Action");
	assert(movies[0].get_year() == 2021);
	assert(movies[0].get_actor() == "Daniel Craig");
}