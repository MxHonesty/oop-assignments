#include "oferta_tests.h"
#include "../domain/oferta.h"
#include "../TipDTO.h"
#include <cassert>

void test_oferta_get_set() {
	Oferta a{ 1, "denum", "dest", "vacanta", 1000 }; // Test get pe Oferta construita prin valori.
	assert(a.get_denumire() == "denum");
	assert(a.get_destinatie() == "dest");
	assert(a.get_id() == 1);
	assert(a.get_tip() == "vacanta");
	assert(a.get_pret() == 1000);

	a.set_denumire("new_dem");  // Test set.
	assert(a.get_denumire() == "new_dem");
	a.set_destinatie("new_dest");
	assert(a.get_destinatie() == "new_dest");
	a.set_pret(10);
	assert(a.get_pret() == 10);
	a.set_tip("A");
	assert(a.get_tip() == "A");

	Oferta b;  // Pe o oferta construita default.
	b = a;
	assert(b.get_denumire() == "new_dem");
	assert(b.get_destinatie() == "new_dest");
	assert(b.get_pret() == 10);
	assert(b.get_tip() == "A");
}

void test_operator_egalitate() {
	Oferta a{1, "A", "A", "A", 1};
	Oferta egal_cu_a{1, "A", "A", "A", 1};
	Oferta diferit_de_a{2, "A", "A", "A", 1};
	assert(a == egal_cu_a);
	assert(not (a == diferit_de_a));
}

void test_dto() {
	TipDTO sal;

	assert(sal.get_count() == 0);
	assert(sal.get_tip() == "");

	sal.set_tip("hello");
	assert(sal.get_tip() == "hello");
	assert(sal.get_count() == 1);

	TipDTO sal2{ "b" };
	assert(sal2.get_count() == 1);
	assert(sal2.get_tip() == "b");
	sal2.increment_count();
	sal2.increment_count();
	sal2.increment_count();
	assert(sal2.get_count() == 4);
	assert(sal2.get_tip() == "b");

	sal2.clear();
	assert(sal2.get_count() == 0);
	assert(sal2.get_tip() == "");
}

void Testing::run_oferta_tests(){
	test_oferta_get_set();
	test_operator_egalitate();
	test_dto();
}
