#include "TestService.h"
#include "Exceptions.h"

void test_undo_adding();

void test_undo_remove();

void test_undo_change();

void TestService::test_undo() {
	test_undo_adding();
	test_undo_remove();
	test_undo_change();
}

void test_undo_adding() {
	std::ofstream fout;
	fout.open("test_movies_file.csv");
	fout.close();
	FileRepoMovies repo_movies{ "test_movie_file.csv" };
	ValidatorMovie validator_movies;
	CartMovies cart_movies;
	Service srv{ repo_movies, cart_movies, validator_movies };
	srv.srv_add_movie("No time to die", "Action", "2021", "Daniel Craig");
	srv.srv_add_movie("Spectre", "Action2", "2015", "D. Craig");
	srv.srv_add_movie("Fast and furious", "Racing", "2018", "Vin Diesel");

	std::vector < Movie > movies = srv.get_all_from_repo();
	assert(movies.size() == 3);
	
	srv.undo(); 
	movies = srv.get_all_from_repo();
	assert(movies.size() == 2);

	srv.undo();
	movies = srv.get_all_from_repo();
	assert(movies.size() == 1);

	srv.undo();
	movies = srv.get_all_from_repo();
	assert(movies.size() == 0);

	try {
		srv.undo();
		assert(false);
	}
	catch(InsuficientMovies &msg) {
		assert(msg.getMessage() == "The action history is empty! ");
	}
}


void test_undo_remove() {
	std::ofstream fout;
	fout.open("test_movies_file.csv");
	fout.close();
	FileRepoMovies repo_movies{ "test_movie_file.csv" };
	ValidatorMovie validator_movies;
	CartMovies cart_movies;
	Service srv{ repo_movies, cart_movies, validator_movies };
	srv.srv_add_movie("No time to die", "Action", "2021", "Daniel Craig");
	srv.srv_add_movie("Spectre", "Action2", "2015", "D. Craig");
	srv.srv_add_movie("Fast and furious", "Racing", "2018", "Vin Diesel");

	std::vector < Movie > movies = srv.get_all_from_repo();
	assert(movies.size() == 3);

	srv.srv_delete_movie("Spectre", "Action2", "2015", "D. Craig");

	movies = srv.get_all_from_repo();
	assert(movies.size() == 2);

	srv.undo();

	movies = srv.get_all_from_repo();
	assert(movies.size() == 3);
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
			continue;
		}
		assert(movie.get_title() == "Fast and furious");
		assert(movie.get_gen() == "Racing");
		assert(movie.get_year() == 2018);
		assert(movie.get_actor() == "Vin Diesel");
	}
}

void test_undo_change() {
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

	srv.undo();
	
	movies = srv.get_all_from_repo();
	assert(movies.size() == 2);
	assert(movies[0].get_title() == "No time to die");
	assert(movies[0].get_gen() == "Action");
	assert(movies[0].get_year() == 2021);
	assert(movies[0].get_actor() == "Daniel Craig");

}