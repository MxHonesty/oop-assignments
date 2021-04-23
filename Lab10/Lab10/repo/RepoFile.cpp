#include "RepoFile.h"
#include "errors/RepoError.h"
#include "errors/ValidatorError.h"
#include <fstream>
#include "errors/FileError.h"

void RepoFile::salveaza_fisier() {
	std::ofstream file(filename);
	if (file.fail()) {
		throw RepoError{ "Nu s-a putut deschide fisier." };
	}
	else {
		for (const auto& el : elems)
			file << el;
	}

	file.close();
}

void RepoFile::citeste_fisier() {
	std::ifstream file(filename);
	if (file.fail()) {
		std::ofstream temp(filename);
		temp.close();
	}
	else {
		while (not file.eof()) {
			Oferta citit;
			try {
				file >> citit;
			}
			catch (const FileError&) {
				continue;
			}
			try {
				valid.validare(citit);
				const auto gasit = std::find_if(elems.begin(), elems.end(), [&citit](const Oferta& of) noexcept 
				{return of.get_id() == citit.get_id(); });
				if (gasit != elems.end())
					throw ValidatorError{ "Element cu id deja existent" };
				elems.push_back(citit);
			}
			catch (const ValidatorError&) {
				continue;  // Daca prindem eroare doar trecem mai departe.
			}
		}
	}

	file.close();
}

void RepoFile::add(const Oferta& de_adaugat) {
	this->elems.push_back(de_adaugat);
	salveaza_fisier();
}

void RepoFile::remove(const int id) {
	auto de_sters = std::remove_if(elems.begin(), elems.end(),
		[id](const Oferta& el) noexcept {return el.get_id() == id; });

	if (de_sters != elems.end()) {
		elems.erase(de_sters, elems.end());
		salveaza_fisier();
	}
}

void RepoFile::update(const int id, const Oferta& new_oferta) {
	for (auto& el : elems) {
		if (el.get_id() == id) {
			el.set_denumire(new_oferta.get_denumire());
			el.set_destinatie(new_oferta.get_destinatie());
			el.set_tip(new_oferta.get_tip());
			el.set_pret(new_oferta.get_pret());
			salveaza_fisier();
			break;
		}
	}
}

bool RepoFile::search(const int id) const {
	auto gasit = std::find_if(elems.begin(), elems.end(),
		[id](const Oferta& el) noexcept {return el.get_id() == id; });

	if (gasit == elems.end())
		return false;
	else
		return true;
}

bool RepoFile::search_denumire(const std::string& denumire) const {
	auto gasit = std::find_if(elems.begin(), elems.end(),
		[&denumire](const Oferta& el) {return el.get_denumire() == denumire; });

	if (gasit == elems.end())
		return false;
	return true;
}

const Oferta& RepoFile::search_get_denumire(const std::string& denumire) const {
	auto gasit = std::find_if(elems.begin(), elems.end(),
		[denumire](const Oferta& el) {return el.get_denumire() == denumire; });

	if (gasit == elems.end())
		throw RepoError{ "Element not found" };
	else
		return *gasit;
}

const Oferta& RepoFile::search_element(const int id) const {
	auto gasit = std::find_if(elems.begin(), elems.end(),
		[id](const Oferta& el) noexcept {return el.get_id() == id; });

	if (gasit == elems.end())
		throw RepoError{ "Element not found" };
	else
		return *gasit;
}

vector<Oferta> RepoFile::get_all() const {
	return this->elems;
}

const vector<Oferta> RepoFile::afisare() const noexcept {
	return this->elems;
}

void RepoFile::remove_all() noexcept {
	elems.clear();
}

unsigned RepoFile::dim() noexcept {
	return elems.size();
}

int RepoFile::get_max_index() const noexcept {
	int maxim = 0;
	for (const auto& el : elems)
		if (el.get_id() > maxim)
			maxim = el.get_id();

	return maxim;
}
