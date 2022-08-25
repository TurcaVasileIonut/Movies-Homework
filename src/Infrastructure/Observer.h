#pragma once
#include <vector>
#include <algorithm>

#ifndef OBSERVER_HEADER
#define OBSERVER_HEADER

/*
 *	Abstract class
 *	update method need to be implemented by observers
 */
class Observer {
public:
	virtual void update() = 0;
};

class Observable {
private:
	std::vector < Observer* > observers;
public:
	/*
	 * Add a new element in the list of observers
	 */
	void addObserver(Observer* observer);

	/*
	 * Notify all observers that it was a change at the level of cart
	 */
	void notify();
};


#endif // !OBSERVER_HEADER

