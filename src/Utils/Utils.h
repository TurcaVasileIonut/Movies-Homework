#pragma once
#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <string>
#include "Domain.h"

/*
* Take the first field from input. The first field will be removed from the input
*
* @param : input - the base string, that contains all fields
* @param : delim - field separator
*
* @return : the first field as a string
*/
std::string get_first_field(std::string& input, const char& delim);

/*
* Convert current number to string
*/
std::string convert_number_to_string(int number);

/*
* Convert current string to int number
*/
int convert_string_to_number(std::string string_number);

/*
* Return 1 if the title of a is lexicografically smaller than the title of b and 0 otherwise
*/
bool cmp_by_title(const Movie& a, const Movie& b);

/*
* Return 1 if the actor of a is lexicografically smaller than the title of b and 0 otherwise
*/
bool cmp_by_actor(const Movie& a, const Movie& b);

/*
* Return 1 if the launch year of the a is smaller than the launch year of the b
* Return 0 if the launch year of the b is greater than the launch year of the b
* if a.year == b.year return 1 if the gen of the a is lexicografically smaller than the gen of b and 0 otherwise
*/
bool cmp_by_year_and_gen(const Movie& a, const Movie& b);

#endif // !UTILS_HEADER