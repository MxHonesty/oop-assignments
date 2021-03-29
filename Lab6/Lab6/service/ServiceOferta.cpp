#include "ServiceOferta.h"
#include <stdexcept>
#include <algorithm>

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

const vector<Oferta> ServiceOferta::filtrare_pret(const int lower, const int upper) const {
	vector<Oferta> new_vec; 
	for (const auto& el : this->get_ref_all()) {
		if (el.get_pret() >= lower and el.get_pret() <= upper)
			new_vec.push_back(el);  // Adaugam in noul vector.  // O Copie la adaugare
	}

	return new_vec;  // Returnam copie.  // O noua copie la returnare
}

const vector<Oferta> ServiceOferta::filtrare_destinatie(const string& filtru_destinatie) const {
	vector<Oferta> new_vec;
	for (const auto& el : this->get_ref_all()) {
		if (el.get_destinatie() == filtru_destinatie)
			new_vec.push_back(el);
	}

	return new_vec;
}

const vector<Oferta> ServiceOferta::sortare(std::function<bool(const Oferta& a, const Oferta& b)> criteriu) const{
	auto new_vec = this->get_all();
	std::sort(new_vec.begin(), new_vec.end(), criteriu);
	return new_vec;  // Copiaza fiecare element de doua ori.
}

const vector<Oferta> ServiceOferta::get_all() const {
	return this->repo.get_all();
}

const vector<Oferta>& ServiceOferta::get_ref_all() const {
	return this->repo.afisare();
}
