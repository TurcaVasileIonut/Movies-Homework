#pragma once
#include <vector>

#include "Domain.h"
#include "Observer.h"

#ifndef CART_HEADER
#define CART_HEADER

class CartMovies : public Observable {
private:
	std::vector < int > products;
public:
	/*
	* Default, basic constructor for cart
	*/
	CartMovies() = default;

	/*
	* Return the number of movies from cart as an int
	*/
	int size() const;

	/*
	* Return all elements from cart
	*/
	std::vector < int > get_all() const;

	/*
	* Add a new movie adress in the cart
	*
	* @param it : the adress of the movie that will be added
	*/
	void push_back(const int& it);

	/*
	* Delete all movies from cart
	*/
	void clear();

	/*
	* Remove a movie from the cart
	* @param movie_pos - the movie we want to remove from the cart. We sent as parameter the adress from the repo
	*/
	void remove_movie(int movie_pos);
};

#endif