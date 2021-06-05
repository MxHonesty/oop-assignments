#include "Produs.h"
#include <sstream>

Produs::Produs(const int id, const string& denumire, const string& tip, const int ca, const int cn)
	: id{id}, denumire {denumire}, tip{ tip }, ca{ ca }, cn{ cn } {}

string Produs::get_denumire() const {
	return denumire;
}

string Produs::get_tip() const {
	return tip;
}

int Produs::get_ca() const {
	return ca;
}

int Produs::get_cn() const {
	return cn;
}

int Produs::get_id() const {
	return id;
}

std::istream& operator>>(std::istream& in, Produs& prod) {
	// Citim din fisier, separatorul este | 
	// Un obiect este scris pe un rand.
	string line;
	std::getline(in, line);

	std::istringstream token{ line };
	string str_id, str_ca, str_cn, str_denumire, str_tip;
	
	std::getline(token, str_id, '|');
	std::getline(token, str_denumire, '|');
	std::getline(token, str_tip, '|');
	std::getline(token, str_ca, '|');
	std::getline(token, str_cn, '|');

	int id = -1, ca = -1, cn = -1;
	try {
		id = stoi(str_id);
		ca = stoi(str_ca);
		cn = stoi(str_cn);

	}
	catch (...) {
		throw std::exception{ "stream conversion error" };
	}

	prod.id = id;
	prod.ca = ca;
	prod.cn = cn;
	prod.denumire = str_denumire;
	prod.tip = str_tip;

	return in;
}
