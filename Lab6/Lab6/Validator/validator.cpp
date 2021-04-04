#include "validator.h"

bool Validator::validare(const Oferta& of) {
	if (of.get_pret() < 0) 
		throw std::domain_error{ "Pret invalid" };
	if (of.get_denumire() == "" or of.get_destinatie() == "" or of.get_tip() == "")
		throw std::domain_error{ "Oferta invalida" };

	return true;
}
