#pragma once
#include "Service.h"
#include "Validators.h"
#include "Utils.h"
#include "ConsoleUtils.h"
#include <iostream>



class Console {
private:
	Service srv;
public:
	Console(const Service &service) : srv{ service } {};

	/*
	* Print all elements
	*/
	void ui_print_all_elements();

	/*
	* Take the parameters of a movie from the user and add the movie in repo
	*/
	void ui_add_element();

	/*
	* Take 2 movies from the user and change the first one into the second one
	*/
	void ui_change();

	/*
	* Take a movie parameters of a movie and remove it from the repo
	*/
	void ui_remove();

	/*
	* Check if a movie is in the repo
	*/
	void ui_check_movie_in_repo();

	/*
	* Print all movies filtered by chosen criteria(by user) between title and year
	*/
	void ui_filter();

	/*
	* Print all movies sorted by chosen criteria
	*/
	void ui_sort();

	/*
	* The GUI part for the undo command
	*/
	void ui_undo();

	/*
	* Starts the admin console
	*/
	void run_admin_console();

	/*
	* Start the user console
	*/
	void run_user_console();

	/*
	* Add a new movie in the cart
	*/
	void ui_add_movie_in_cart();

	/*
	* Take a number from user and generate random movie in cart
	*/
	void ui_generate_cart();

	/*
	* Take a filename from user and save the cart
	*/
	void ui_save_cart();

	/*
	* Start the opening console
	*/
	void run_super_console();
};
