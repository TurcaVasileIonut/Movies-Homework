#include "Observer.h"

void Observable::addObserver(Observer* observer){
	observers.push_back(observer);
}

void Observable::notify(){
	for (auto obs : observers)
		obs->update();
}