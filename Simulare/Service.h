#pragma once
#include "Repository.h"
#include <vector>
#include "Produs.h"


class Service {
private:
	Repository repo;

public:
	/** Constructor implicit */
	Service() : repo{} {};

	std::vector<Produs> get_all();

	std::vector<Produs> sortare_stoc_desc();

	std::vector<Produs> sortare_tip_crescator();

	int stoc_necesar(const int id);

	/** Returneaza true daca itemul trebuie colorat in rosu. */
	bool nu_este_suficient(const int id);
};
