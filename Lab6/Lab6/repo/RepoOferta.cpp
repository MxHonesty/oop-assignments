#include "RepoOferta.h"

void RepoOferte::add(const Oferta& de_adaugat){
	this->elems.push_back(de_adaugat);
}

void RepoOferte::remove(int id) noexcept{
	for (auto iter = elems.begin(); iter != elems.end(); iter++) {
		auto& value = *iter;  // value este elementul curent.
		if (value.get_id() == id) {
			elems.erase(iter);
			break;
		}
 	}
}

bool RepoOferte::search(int id) const noexcept{
	for (auto& el : elems)
		if (el.get_id() == id)
			return true;

	return false;
}

const Oferta& RepoOferte::search_element(int id) const{
	for (auto& el : elems) {
		if (el.get_id() == id)
			return el;
	}
	throw "Element not found.";
}

vector<Oferta> RepoOferte::get_all() const{
	return this->elems;
}

void RepoOferte::remove_all() noexcept{
	elems.clear();
}

unsigned int RepoOferte::dim() noexcept{
	return elems.size();
}
