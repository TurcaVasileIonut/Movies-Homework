#include "Cart.h"

int CartMovies::size() const{
	return products.size();
}

std::vector < int > CartMovies::get_all() const{
	return products;
}

void CartMovies::push_back(const int &it){
	products.push_back(it);
	notify();
}

void CartMovies::clear(){
	products.clear();
	notify();
}

void CartMovies::remove_movie(int movie_pos){
	std::vector < int >::iterator poz_to_delete = find(products.begin(), products.end(), movie_pos);
	if(poz_to_delete != products.end())
		products.erase(poz_to_delete);
	notify();
}
