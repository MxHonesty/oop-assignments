#include "validator.h"
#include "../errors/ValidatorError.h"


bool Validator::validare(const Oferta& of) const {
	if (of.get_pret() < 0) 
		throw ValidatorError{ "Pret invalid" };
	if (of.get_denumire() == "" or of.get_destinatie() == "" or of.get_tip() == "")
		throw ValidatorError{ "Oferta invalida" };

	if (oRepo.has_value()) {  // Daca este un repo atasat
		if (oRepo.value()->search_denumire(of.get_denumire()))
			throw ValidatorError{ "Un element cu aceasta denumire deja exista" };
	}
	return true;
}
