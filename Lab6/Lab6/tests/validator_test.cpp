#include "validator_test.h"
#include "../Velidator/validator.h"
#include <cassert>

void Testing::run_validator_tests() {
	Validator v;
	Oferta b(1, "a", "a", "a", 10);
	assert(v.validare(b));
	Oferta c{ 1, "", "", "", 10 };
	Oferta d{ 1, "A", "A", "A", -10 };
	assert(not v.validare(c));
	assert(not v.validare(d));
}
