#pragma once

#ifndef REPO_HEADER
#define REPO_HEADER


#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>
#include "Domain.h"
#include "Utils.h"

class RepoMovies {
protected:
	std::vector <Movie> repo;
public:
	/*
	* Create the repo object with the default constructor
	*/
	RepoMovies() = default;

	/*
	* Copy constructor
	*/
	RepoMovies(const RepoMovies& ot);

	/*
	* Return the number of elements from repo
	*/
	int size() const;

	/*
	* Make imposible the copy of the repo
	*
	* @param other: other repo with movies
	*/
	//void operator=(const RepoMovies& other) = delete;

	/*
	* Return a list of all elements from repo
	*/
	std::vector<Movie> get_all() const;

	/*
	* Add a movie in the repo
	*
	* @param current_movie : a Movie object - the movie that will be added at the end of the repo
	*/
	void push_back(Movie& current_movie);

	/*
	* Delete a movie
	*
	* @param current_movie : a Movie object - the movie that will be removed from the list
	*
	* @throw exception "Movie not found! " if there is no movie with given specs
	*/
	void delete_movie(const Movie& current_movie);

	/*
	* Change the specs of a movie to the specs of another
	*
	* @param current_movie : the movie that will be changed
	* @param new_movie : the movie that will be added instead
	*
	* @throw exception "Movie not found! " if current_movie is not in the list
	*/
	void change_movie(const Movie& current_movie, const Movie& new_movie);

	/*
	* Search for movies with chosen title
	* 
	* @param title - the target title
	* 
	* @return a list of movies that satisfy requirements
	*/
	std::vector<Movie> filter_by_title(const std::string& title) const;

	/*
	* Search for movies with chosen year
	*
	* @param year - the target year
	*
	* @return a list of movies that satisfy requirements
	*/
	std::vector<Movie> filter_by_year(const int& year) const;

	/*
	* Search for a movie in the repo
	*
	* Check if current_movie is in the list of movies
	* 
	* @param current_movie - the movie we look for
	*
	* @return a list of movies that satisfy requirements
	*
	*/
	std::vector<Movie> search_movies(const Movie &current_movie) const;
	
	/*
	* Return the adress of a movie
	*/
	int movie_adress(const Movie& movie);
};


class FileRepoMovies: public RepoMovies {
private:
	std::string filename;
	/*
	* Load the repo from the chosen file into the repo
	*/
	void read_from_file();

	/*
	* Refresh the repo
	*/
	void refresh_repo();

	/*
	* Write on the bask of the repo
	*/
	void write_back();

public:
	/*
	* Make imposible to create a FileRepo that has no file 
	*/
	FileRepoMovies() = delete;

	/*
	* Constructor of the file repo
	* 
	* @param filename : string - the name of the file that will store all movies
	*/
	FileRepoMovies(const std::string& filename) : filename{ filename }{};

	/*
	* Return the iterator for the beginning of the repo
	*/
	std::vector < Movie >::iterator begin();

	/*
	* Copy constructor
	*/
	FileRepoMovies(const FileRepoMovies& ot);

	/*
	* Overwrite the size function from clasic RepoMovies
	*/
	int size();

	/*
	* Overwrite the get_all function from clasic RepoMovies
	*/
	std::vector < Movie > get_all();

	/*
	* Overwrite the push_back function from clasic repo
	*
	* @param current_movie : a Movie object - the movie that will be added at the end of the repo
	*/
	void push_back(Movie& current_movie);

	/*	
	* Overwrite the delete function from clasical repo
	*
	* @param current_movie : a Movie object - the movie that will be removed from the list
	*
	* @throw exception "Movie not found! " if there is no movie with given specs
	*/
	void delete_movie(const Movie& current_movie);

	/*
	* Overwrite the function that change the specs of a movie to the specs of another
	*
	* @param current_movie : the movie that will be changed
	* @param new_movie : the movie that will be added instead
	*
	* @throw exception "Movie not found! " if current_movie is not in the list
	*/
	void change_movie(const Movie& current_movie, const Movie& new_movie);

	/*
	* Overwrite the function that search for movies with chosen title
	*
	* @param title - the target title
	*
	* @return a list of movies that satisfy requirements
	*/
	std::vector<Movie> filter_by_title(const std::string& title);

	/*
	* Overwrite the function that search for movies with chosen year
	*
	* @param year - the target year
	*
	* @return a list of movies that satisfy requirements
	*/
	std::vector<Movie> filter_by_year(const int& year);

	/*
	* Overwrite the function that search for a movie in the repo
	*
	* Check if current_movie is in the list of movies
	*
	* @param current_movie - the movie we look for
	*
	* @return a list of movies that satisfy requirements
	*
	*/
	std::vector<Movie> search_movies(const Movie& current_movie);

	/*
	* Overwrite the function that return the adress of a movie
	* 
	* Return the offset of the movie in repo
	*
	*/
	int movie_adress(const Movie& movie);
};

#endif