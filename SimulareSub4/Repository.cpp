#include "Repository.h"
#include <fstream>
#include <QDebug>

void Repository::incarca_fisier() {
	std::ifstream file{ filename };
	Task tsk{ 0, "A", "A", std::vector<string>{} };
	while (!file.eof()) {
		try {
			file >> tsk;
			elems.push_back(tsk);
		}
		catch (...) {

		}
	}

	file.close();
}

void Repository::scrie_fisier() {
	std::ofstream file{ filename };

	for (auto& el : elems)
		file << el;

	file.close();
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
			return;
		}
	}

	return;
}
