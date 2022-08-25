#include "TestValidators.h"
#include <assert.h>
#include "Exceptions.h"

#include <iostream>


void test_movie_validator_1(ValidatorMovie movie_validator) {

	movie_validator.validate_movie("Spectre", "Action", "2022", "Daniel Craig");

}

void test_movie_validator_2(ValidatorMovie movie_validator) {
	try {
		movie_validator.validate_movie("", "Action", "2022", "Daniel Craig");
	}
	catch (InvalidMovie& msg) {
		assert(msg.getMessage() == "Invalid title length! ");
	}
}

void test_movie_validator_3(ValidatorMovie movie_validator) {
	try {
		movie_validator.validate_movie("", "", "", "");
	}
	catch (InvalidMovie& msg) {
		assert(msg .getMessage()  == "Invalid title length! Invalid gen length! Invalid year length! Invalid length of the main actor name! ");
	}
}

void test_movie_validator_4(ValidatorMovie movie_validator) {
	try {
		movie_validator.validate_movie("", "", "a2", "");
	}
	catch (InvalidMovie& msg) {
		assert(msg.getMessage() == "Invalid title length! Invalid gen length! Found 1 characters that are not digits in the year entered! Invalid length of the main actor name! ");
	}
}

void test_movie_validator_5(ValidatorMovie movie_validator) {
	try {
		movie_validator.validate_movie("", "Action", "-2022", "Daniel Craig");
	}
	catch (InvalidMovie& msg) {
		assert(msg.getMessage() == "Invalid title length! ");
	}
}

void TestValidators::test_movie_validator() {
	test_movie_validator_1(movie_validator);
	test_movie_validator_2(movie_validator);
	test_movie_validator_3(movie_validator);
	test_movie_validator_4(movie_validator);
	test_movie_validator_5(movie_validator);
}

void TestValidators::test_is_number() {

	movie_validator.is_number("123");
	movie_validator.is_number("-123");

	try {
		movie_validator.is_number("aa");
	}
	catch (InvalidMovie& msg) {
		assert(msg.getMessage() == "Found 2 characters that are not digits in the year entered! ");
	}
	try {
		movie_validator.is_number("");
	}
	catch (InvalidMovie& msg) {
		assert(msg.getMessage() == "Invalid year length! ");
	}
}

void TestValidators::run_all_tests_validators() {
	test_movie_validator();
	test_is_number();
}