#pragma once
#include <string>
#include <ostream>
using std::string;

class Produs {
private:
	int ca, cn, id;
	string denumire, tip;


public:
	/** Constructor pentru un produs. */
	Produs(const int id, const string& denumire, const string& tip, const int ca, const int cn);

	/** Returneaza denumirea produsului. */
	string get_denumire() const;

	/** Returneaza tipul produsului. */
	string get_tip() const;

	/** Returneaza cantitatea actuala produsului produsului. */
	int get_ca() const;

	/** Returneaza cantitatea necesara a produsului. */
	int get_cn() const;

	/** Returneaza id-ul produsului. */
	int get_id() const;

	// Ordine fisier id|denumire|tip|ca|cn
	friend std::istream& operator>>(std::istream& in, Produs& prod);
};
