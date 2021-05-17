#pragma once

#include <vector>
#include <string>
#include "Produs.h"
using std::vector;
using std::string;


class Repository {
private:
	vector<Produs> elems;
	string filename;

	void initializare_din_fisier(string name);

public:

	Repository(string file = "data.txt") : filename{ file } {
		initializare_din_fisier(filename);
	}

	/** Adauga un produs in lista. */
	void adauga(const Produs& prod);

	/** Returneaza diferenta dintre cost necesar si cost actual sau 0.
		Arunca exceptie daca nu exista element cu id dat.
	*/
	int stoc_necesar(const int id) const;
	
	/** Returneaza referinta constanta la vectorul de elemente. */
	vector<Produs> get_all() const;
};

