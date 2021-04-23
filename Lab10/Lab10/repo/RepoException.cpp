#include "RepoException.h"
#include <random>
#include <iostream>

void RepoException::trigger() const {
	const int randNum = rand() % (101);
	const int probabili = static_cast<int>(prob * 100);
	std::cout << randNum << "/" << probabili << "\n";
	if (randNum <= probabili) {
		std::cout << "\nAruncat\n";
		throw RepoError{ "Eroare de ghinion!" };
	}
}

void RepoException::add(const Oferta& de_adaugat) {
	trigger();
	dict.insert(std::pair<int, Oferta>(de_adaugat.get_id(), de_adaugat));
}

void RepoException::remove(const int id) {
	trigger();
	dict.erase(id);
}

void RepoException::update(const int id, const Oferta& new_oferta) {
	trigger();
	auto& gasit = dict.at(id);
	gasit.set_denumire(new_oferta.get_denumire());
	gasit.set_destinatie(new_oferta.get_destinatie());
	gasit.set_tip(new_oferta.get_tip());
	gasit.set_pret(new_oferta.get_pret());
}

bool RepoException::search(const int id) const {
	trigger();
	const auto gasit = std::find_if(dict.begin(), dict.end(), [id](const std::pair<int, Oferta>& a) {
		return a.second.get_id() == id; });

	if (gasit == dict.end())
		return false;
	return true;
}

bool RepoException::search_denumire(const std::string& denumire) const {
	trigger();
	const auto gasit = std::find_if(dict.begin(), dict.end(), [&denumire](const std::pair<int, Oferta>& a) {
		return a.second.get_denumire() == denumire; });

	if (gasit == dict.end())
		return false;
	return true;
}

const Oferta& RepoException::search_get_denumire(const std::string& denumire) const {
	trigger();
	const auto gasit = std::find_if(dict.begin(), dict.end(), [&denumire](const std::pair<int, Oferta>& a) {
		return a.second.get_denumire() == denumire; });

	if (gasit == dict.end())
		throw RepoError{"Nu exista"};
	return (*gasit).second;
}

const Oferta& RepoException::search_element(const int id) const {
	trigger();
	const auto gasit = std::find_if(dict.begin(), dict.end(), [id](const std::pair<int, Oferta>& a) {
		return a.second.get_id() == id; });

	if (gasit == dict.end())
		throw RepoError{ "Nu exista" };
	return (*gasit).second;
}

vector<Oferta> RepoException::get_all() const {
	trigger();
	vector<Oferta> elems;
	for (const auto& el : dict) {
		elems.push_back(el.second);
	}

	return elems;
}

const vector<Oferta> RepoException::afisare() const noexcept {
	trigger();
	std::vector<Oferta> new_elems;
	for (const auto& el : dict) {
		new_elems.push_back(el.second);
	}
	return new_elems;
}

void RepoException::remove_all() noexcept {
	trigger();
	dict.clear();
}

size_t RepoException::dim() noexcept {
	trigger();
	return dict.size();
}

int RepoException::get_max_index() const noexcept {
	int max_id = 0;
	for (const auto& el : dict) {
		if (el.first > max_id)
			max_id = el.first;
	}
	return max_id;
}
