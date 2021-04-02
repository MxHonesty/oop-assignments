#include "RepoOferta.h"
#include <stdexcept>

void RepoOferte::add(const Oferta& de_adaugat){
	this->elems.add(de_adaugat);
}

void RepoOferte::remove(const int id) {
	int pozitie = 0;
	for (const auto& el : this->elems) {
		if (el.get_id() == id) {
			this->elems.remove(pozitie);
			break;
		}
		pozitie++;
	}
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
	for (const auto& el : elems)
		if (el.get_id() == id)
			return true;

	return false;
}

const Oferta& RepoOferte::search_element(const int id) const{
	for (auto& el : elems) {
		if (el.get_id() == id)
			return el;
	}
	throw std::domain_error{"Element not found"};
}

VectorDinamic<Oferta> RepoOferte::get_all() const{
	return this->elems;
}

const VectorDinamic<Oferta>& RepoOferte::afisare() const noexcept {
	return this->elems;
}

void RepoOferte::remove_all() noexcept{
	elems.clear();
}

int RepoOferte::dim() noexcept{
	return elems.dim();
}
