#include "Domain.h"
#include "Utils.h"


std::string Movie::get_actor() const {
	return this->actor;
}

void Movie::set_title(const std::string& new_title) {
	this->title = new_title;
}

void Movie::set_gen(const std::string& new_gen) {
	this->gen = new_gen;
}

void Movie::set_year(const int& new_year) {
	this->year = new_year;
}

void Movie::set_actor(const std::string& new_actor) {
	this->actor = new_actor;
}

std::string Movie::get_gen() const {
	return this->gen;
}

Movie::Movie(const std::string& title, const std::string& gen, const std::string& year, const std::string& actor) {
	this->title = title;
	this->gen = gen;
	int current_year = 0;
	for (auto digit : year)
		current_year = current_year * 10 + digit - '0';
	this->year = current_year;
	this->actor = actor;
};

std::string Movie::get_title() const {
	return this->title;
}

int Movie::get_year() const {
	return this->year;
}

bool Movie::operator==(const Movie& other) {
	return other.gen == this->gen && other.title == this->title && other.actor == this->actor && other.year == this->year;
}

void Movie::operator=(const Movie& other) {
	this->title = other.title;
	this->gen = other.gen;
	this->year = other.year;
	this->actor = other.actor;
}

std::string Movie::string_movie() const {
	std::string result = "";
	result += this->title;
	result += " ";
	result += this->gen;
	result += " ";
	result += convert_number_to_string(this->year);
	result += " ";
	result += this->actor;
	return result;
}
