#include "validator_test.h"
#include "Validator/validator.h"
#include <cassert>

void Testing::run_validator_tests() {
	Validator v;
	Oferta b(1, "a", "a", "a", 10);
	assert(v.validare(b));
	Oferta c{ 1, "", "", "", 10 };
	Oferta d{ 1, "A", "A", "A", -10 };
	try {
		v.validare(c);
	}
	catch (const std::exception& e) {
		assert(std::string{ e.what() } == "Oferta invalida");
	}
	try {
		v.validare(d);
	}
	catch (const std::exception& e) {
		assert(std::string{ e.what() } == "Pret invalid");
	}
}
