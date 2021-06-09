#pragma once
#include "Task.h"
#include <string>
#include <vector>

class Repository {
private:
	std::string filename;
	std::vector<Task> elems;

	void incarca_fisier();

	void scrie_fisier();

public:

	// Constructor Repo cu filename dat
	Repository(const std::string& filename) : filename{ filename } {
		incarca_fisier();
	};

	// Returneaza referinta constanta la vectorul de elemente.
	const std::vector<Task>& get_all() const;

	// Adauga un task in Repo
	void add(const Task& tsk);

	// Schimba starea unui element cu id dat.
	// Arunca eroare daca nu a gasit id.
	void change_stare(const int id, const string& new_stare);

};

