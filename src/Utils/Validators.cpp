#include "Validators.h"
#include "Exceptions.h"

void ValidatorMovie::validate_movie(const std::string& title, const std::string& gen, const std::string& year, const std::string& actor) {
	std::string errors = "";
	if (title.length() < 1)
		errors += "Invalid title length! ";

	if (gen.length() < 1)
		errors += "Invalid gen length! ";

	int nr_not_digits = 0;
	for (auto character : year)
		if (character < '0' || character > '9')
			nr_not_digits++;

	if (year.length() >= 1) {
		if (year[0] == '-')
			nr_not_digits--;
	}

	if (nr_not_digits)
		errors += "Found " + std::to_string(nr_not_digits) + " characters that are not digits in the year entered! ";

	if (year.length() < 1 || year.length() >= 10)
		errors += "Invalid year length! ";

	if (actor.length() < 1)
		errors += "Invalid length of the main actor name! ";

	if (errors.length() > 0)
		throw InvalidMovie(errors);
}

void ValidatorMovie::is_number(const std::string& number) {
	std::string errors = "";

	int nr_not_digits = 0;
	for (auto character : number)
		if (character < '0' || character > '9')
			nr_not_digits++;

	if (number.length() >= 1) {
		if (number[0] == '-')
			nr_not_digits--;
	}

	if (nr_not_digits)
		errors += "Found " + std::to_string(nr_not_digits) + " characters that are not digits in the year entered! ";

	if (number.length() < 1 || number.length() >= 10)
		errors += "Invalid year length! ";

	if (errors.length() > 0)
		throw InvalidMovie(errors);
}