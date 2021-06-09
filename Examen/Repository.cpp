#include "Repository.h"
#include <fstream>
#include <exception>

void Repository::incarca_fisier() {
	std::ifstream file{ filename };
	Task tsk;
	while (!file.eof()) {
		try {
			file >> tsk;
			elems.push_back(tsk);
		}
		catch (...) {

		}
	}
}

void Repository::scrie_fisier() {
	std::ofstream file{ filename };
	for (auto& el : elems)
		file << el;
}

const std::vector<Task>& Repository::get_all() const {
	return elems;
}

void Repository::add(const Task& tsk) {
	elems.push_back(tsk);
	scrie_fisier();
}

void Repository::change_stare(const int id, const string& new_stare) {
	for (auto& el : elems) {
		if (el.get_id() == id) {
			el.set_stare(new_stare);
			scrie_fisier();
			return;
		}
	}

	throw std::exception{"Starea nu s-a putut schimba"};
}
