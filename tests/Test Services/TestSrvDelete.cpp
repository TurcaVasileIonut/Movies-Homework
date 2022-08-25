#include "TestService.h"
#include "Exceptions.h"


void test_delete_a_movie_feature_light_test(Service srv);

void test_delete_a_movie_feature_extended_test(Service srv);

void test_delete_movie_feature_throw_exception(Service srv);

void test_delete_movie_with_movie_in_cart(Service srv);

void TestService::test_delete_movie_feature() {
	std::ofstream fout("test_movie_file.csv");
	fout.close();
	test_delete_a_movie_feature_light_test(srv);
	test_delete_a_movie_feature_extended_test(srv);
	test_delete_movie_feature_throw_exception(srv);
	test_delete_movie_with_movie_in_cart(srv);
}


void test_delete_a_movie_feature_light_test(Service srv) {
	srv.srv_add_movie("No time to die", "Action", "2021", "Daniel Craig");

	std::vector < Movie > movies = srv.get_all_from_repo();
	assert(movies.size() == 1);
	assert(movies[0].get_title() == "No time to die");
	assert(movies[0].get_gen() == "Action");
	assert(movies[0].get_year() == 2021);
	assert(movies[0].get_actor() == "Daniel Craig");

	srv.srv_delete_movie("No time to die", "Action", "2021", "Daniel Craig");
	std::vector < Movie > movies2 = srv.get_all_from_repo();
	assert(movies2.size() == 0);
}

void test_delete_a_movie_feature_extended_test(Service srv) {
	srv.srv_add_movie("No time to die", "Action", "2021", "Daniel Craig");
	srv.srv_add_movie("Spectre", "Action2", "2015", "D. Craig");
	srv.srv_delete_movie("No time to die", "Action", "2021", "Daniel Craig");

	std::vector < Movie > movies = srv.get_all_from_repo();
	assert(movies.size() == 1);
	if (movies[0].get_title() == "Spectre") {
		assert(movies[0].get_gen() == "Action2");
		assert(movies[0].get_year() == 2015);
		assert(movies[0].get_actor() == "D. Craig");
	}

	try {
		srv.srv_delete_movie("No time to die", "Action", "2021", "Daniel Craig");
	}
	catch (MovieInexistent &error) {
		assert(error.getMessage() == "Movie not found! ");
	}
	std::vector < Movie > movies2 = srv.get_all_from_repo();
	assert(movies2.size() == 1);
	if (movies2[0].get_title() == "Spectre") {
		assert(movies2[0].get_gen() == "Action2");
		assert(movies2[0].get_year() == 2015);
		assert(movies2[0].get_actor() == "D. Craig");
	}
	srv.srv_delete_movie("Spectre", "Action2", "2015", "D. Craig");
}

void test_delete_movie_feature_throw_exception(Service srv) {
	try {
		srv.srv_delete_movie("", "", "", "");
	}
	catch (InvalidMovie &msg) {
		assert(msg.getMessage() == "Invalid title length! Invalid gen length! Invalid year length! Invalid length of the main actor name! ");
	}
	try {
		srv.srv_delete_movie("No time to die", "Action", "2021", "Daniel Craig");
	}
	catch (MovieInexistent &error) {
		assert(error.getMessage() == "Movie not found! ");
	}
	srv.srv_add_movie("No time to die", "Action", "2021", "Daniel Craig");
	srv.srv_add_movie("Spectre", "Action2", "2015", "D. Craig");
	srv.srv_delete_movie("No time to die", "Action", "2021", "Daniel Craig");
	srv.srv_delete_movie("Spectre", "Action2", "2015", "D. Craig");
	try {
		srv.srv_delete_movie("", "", "", "");
	}
	catch (InvalidMovie &msg) {
		assert(msg.getMessage() == "Invalid title length! Invalid gen length! Invalid year length! Invalid length of the main actor name! ");
	}

	try {
		srv.srv_delete_movie("", "", "a2", "");
	}
	catch (InvalidMovie& msg) {
		assert(msg.getMessage() == "Invalid title length! Invalid gen length! Found 1 characters that are not digits in the year entered! Invalid length of the main actor name! ");
	}
}


void test_delete_movie_with_movie_in_cart(Service srv){
	std::ofstream fout("test_movie_file.csv");
	fout.close();
	srv.srv_add_movie("No time to die", "Action", "2021", "Daniel Craig");
	srv.srv_add_movie("Spectre", "Action2", "2015", "D. Craig");
	srv.srv_add_movie("Spectre2", "Action3", "32", "D. Craig");
	
	srv.add_in_cart("Spectre", "Action2", "2015", "D. Craig");
	
	srv.srv_delete_movie("Spectre", "Action2", "2015", "D. Craig");
	
	/// Check if a movie is deleted both from repo and from cart
	std::vector < Movie > movies = srv.get_all_from_repo();
	std::vector < Movie > movies_from_cart = srv.get_all_from_cart();
	assert(movies.size() == 2);
	assert(movies_from_cart.size() == 0);
	for (Movie movie : movies) {
		if (movie.get_title() == "No time to die") {
			assert(movie.get_gen() == "Action");
			assert(movie.get_year() == 2021);
			assert(movie.get_actor() == "Daniel Craig");
		}
		else {
			assert(movie.get_title() == "Spectre2");
			assert(movie.get_gen() == "Action3");
			assert(movie.get_year() == 32);
			assert(movie.get_actor() == "D. Craig");
		}
	}

	/// Check if removing a movie is working from more than one movie in cart
	srv.srv_add_movie("Spectre", "Action2", "2015", "D. Craig");
	srv.add_in_cart("No time to die", "Action", "2021", "Daniel Craig");
	srv.add_in_cart("Spectre", "Action2", "2015", "D. Craig");
	srv.add_in_cart("Spectre2", "Action3", "32", "D. Craig");
	movies_from_cart = srv.get_all_from_cart();
	assert(movies_from_cart.size() == 3);

	srv.srv_delete_movie("Spectre", "Action2", "2015", "D. Craig");

	movies = srv.get_all_from_repo();
	movies_from_cart = srv.get_all_from_cart();
	assert(movies.size() == 2);
	assert(movies_from_cart.size() == 2);
	for (Movie movie : movies) {
		if (movie.get_title() == "No time to die") {
			assert(movie.get_gen() == "Action");
			assert(movie.get_year() == 2021);
			assert(movie.get_actor() == "Daniel Craig");
		}
		else {
			assert(movie.get_title() == "Spectre2");
			assert(movie.get_gen() == "Action3");
			assert(movie.get_year() == 32);
			assert(movie.get_actor() == "D. Craig");
		}
	}
	for (auto movie : movies_from_cart) {
		if (movie.get_title() == "No time to die") {
			assert(movie.get_gen() == "Action");
			assert(movie.get_year() == 2021);
			assert(movie.get_actor() == "Daniel Craig");
		}
		else {
			assert(movie.get_title() == "Spectre2");
			assert(movie.get_gen() == "Action3");
			assert(movie.get_year() == 32);
			assert(movie.get_actor() == "D. Craig");
		}
	}
}
