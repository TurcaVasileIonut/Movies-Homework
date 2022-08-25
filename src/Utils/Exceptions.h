#pragma once


#include <string>


#ifndef EXCEPTION_HEADER
#define EXCEPTION_HEADER



class MovieInexistent {
private:
	std::string message;
public:
	MovieInexistent(std::string message) : message(message) {}
	const std::string& getMessage() const {
		return message;
	}
};

class InvalidMovie {
private:
	std::string message;
public:
	InvalidMovie(std::string message) : message(message) {}
	const std::string& getMessage() const {
		return message;
	}
};

class MovieExistent {
private:
	std::string message;
public:
	MovieExistent(std::string message) : message(message) {}
	const std::string& getMessage() const {
		return message;
	}
};

class InsuficientMovies {
private:
	std::string message;
public:
	InsuficientMovies(std::string message) : message(message) {}
	const std::string& getMessage() const {
		return message;
	}
};

#endif // !EXCEPTION_HEADER