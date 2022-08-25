#pragma once

#include "Validators.h"

class TestValidators {
private:
	ValidatorMovie movie_validator;
public:

	/*
	* Test if the movie validator is working properly
	*/
	void test_movie_validator();

	/*
	* Test if number validator is working
	*/
	void test_is_number();

	/*
	* Run all tests for validators
	*/
	void run_all_tests_validators();
};
