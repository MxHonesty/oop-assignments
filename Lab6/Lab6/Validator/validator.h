#pragma once

#include "../domain/oferta.h"

class Validator {
public:
	/** Clasa care determina daca oferta data este valida 
	* @param of - oferta pe care dorim sa o validam.
	* @return true daca e valid, arunca exceptie daca nu e valid
	*/
	bool validare(const Oferta& of);
};
