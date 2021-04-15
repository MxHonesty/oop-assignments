#include "ServiceOferta.h"
#include "../errors/ServiceError.h"
#include <algorithm>
#include <iostream>
#include <random>
#include <chrono>

void ServiceOferta::adaugare(const string& denumire, const string& destinatie, const string& tip, int pret){
	Oferta noua_oferta{ this->id, denumire, destinatie, tip, pret };
	if (valid.validare(noua_oferta)) {
		this->repo->add(noua_oferta);
		this->id++;  // incrementare id.
		undo_actions.push_back(std::make_unique<UndoAdauga>(repo.get(), noua_oferta, cos));
	}
}

void ServiceOferta::stergere(const int id_sters){
	if (not this->repo->search(id_sters)) {
		throw ServiceError{"Elementul nu este in registru"};
	}
	const Oferta de_sters = this->repo->search_element(id_sters);
	const auto a_sters_cos = this->cos.sterge(de_sters);  // Stergem din cos. 
	this->repo->remove(id_sters);

	if (a_sters_cos) {
		undo_actions.push_back(std::make_unique<UndoStergeCuCos>(repo.get(), de_sters, cos));
	}
	else {
		undo_actions.push_back(std::make_unique<UndoSterge>(repo.get(), de_sters));
	}
}

void ServiceOferta::modificare(const int id_modificat, const string& denumire, const string& destinatie, const string& tip, const int pret){
	if (not this->repo->search(id_modificat)) {
		throw ServiceError{"Elementul nu este in registru"};
	}
	Oferta noua_oferta{id_modificat, denumire, destinatie, tip, pret};
	if (valid.validare(noua_oferta)) {
		const Oferta de_modifcat = this->repo->search_element(id_modificat);
		const auto a_modificat_cos = this->cos.modifica(de_modifcat, noua_oferta);
		this->repo->update(id_modificat, noua_oferta);

		if (a_modificat_cos) {
			undo_actions.push_back(std::make_unique<UndoModificaCuCos>(repo.get(),
				de_modifcat, noua_oferta, cos));
		}
		else {
			undo_actions.push_back(std::make_unique<UndoModifica>(repo.get(),
				de_modifcat, noua_oferta));
		}
	}
}

const Oferta& ServiceOferta::cautare(int id_cautat) const{
	return this->repo->search_element(id_cautat);
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

const vector<Oferta>& ServiceOferta::get_all() const {
	return this->repo->afisare();
}

const vector<Oferta>& ServiceOferta::get_ref_all() const {
	return this->repo->afisare();
}

void ServiceOferta::adauga_cos(const string& denumire) {
	const auto& gasit = repo->search_get_denumire(denumire);
	cos.adauga(gasit);
}

void ServiceOferta::sterge_din_cos(const string& denumire) {
	const auto& gasit = repo->search_get_denumire(denumire);
	cos.sterge(gasit);
}

void ServiceOferta::golire_cos() noexcept {
	cos.golire();
}

unsigned ServiceOferta::dimensiune_cos() const noexcept {
	return cos.dim();
}

const vector<Oferta>& ServiceOferta::vector_cos() const noexcept {
	return cos.lista_cos();
}

void ServiceOferta::export_html_cos(const string& file_name) const {
	cos.export_html(file_name);
}

void ServiceOferta::export_html_cos_fancy(const string& file_name) const {
	cos.export_html_fancy(file_name);
}

void ServiceOferta::adauga_random_cos(int numar) {
	vector<Oferta> vec = get_all();  // Copiem toate elementele in vector.
	const auto seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());  // generam seed 
	std::shuffle(vec.begin(), vec.end(), std::default_random_engine(seed)); //amesteca vectorul v
	for (const auto& el : vec) {
		if (numar > 0) {
			this->adauga_cos(el.get_denumire());
			numar--;
		}
	}
}

std::unordered_map<string, TipDTO> ServiceOferta::mapare_tip() {
	std::unordered_map<string, TipDTO> rez;
	// Folosim find, daca rezultatul == end nu exista.

	for (const auto& el : get_ref_all()) {
		const auto gasit = rez.find(el.get_tip());
		if (gasit == rez.end()) {  // Nu exista deja
			rez.insert({ el.get_tip(), TipDTO{el.get_tip()} });  // Inseram perechea
		}
		else {  // Exista pe pozitia aratata de gasit.
			(*gasit).second.increment_count();  // Incrementam aparitia.
		}
	}

	return rez;
}

void ServiceOferta::undo() {
	if (not undo_actions.empty()) {
		this->undo_actions.back()->doUndo();
		this->undo_actions.pop_back();
	}
}
