#ifndef DOMAIN_HEADER
#define DOMAIN_HEADER

#include <string>

class Movie {
private:
	std::string title;
	std::string gen;
	int year;
	std::string actor;
public:

	/*
	* Default constructor
	*/
	Movie() {
		year = 0;
	};

	/*
	* Create the movie object using an int year
	* 
	* @param title : string - the title of the movie
	* @param gen : string - the gen of the movie
	* @param year : int - the year of launch of the movie
	* @param actor : string - the name of the main actor of the movie
	* 
	*/
	Movie(const std::string& title, const std::string& gen, const int& year, const std::string& actor) : title{ title }, gen{ gen }, actor{ actor }, year{ year }{};

	/*
	* Create the movie object using a string year. The year will be stored as int
	* 
	* @param title : string - the title of the movie
	* @param gen : string - the gen of the movie
	* @param year : string - the year of launch of the movie
	* @param actor : string - the name of the main actor of the movie
	*/
	Movie(const std::string& title, const std::string& gen, const std::string& year, const std::string& actor);

	/*
	* Current movie take the value of other ( copy constructor)
	* 
	* @param other : Movie object, the movie that will substitute current movie
	*/
	Movie(const Movie& other) : title{ other.title }, gen{ other.gen }, actor{ other.actor }, year{ other.year }{}

	/*
	* Return the title of the movie as a string
	* 
	* @return string
	*/
	std::string get_title() const;

	/*
	* Return the gen of the Movie as a string
	* 
	* @return
	*/
	std::string get_gen() const;

	/*
	* Return the year of the movie as an int
	* 
	* @return int
	*/
	int get_year() const;

	/*
	* Return the name of the main actor of the movie as string
	* 
	* @return string
	*/
	std::string get_actor() const;

	/*
	* Change the title of the current movie
	* 
	* @param new_title : string - the new title
	*/
	void set_title(const std::string& new_title);

	/*
	* Change the gen of the current movie
	* 
	* @param new_gen : string - the new gen
	*/
	void set_gen(const std::string& new_gen);

	/*
	* Change the year of the current movie
	* 
    * @param year : int - the new year
	*/
	void set_year(const int& new_year);

	/*
	* Change the name of the main actor of the current movie
	* 
	* @param new_actor : string - the new main actor
	*/
	void set_actor(const std::string& new_actor);

	/*
	* Check if two movies are the same movie (identical parameters)
	* 
	* @param other : movie object - the movie we compare with
	* 
	* @return 1 if current movie and other are identical and 0 otherwise
	*/
	bool operator==(const Movie& other);

	/*
	* Current movie take the values of other
	* 
	* @param other : movie object - the movie we compare with
	*/
	void operator=(const Movie& other);

	/*
	* Create a string with the parameters of the current movie
	* format: "Title Gen Year Main_Actor"
	* 
	* @return: string 
	*/
	std::string string_movie() const;
};

#endif
