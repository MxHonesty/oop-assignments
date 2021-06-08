#pragma once

#include "Task.h"
#include <string>

class Repository {
private:
	std::string filename;
	std::vector<Task> elems;

	void incarca_fisier();

	void scrie_fisier();
public:

	// Constructor cu filename dat.
	Repository(const std::string& filename) : filename{ filename } {
		incarca_fisier();
	};

	// Returneaza referinta constanta la vectorul de elemnte.
	const std::vector<Task>& get_all() const;

	// Adauga un Task in repo.
	void add(const Task& tsk);

	// Schimba starea elementului.
	// Daca nu gaseste niciun element cu acest id, atunci nu se modifica nimic.
	void change_stare(const int id, const string& new_stare);
		
};
