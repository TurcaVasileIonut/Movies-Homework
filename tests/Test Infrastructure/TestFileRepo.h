#pragma once
#include "Repo.h"
#include <assert.h>

#include <fstream>


class TestFileRepo{
private:
	FileRepoMovies repo{"test_movie_file.csv"};
public:

	TestFileRepo() {
		std::ofstream fout;
		fout.open("test_movie_file.csv");
		fout.close();
	};

	void test_get_all();

	void test_delete_a_movie();

	void test_change_a_movie();

	void test_filter_by_title();

	void test_filter_by_year();
	/*
	* Start all tests for repo
	*/
	void run_all_tests_repo();
};
