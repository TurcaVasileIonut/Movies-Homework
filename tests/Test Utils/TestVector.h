#pragma once
#include "Vector.h"

#include <assert.h>


class TestVector {
public:
	/*
	* Test if can be added all data types in vector
	*/
	void test_push_back();

	/*
	* Test if the last element can be poped from vector
	*/
	void test_pop_back();

	/*
	* Test begin function
	*/
	void test_begin();

	/*
	* Test end function
	*/
	void test_end();

	/*
	* Test size function
	*/
	void test_size();

	/*
	* Tests the iterator
	*/
	void test_iterator();

	/*
	* Run all tests for vector
	*/
	void run_all_tests();
};

