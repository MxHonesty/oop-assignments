#include "RepoOferta.h"
#include <stdexcept>

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

void RepoOferte::update(int id, const Oferta& new_oferta){
	for (auto& el : elems) {
		if (el.get_id() == id) {
			el.set_denumire(new_oferta.get_denumire());
			el.set_destinatie(new_oferta.get_destinatie());
			el.set_tip(new_oferta.get_tip());
			el.set_pret(new_oferta.get_pret());
			break;
		}
	}
}

bool RepoOferte::search(int id) const noexcept{
	for (const auto& el : elems)
		if (el.get_id() == id)
			return true;

	return false;
}

const Oferta& RepoOferte::search_element(int id) const{
	for (auto& el : elems) {
		if (el.get_id() == id)
			return el;
	}
	throw std::domain_error{"Element not found"};
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
