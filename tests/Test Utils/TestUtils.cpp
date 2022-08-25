#include "TestUtils.h"
#include "Utils.h"

#include <assert.h>


void test_convert_number_to_string() {
	assert(convert_number_to_string(123) == "123");
	assert(convert_number_to_string(321) == "321");
	assert(convert_number_to_string(121321) == "121321");
	assert(convert_number_to_string(2314) != "dsa");
}

void test_convert_string_to_number() {
	assert(convert_string_to_number("123") == 123);
	assert(convert_string_to_number("321") == 321);
	assert(convert_string_to_number("121321") == 121321);
	assert(convert_string_to_number("-312") == -312);
}

void run_all_tests_utils() {
	test_convert_number_to_string();
	test_convert_string_to_number();
}