#pragma once

#ifndef SERVICE
#define SERVICE

#include "Repo.h"
#include "Cart.h"
#include "Validators.h"
#include "Utils.h"
#include "Exceptions.h"
#include "Undo.h"

#include <algorithm>
#include <random>
#include <set>
#include <vector>
#include <fstream>


class Service {
private:
	FileRepoMovies repo_movies;
	CartMovies cart_movies;
	ValidatorMovie validator_movie;
	std::vector < UndoActions* > Actions;
public:
	Service() = delete;

	/*
	* Create a service object
	*/
	Service(const FileRepoMovies& repo_movies, const CartMovies& cart_movies, const ValidatorMovie& validator_novie) : repo_movies{ repo_movies }, cart_movies{ cart_movies }, validator_movie{ validator_novie }{};


	/*
	* Return a list of Movie object with all movies from the repo
	*/
	std::vector<Movie> get_all_from_repo();


	/*
	* Add a new movie in repo if the parameters are suitable for a movie object
	*
	* @param title : string - the title of the movie
	* @param gen : string - the gen of the movie
	* @param year : string - the year of launch of the movie
	* @param actor : string - the name of the main actor of the movie
	*
	* @throw string error if the parameters are not suitable
	*/
	void srv_add_movie(const std::string& title, const std::string& gen, const std::string& year, const std::string& actor);


	/*
	* Delete a movie from the repo
	*
	* @param title : string - the title of the movie
	* @param gen : string - the gen of the movie
	* @param year : string - the year of launch of the movie
	* @param actor : string - the name of the main actor of the movie
	*
	* @throw string error if the parameters are not suitable
	* @throw string error if there is no movie with that parameters
	*/
	void srv_delete_movie(const std::string& title, const std::string& gen, const std::string& year, const std::string& actor);


	/*
	* Change the parameters of a selected movie
	*
	* @param title : string - the title of the movie
	* @param gen : string - the gen of the movie
	* @param year : string - the year of launch of the movie
	* @param actor : string - the name of the main actor of the movie
	*
	* @param new_title : string - the new title of the movie
	* @param new_gen : string - the new gen of the movie
	* @param new_year : string - the new year of launch of the movie
	* @param new_actor : string - the new name of the main actor of the movie
	*
	* @throw string error if the parameters are not suitable
	* @throw string error if there is no movie with that parameters
	*/
	void srv_change_movie(const std::string& title, const std::string& gen, const std::string& year, const std::string& actor, const std::string& new_title, const std::string& new_gen, const std::string& new_year, const std::string& new_actor);

	/*
	* Check if the movie is in the repo
	*
	* @param title: the target title
	* @param gen: the target gen
	* @param year: the target year
	* @param actor: the target actor
	*
	* @return true if the movie is in the repo and false if the movie is not in the repo
	*
	* @throw string error if the parameters are not suitable
	*/
	bool search_movie(const std::string& title, const std::string& gen, const std::string& year, const std::string& actor);

	/*
	* Filter and returns the list of the movies with a fixed title
	*
	* @param title - string - the fixed title
	*
	* @return a list of movies
	*
	* @throw "Invalid title length! " if the length of the title is 0
	*/
	std::vector < Movie > filter_by_title(const std::string& title);

	/*
	* Filter and returns the list of the movies with a fixed launch year
	*
	* @param year - string - the fixed year
	*
	* @return a list of movies
	*
	* @throw string error
	*/
	std::vector < Movie > filter_by_year(const std::string& year);

	/*
	* Sort the movies from the repo ascending according to chosen criteria and return the list of sorted movies
	*
	* @param criteria - int
	* @param criteria = 1 - sort by title
	* @param criteria = 2 - sort by	main actor
	* @param criteria = 3 - sort by launcing year ascending and by gen when years are equal
	*/
	std::vector < Movie > sorting(const int& criteria);

	/*
	* Undo the last command that changed the repo
	*/
	void undo();


	/*
	* Return the number of products from cart
	*/
	int cart_size() const;

	/*
	* Return a vector with all movies from cart
	*/
	std::vector < Movie > get_all_from_cart();

	/*
	* Add a new product in the cart
	* 
	* @param title : string - the title of the movie
	* @param gen : string - the gen of the movie
	* @param year : string - the year of launch of the movie
	* @param actor : string - the name of the main actor of the movie
	* 
	*/
	void add_in_cart(const std::string& title, const std::string& gen, const std::string& year, const std::string& actor);
	
	/*
	* Remove all elements from cart
	*/
	void clear_cart();

	/*
	* Add cnt random movies in cart
	* 
	* @param cnt - int - the number of movies that will be added in cart
	* 
	* @throw InsuficientMovies - if repo has less than cnt movies that are not already in cart
	*/
	void add_random_movies_in_cart(const int& cnt);

	/*
	* Save the content from cart in a csv file
	*/
	void save_cart_in_csv(std::string filename);


	CartMovies& get_cart(){
		return cart_movies;
	}

	~Service();
};

#endif // !SERVICE