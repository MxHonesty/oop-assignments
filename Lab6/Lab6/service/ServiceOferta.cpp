#include "ServiceOferta.h"
#include "../errors/ServiceError.h"
#include <algorithm>
#include <iostream>

void ServiceOferta::adaugare(const string& denumire, const string& destinatie, const string& tip, int pret){
	Oferta noua_oferta{ this->id, denumire, destinatie, tip, pret };
	if (valid.validare(noua_oferta)) {
		this->repo.add(noua_oferta);
		this->id++;  // incrementare id.
	}
}

void ServiceOferta::stergere(const int id_sters){
	if (not this->repo.search(id_sters)) {
		throw ServiceError{"Elementul nu este in registru"};
	}
	this->repo.remove(id_sters);
}

void ServiceOferta::modificare(const int id_modificat, const string& denumire, const string& destinatie, const string& tip, const int pret){
	if (not this->repo.search(id_modificat)) {
		throw ServiceError{"Elementul nu este in registru"};
	}
	Oferta noua_oferta{id_modificat, denumire, destinatie, tip, pret};
	if(valid.validare(noua_oferta))
		this->repo.update(id_modificat, noua_oferta);
}

const Oferta& ServiceOferta::cautare(int id_cautat) const{
	return this->repo.search_element(id_cautat);
}

const vector<Oferta> ServiceOferta::filtrare_pret(const int lower, const int upper) const {
	vector<Oferta> new_vec;
	const vector<Oferta>& current = this->get_ref_all() ;
	std::copy_if(current.begin(), current.end(), std::back_inserter(new_vec), 
		[lower, upper](const Oferta& el) noexcept 
	{return el.get_pret() >= lower and el.get_pret() <= upper; });
	return new_vec;  // Returnam copie.  // O noua copie la returnare
}

const vector<Oferta> ServiceOferta::filtrare_destinatie(const string& filtru_destinatie) const {
	vector<Oferta> new_vec;
	const vector<Oferta>& current = this->get_ref_all();

	std::copy_if(current.begin(), current.end(), std::back_inserter(new_vec),
		[filtru_destinatie](const Oferta& el) 
	{return el.get_destinatie() == filtru_destinatie; });


	return new_vec;
}

const vector<Oferta> ServiceOferta::sortare(std::function<bool(const Oferta& a, const Oferta& b)> criteriu) const{
	auto new_vec = this->get_all();
	std::sort(new_vec.begin(), new_vec.end(), criteriu);
	return new_vec;  // Copiaza fiecare element de doua ori.
}

const vector<Oferta>& ServiceOferta::get_all() const noexcept {
	return this->repo.afisare();
}

const vector<Oferta>& ServiceOferta::get_ref_all() const noexcept {
	return this->repo.afisare();
}
