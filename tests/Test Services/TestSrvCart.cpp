#include "TestService.h"
#include <iostream>
#include <fstream>

void test_add_cart_srv();

void test_clear_cart_srv();

void test_add_random_movies_cart();

void TestService::test_cart() {
	test_add_cart_srv();
	test_clear_cart_srv();
	test_add_random_movies_cart();
}

void test_add_cart_srv(){
	std::ofstream fout;
	fout.open("test_movies_file.csv");
	fout.close();
	FileRepoMovies repo_movies{ "test_movies_file.csv" };
	ValidatorMovie validator_movies;
	CartMovies cart_movies;
	Service srv{ repo_movies, cart_movies, validator_movies };
	srv.srv_add_movie("No time to die", "Action", "2021", "Daniel Craig");
	srv.srv_add_movie("Spectre", "Action2", "2015", "D. Craig");
	 
	srv.add_in_cart("No time to die", "Action", "2021", "Daniel Craig");

	assert(srv.cart_size() == 1);

	srv.add_in_cart("Spectre", "Action2", "2015", "D. Craig");

	assert(srv.cart_size() == 2);
}

void test_clear_cart_srv(){
	std::ofstream fout;
	fout.open("test_movies_file.csv");
	fout.close();
	FileRepoMovies repo_movies{ "test_movies_file.csv" };
	ValidatorMovie validator_movies;
	CartMovies cart_movies;
	Service srv{ repo_movies, cart_movies, validator_movies };
	srv.srv_add_movie("No time to die", "Action", "2021", "Daniel Craig");
	srv.srv_add_movie("Spectre", "Action2", "2015", "D. Craig");

	srv.add_in_cart("No time to die", "Action", "2021", "Daniel Craig");
	srv.add_in_cart("Spectre", "Action2", "2015", "D. Craig");

	srv.clear_cart();

	assert(srv.cart_size() == 0);
}

void test_add_random_movies_cart(){
	std::ofstream fout2;
	fout2.open("test_movies_file.csv");
	fout2.close();
	FileRepoMovies repo_movies{ "test_movies_file.csv" };
	ValidatorMovie validator_movies;
	CartMovies cart_movies;
	Service srv{ repo_movies, cart_movies, validator_movies };
	for (int i = 1; i <= 10; i++) {
		std::string title = "No time to die" + convert_number_to_string(i);
		srv.srv_add_movie(title, "Action", "2021", "Daniel Craig");
	}

	try {
		srv.add_random_movies_in_cart(500);
		assert(false);
	}
	catch(InsuficientMovies &msg){
		assert(msg.getMessage() == "There are less than 500 movies in repo that are not in cart! ");
	}

	srv.add_random_movies_in_cart(4);

	assert(srv.cart_size() == 4);

	std::vector < Movie > elems_from_cart = srv.get_all_from_cart();
	std::vector <std::string > titles;
	for (auto it : elems_from_cart) {
		assert(it.get_gen() == "Action");
		assert(it.get_year() == 2021);
		assert(it.get_actor() == "Daniel Craig");
		titles.push_back(it.get_title());
	}
	for (int i = titles.size() - 1; i >= 1; i--)
		for (int j = i - 1; j >= 0; j--)
			assert(titles[i] != titles[j]);

	srv.save_cart_in_csv("test_cart.csv");

	std::ifstream fin;
	fin.open("test_cart.csv");
	for (int i = 0; i < elems_from_cart.size(); i++) {
		std::string input;
		std::getline(fin, input);

		std::string title = get_first_field(input, char(','));
		std::string gen = get_first_field(input, char(','));
		std::string year = get_first_field(input, char(','));
		std::string actor = get_first_field(input, char(','));

		assert((elems_from_cart[i]).get_title() == title);
		assert((elems_from_cart[i]).get_gen() == gen);
		assert((elems_from_cart[i]).get_year() == convert_string_to_number(year));
		assert((elems_from_cart[i]).get_actor() == actor);
	}
	fin.close();

	std::ofstream fout;
	fout.open("test_cart.csv");
	fout.close();
}