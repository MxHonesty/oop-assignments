#include "ServiceOferta.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>

void ServiceOferta::adaugare(const string& denumire, const string& destinatie, const string& tip, int pret){
	this->repo.add({ this->id, denumire, destinatie, tip, pret });
	this->id++;  // incrementare id.
}

void ServiceOferta::stergere(const int id_sters){
	if (not this->repo.search(id_sters)) {
		throw std::out_of_range{"Elementul nu este in registru"};
	}
	this->repo.remove(id_sters);
}

void ServiceOferta::modificare(const int id_modificat, const string& denumire, const string& destinatie, const string& tip, const int pret){
	if (not this->repo.search(id_modificat)) {
		throw std::out_of_range{"Elementul nu este in registru"};
	}
	Oferta noua_oferta{id_modificat, denumire, destinatie, tip, pret};
	this->repo.update(id_modificat, noua_oferta);
}

const Oferta& ServiceOferta::cautare(int id_cautat) const{
	return this->repo.search_element(id_cautat);
}

const VectorDinamic<Oferta> ServiceOferta::filtrare_pret(const int lower, const int upper) const {
	VectorDinamic<Oferta> new_vec;
	for (const auto& el : this->get_ref_all()) {
		if (el.get_pret() >= lower and el.get_pret() <= upper)
			new_vec.add(el);  // Adaugam in noul vector.  // O Copie la adaugare
	}

	return new_vec;  // Returnam copie.  // O noua copie la returnare
}

const VectorDinamic<Oferta> ServiceOferta::filtrare_destinatie(const string& filtru_destinatie) const {
	VectorDinamic<Oferta> new_vec;
	for (const auto& el : this->get_ref_all()) {
		if (el.get_destinatie() == filtru_destinatie)
			new_vec.add(el);
	}

	return new_vec;
}

const VectorDinamic<Oferta> ServiceOferta::sortare(std::function<bool(const Oferta& a, const Oferta& b)> criteriu) const{
	auto new_vec = this->get_all();
	new_vec.sort(criteriu);
	return new_vec;  // Copiaza fiecare element de doua ori.
}

const VectorDinamic<Oferta>& ServiceOferta::get_all() const {
	return this->repo.afisare();
}

const VectorDinamic<Oferta>& ServiceOferta::get_ref_all() const {
	return this->repo.afisare();
}
