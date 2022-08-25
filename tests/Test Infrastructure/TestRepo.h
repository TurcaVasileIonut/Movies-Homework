#pragma once
#include "Repo.h"

#include <assert.h>


class TestRepo {
private:
	RepoMovies repo_movies;
public:
	/*
	* Start all tests for repo
	*/
	void run_all_tests_repo();
};
