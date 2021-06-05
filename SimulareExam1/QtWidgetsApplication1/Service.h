#pragma once
#include "Repository.h"

class Service {
private:
	Repository repo;

public:

	// Constructor
	Service();
	
	vector<Produs> sort_tip() const;

	vector<Produs> sort_ca() const;

	// Get all the elements.
	vector<Produs> get_all() const;

	// Cauta produsul dorit. Returneaza o refeinta.
	// Arunca eroare daca nu exista element cu id dat.
	const Produs& find(const int id);

	// Returneaza true daca elementul are ca < cn
	// DAca returneaza true elementul trebuie colorat in rosu.
	bool este_nevoie(const int id);
};
