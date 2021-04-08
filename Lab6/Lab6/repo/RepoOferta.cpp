#include "RepoOferta.h"
#include <stdexcept>

void RepoOferte::add(const Oferta& de_adaugat){
	this->elems.push_back(de_adaugat);
}

void RepoOferte::remove(const int id) {
	auto de_sters = std::remove_if(elems.begin(), elems.end(), 
		[id](const Oferta& el) noexcept {return el.get_id() == id; });
	
	if (de_sters != elems.end())
		elems.erase(de_sters);
}

void RepoOferte::update(const int id, const Oferta& new_oferta){
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

bool RepoOferte::search(const int id) const{
	auto gasit = std::find_if(elems.begin(), elems.end(),
		[id](const Oferta& el) noexcept {return el.get_id() == id; });

	if (gasit == elems.end())
		return false;
	else
		return true;
}

const Oferta& RepoOferte::search_element(const int id) const{
	auto gasit = std::find_if(elems.begin(), elems.end(), 
		[id](const Oferta& el) noexcept {return el.get_id() == id; });

	if (gasit == elems.end())
		throw std::domain_error{ "Element not found" };
	else
		return *gasit;
}

vector<Oferta> RepoOferte::get_all() const{
	return this->elems;
}

const vector<Oferta>& RepoOferte::afisare() const noexcept {
	return this->elems;
}

void RepoOferte::remove_all() noexcept{
	elems.clear();
}

unsigned RepoOferte::dim() noexcept{
	return elems.size();
}
