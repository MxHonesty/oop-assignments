#include "validator_test.h"
#include "../Validator/validator.h"
#include <cassert>

/** Testare validare. */
void Testing::run_validator_tests() {
	const Validator v;
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

	RepoOferte repo;
	repo.add({1, "A", "A", "A", 1});
	repo.add({2, "B", "A", "A", 1});
	repo.add({3, "C", "A", "A", 1});
	const Validator valid{ &repo };
	const Oferta salut{ 10, "A", "A", "A", 1 };
	try {
		valid.validare(salut);
	}
	catch (const std::exception& e) {
		assert(std::string{e.what()} == "Un element cu aceasta denumire deja exista");
	}
}

