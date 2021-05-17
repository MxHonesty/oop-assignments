#include "Cos_tests.h"
#include "../cos/Cos.h"
#include "../observer/observer.h"
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

/** Testeaza daca valorile de adevar returnate in urma
	Operatiilor de adaugare, stergere, modificare sunt adevarate.
*/
void test_cos_returns() {
	Cos cos;

	assert(cos.adauga({ 1, "A", "A", "A", 100 }) == true);
	assert(cos.adauga({ 1, "A", "A", "A", 100 }) == false);
	assert(cos.adauga({ 1, "A", "A", "A", 100 }) == false);
	assert(cos.adauga({ 2, "B", "A", "A", 100 }) == true);
	assert(cos.adauga({ 3, "C", "A", "A", 100 }) == true);

	assert(cos.sterge({ 1, "A", "A", "A", 100 }) == true);
	assert(cos.sterge({ 1, "A", "A", "A", 100 }) == false);

	assert(cos.modifica({ 2, "B", "A", "A", 100 }, {1, "A", "A", "A", 100}) == true);
	assert(cos.modifica({ 2, "B", "A", "A", 100 }, {1, "A", "A", "A", 100}) == false);
}

void test_cos_observer() {
	class TestObserver : public Observer {
	private:
		Cos& cos;

	public:
		std::vector<Oferta> elems;
		TestObserver(Cos& cos) : cos{ cos }, elems{} {
			cos.addObserver(this);
		};

		virtual ~TestObserver() {};

		void update() override {
			elems = cos.lista_cos();
		}
	};

	Cos cos;
	TestObserver obs1{ cos }, obs2{ cos }, obs3{ cos };
	Oferta a{ 1, "a", "a", "a", 100 };
	Oferta b{ 2, "a", "a", "a", 100 };
	Oferta c{ 3, "a", "a", "a", 100 };
	cos.adauga(a);

	assert(obs1.elems.size() == 1);
	assert(obs2.elems.size() == 1);
	assert(obs3.elems.size() == 1);

	cos.adauga(b);
	assert(obs1.elems.size() == 2);
	assert(obs2.elems.size() == 2);
	assert(obs3.elems.size() == 2);

	cos.removeObserver(&obs3);
	cos.removeObserver(&obs2);
	
	cos.adauga(c);
	assert(obs1.elems.size() == 3);
	assert(obs2.elems.size() == 2);
	assert(obs3.elems.size() == 2);

}

void Testing::run_all_cos_tests() {
	test_cos_adaugare();
	test_cos_stergere();
	test_cos_modificare();
	test_cos_returns();
	test_cos_observer();
}
