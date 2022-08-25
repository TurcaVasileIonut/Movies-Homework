#pragma once

#ifndef VALIDATORS_HEADER
#define VALIDATORS_HEADER

#include <string>
#include <exception>

class ValidatorMovie {
public:
	/*
	* Check if the parameters are suitable for a movie
	*
	* @param title : string - the title of the movie
	* @param gen : string - the gen of the movie
	* @param year : string - the year of launch of the film
	* @param actor : string - the name of the main actor of the film
	*
	* @throw string error if parameters are not suitable
	*/
	void validate_movie(const std::string& title, const std::string& gen, const std::string& year, const std::string& actor);

	/*
	* Cheack if a string can be transformed into a number
	*
	* @param number: string - the string we check
	*
	* @throw string error if the string is not compatible for a string
	*/
	void is_number(const std::string& number);
};

#endif // !VALIDATORS_HEADER