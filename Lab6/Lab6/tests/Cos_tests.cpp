#include "Cos_tests.h"
#include "../Cos.h"
#include <cassert>

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

void Testing::run_all_cos_tests() {
	test_cos_adaugare();
	test_cos_stergere();
}
