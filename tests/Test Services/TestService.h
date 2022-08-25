#pragma once

#include "Service.h"
#include <assert.h>


class TestService {
private:
	FileRepoMovies repo_movies{ "test_movie_file.csv" };
	ValidatorMovie validator_movies;
	CartMovies cart_movies;
	Service srv{ repo_movies, cart_movies, validator_movies };
public:
	/*
	* Test if the feature of adding a new movie in repo is working properly
	*/
	void test_add_movie_feature();

	/*
	* Test if the feature of deleting a movie is working properly
	*/
	void test_delete_movie_feature();

	/*
	* Test if the feature of changing a movie is working properly
	*/
	void test_change_movie_feature();

	/*
	* Tests if the feature of searching a certain movie is working properly
	*/
	void test_check_for_movie();

	/*
	* Tests if filter by title feature is working properly
	*/
	void test_filter_by_title();

	/*
	* Tests if filter by year feature is working properly
	*/
	void test_filter_by_year();

	/*
	* Tests if the sorting feature is working properly
	*/
	void test_sorting();

	/*
	* Test if cart features are working
	*/
	void test_cart();

	/*
	* Test if undo feature is working
	*/
	void test_undo();

	/*
	* Run all tests for service
	*/
	void run_all_tests_service();
};