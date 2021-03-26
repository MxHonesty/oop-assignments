#include "ServiceOferta.h"
#include <stdexcept>
#include <algorithm>

void ServiceOferta::adaugare(string denumire, string destinatie, string tip, int pret){
	Oferta new_of{this->id, denumire, destinatie, tip, pret};
	this->repo.add(new_of);
	this->id++;  // incrementare id.
}

void ServiceOferta::stergere(int id_sters){
	if (not this->repo.search(id_sters)) {
		throw std::out_of_range{"Elementul nu este in registru"};
	}
	this->repo.remove(id_sters);
}

void ServiceOferta::modificare(int id_modificat, string denumire, string destinatie, string tip, int pret){
	if (not this->repo.search(id_modificat)) {
		throw std::out_of_range{"Elementul nu este in registru"};
	}
	Oferta noua_oferta{id_modificat, denumire, destinatie, tip, pret};
	this->repo.update(id_modificat, noua_oferta);
}

const Oferta& ServiceOferta::cautare(int id_cautat) const{
	return this->repo.search_element(id_cautat);
}

const vector<Oferta> ServiceOferta::filtrare_pret(int lower, int upper) const{
	vector<Oferta> new_vec; 
	for (const auto& el : this->get_all()) {
		if (el.get_pret() >= lower and el.get_pret() <= upper)
			new_vec.push_back(el);  // Adaugam in noul vector.
	}

	return new_vec;  // Returnam copie.
}

const vector<Oferta> ServiceOferta::filtrare_destinatie(string filtru_destinatie) const{
	vector<Oferta> new_vec;
	for (const auto& el : this->get_all()) {
		if (el.get_destinatie() == filtru_destinatie)
			new_vec.push_back(el);
	}

	return new_vec;
}

const vector<Oferta> ServiceOferta::sortare(std::function<bool(Oferta& a, Oferta& b)> criteriu) const{
	vector<Oferta> new_vec;
	new_vec = this->get_all();
	std::sort(new_vec.begin(), new_vec.end(), criteriu);
	return new_vec;
}

const vector<Oferta> ServiceOferta::get_all() const{
	return this->repo.get_all();
}
