#include "validator.h"
#include "../errors/ValidatorError.h"


bool Validator::validare(const Oferta& of) const {
	if (of.get_pret() < 0) 
		throw ValidatorError{ "Pret invalid" };
	if (of.get_denumire() == "" || of.get_destinatie() == "" || of.get_tip() == "")
		throw ValidatorError{ "Oferta invalida" };

	if (oRepo.has_value()) {  // Daca este un repo atasat
		if (oRepo.value()->search_denumire(of.get_denumire())) {  // Daca exista cu denumire identica.
			const Oferta& gasita = oRepo.value()->search_get_denumire(of.get_denumire());
			if(! (gasita == of))
				throw ValidatorError{ "Un element cu aceasta denumire deja exista" };
		}
	}

	return true;
}
