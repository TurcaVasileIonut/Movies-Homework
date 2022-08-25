#pragma once
#include "Repo.h"

#include <iostream>


#ifndef UNDO
#define UNDO


class UndoActions {

public:
	virtual void doUndo() = 0;
	
	/*
	* Virtual destructor
	*/
	virtual ~UndoActions() {};
};


class UndoAdauga: public UndoActions {
private:
	Movie added_movie;
	FileRepoMovies& repo;
public:
	/*
	* Constructor for adding history
	*/
	UndoAdauga(FileRepoMovies& repo, const Movie& current_movie) :repo{ repo }, added_movie{ current_movie }{};

	/*
	* Undo function for adding
	*/
	void doUndo() override;
};

class UndoRemove : public UndoActions {
private:
	Movie removed_movie;
	FileRepoMovies& repo;
public:
	/*
	* Constructor for removing history
	*/
	UndoRemove(FileRepoMovies& repo, const Movie& current_movie) : repo{ repo }, removed_movie{ current_movie }{};

	/*
	* Undo function for remove
	*/
	void doUndo() override;
};

class UndoChange : public UndoActions {
private:
	Movie old_movie;
	Movie new_movie;
	FileRepoMovies& repo;
public:
	/*
	* Constructor for change function
	*/
	UndoChange(FileRepoMovies& repo, const Movie& old_movie, const Movie& new_movie) :repo{ repo }, old_movie{ old_movie }, new_movie{ new_movie }{};
	
	/*
	* Undo function for change
	*/
	void doUndo() override;
};

#endif