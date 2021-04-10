#include "Cos_tests.h"
#include "../Cos.h"
#include <cassert>

/** Functie de testare pentru functionalitatea de adaugare din cos. */
void test_cos_adaugare() {
	Cos cos;
	cos.adauga({1, "A", "A", "A", 100});
	cos.adauga({2, "A", "A", "A", 100});
	cos.adauga({3, "A", "A", "A", 100});
	cos.adauga({4, "A", "A", "A", 100});

	const auto& vec = cos.lista_cos();
	int i = 1;
	for (const auto& el : vec) {
		Oferta de_proba{ i, "A", "A", "A", 100 };
		assert(el == de_proba);
		i++;
	}
}

/** Functie de testare pentru functionalitatea de stergere din cos. */
void test_cos_stergere() {
	Cos cos;
	cos.adauga({ 1, "A", "A", "A", 100 });
	cos.adauga({ 2, "A", "A", "A", 100 });
	cos.adauga({ 3, "A", "A", "A", 100 });
	cos.adauga({ 4, "A", "A", "A", 100 });
	cos.adauga({ 5, "A", "A", "A", 100 });

	cos.sterge({ 2, "A", "A", "A", 100 });  // Stergem elementele pare.
	cos.sterge({ 4, "A", "A", "A", 100 });

	const auto& vec = cos.lista_cos();
	int i = 1;
	for (const auto& el : vec) {
		Oferta de_proba{ i, "A", "A", "A", 100 };
		assert(el == de_proba);
		i += 2;
	}

	cos.golire();
	assert(cos.dim() == 0);
}

void test_cos_modificare() {
	Cos cos;
	cos.adauga({ 1, "A", "A", "A", 100 });
	cos.adauga({ 2, "A", "A", "A", 100 });
	cos.adauga({ 3, "A", "A", "A", 100 });
	cos.adauga({ 4, "A", "A", "A", 100 });
	cos.adauga({ 5, "A", "A", "A", 100 });

	cos.modifica({ 1, "A", "A", "A", 100 }, { 100, "A", "A", "A", 1 });

	assert(cos.dim() == 5);
	const auto& vec = cos.lista_cos();
	Oferta a{ 1, "A", "A", "A", 100 };
	auto gasit = std::find(vec.begin(), vec.end(), a);  // Cautam element inexistent
	assert(gasit == vec.end());

	Oferta b{ 100, "A", "A", "A", 1 };
	auto gasit2 = std::find(vec.begin(), vec.end(), b);  // Cautam elementul nou.
	assert(*gasit2 == b);
}

void Testing::run_all_cos_tests() {
	test_cos_adaugare();
	test_cos_stergere();
	test_cos_modificare();
}
