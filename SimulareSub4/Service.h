#pragma once

#include "Repository.h"
#include "Observer.h"

class Service : public Observable {
private:
	Repository repo;

public:

	Service() : repo{ "data.txt" } {};

	// Returneaza toate elementele.
	const vector<Task> get_all(); 

	// Adauga un task in Registru.
	// Verifica daca numarul de programatori e bun.
	// Verifica daca id-ul este unic.
	// Arunca exceptii daca validarile nu trec.
	void add_task(const int id, const string& descriere, const string& tip, const vector<string>& prog);

	const vector<Task> get_programator(string programator);
};
