#include "TestService.h"
#include "Exceptions.h"


void test_filter_by_title_test1();

void test_filter_by_title_test2();

void TestService::test_filter_by_title() {
	test_filter_by_title_test1();
	test_filter_by_title_test2();
}

void test_filter_by_title_test1() {
	std::ofstream fout;
	fout.open("test_movies_file.csv");
	fout.close();
	FileRepoMovies repo_movies{ "test_movies_file.csv" };
	ValidatorMovie validator_movies;
	CartMovies cart_movies;
	Service srv{ repo_movies, cart_movies, validator_movies };
	srv.srv_add_movie("No time to die", "Action", "2021", "Daniel Craig");
	srv.srv_add_movie("Spectre", "Action", "2015", "D. Craig");
	srv.srv_add_movie("Spectre", "Action3", "2012", "D. Craig");
	srv.srv_add_movie("No time to die2", "Action", "2021", "Daniel Craig");
	srv.srv_add_movie("Spectre", "Action4", "2013", "D. Craig");

	std::vector < Movie > movies = srv.filter_by_title("Spectre");
	assert(movies.size() == 3);
	int cnt_covered = 0;
	for (auto movie : movies) {
		assert(movie.get_title() == "Spectre");
		if (movie.get_gen() == "Action") {
			assert(movie.get_year() == 2015);
			assert(movie.get_actor() == "D. Craig");
			cnt_covered++;
			continue;
		}
		if (movie.get_gen() == "Action3") {
			assert(movie.get_year() == 2012);
			assert(movie.get_actor() == "D. Craig");
			cnt_covered++;
			continue;
		}
		if (movie.get_gen() == "Action4") {
			assert(movie.get_year() == 2013);
			assert(movie.get_actor() == "D. Craig");
			cnt_covered++;
		}
	}
	assert(cnt_covered == 3);

	try {
		movies = srv.filter_by_title("");
	}
	catch (InvalidMovie& error) {
		assert(error.getMessage() == "Invalid title length! ");
		assert(true);
	}
}

void test_filter_by_title_test2() {
	std::ofstream fout;
	fout.open("test_movies_file.csv");
	fout.close();
	FileRepoMovies repo_movies{ "test_movies_file.csv" };
	ValidatorMovie validator_movies;
	CartMovies cart_movies;
	Service srv{ repo_movies, cart_movies, validator_movies };
	srv.srv_add_movie("No time to die", "Action", "2021", "Daniel Craig");
	srv.srv_add_movie("Spectre", "Action", "2015", "D. Craig");
	srv.srv_add_movie("Spectre", "Action3", "2012", "D. Craig");
	srv.srv_add_movie("No time to die2", "Action", "2021", "Daniel Craig");
	srv.srv_add_movie("Spectre", "Action4", "2013", "D. Craig");

	std::vector < Movie > movies = srv.filter_by_title("Game of Thrones");
	assert(movies.size() == 0);
}
