#pragma once

#include "../domain/oferta.h"
#include "../repo/RepoOferta.h"
#include <optional>

class Validator {
private:
	std::optional<const Repository*> oRepo;

public:

	/** Constructor */
	Validator(const Repository* r) noexcept : oRepo(r) {};

	/** Default constructor 
	* Validator cu repo gol.
	*/
	Validator() noexcept : oRepo{} {};

	/** Clasa care determina daca oferta data este valida 
	* @param of - oferta pe care dorim sa o validam.
	* @return true daca e valid, arunca exceptie daca nu e valid
	*/
	bool validare(const Oferta& of) const;
};
