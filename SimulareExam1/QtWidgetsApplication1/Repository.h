#pragma once
#include "Produs.h"
#include <istream>
#include <vector>
#include <string>
using std::vector;
using std::string;


class Repository {
private:
	vector<Produs> elems;

	void load_from_file(std::istream& in);

public:
	
	// Constructor din stream (pentru testing)
	Repository(std::istream& in);

	// Constructor din filname.
	Repository(const string& filename);

	// Get a referance to the Produs with the given id.
	// Arunca exceptie daca nu este gasit.
	const Produs& get_produs(const int id) const;

	// Returns referance to the vector. 
	const vector<Produs>& get_all() const;
};
