#pragma once

#include <string>
#include <ostream>
using std::string;


class Produs {
private:
	string denumire;
	string tip;
	int ca;  // Cantitate actuala.
	int cn;  // Cantitate necesara pe zi
	int id;

public:

	// Constructor implicit.
	Produs();

	/** Data constructor */
	Produs(int id, string denumire, string tip, int cantitate_actuala, int cantitate_necesara) : id{id}, denumire { denumire }, tip{ tip },
		ca{ cantitate_actuala }, cn{ cantitate_necesara } {};

	int get_id() const;

	/** Returneaza denumirea */
	string get_denumire() const;

	/** Returneaza tipul */
	string get_tip() const;

	/** Returneaza cantitatea actuala. */
	int get_ca() const;

	/** Returneaza cantitatea necesara */
	int get_cn() const;

	/** Citeste din fisier linii de forma 
	id,denumire,tip,ca,cn

	*/
	friend std::istream& operator>>(std::istream& in, Produs& prod);
};
