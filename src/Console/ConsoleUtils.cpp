#include "ConsoleUtils.h"

std::string get_title_from_user() {
	std::string title;
	std::cout << "Please give the title: ";
	std::getline(std::cin, title);
	return title;
}

std::string get_gen_from_user() {
	std::string gen;
	std::cout << "Please give the gen: ";
	std::getline(std::cin, gen);
	return gen;
}

std::string get_year_from_user() {
	std::string year;
	std::cout << "Please give the year: ";
	std::getline(std::cin, year);
	return year;
}

std::string get_actor_from_user() {
	std::string actor;
	std::cout << "Please give the name of the main actor: ";
	std::getline(std::cin, actor);
	return actor;
}
