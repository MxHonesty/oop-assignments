#include "oferta_tests.h"
#include "../domain/oferta.h"
#include "../DTO/TipDTO.h"
#include <cassert>
#include <sstream>
#include <vector>

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
	assert(! (a == diferit_de_a));
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

void test_scriere() {
	Oferta a{ 1, "A", "B", "C", 100 };
	std::ostringstream m;

	m << a;
	assert(m.str() == "1|A|B|C|100|\n");

	Oferta b{ 2, "A", "A", "A", 100 };
	m << b;
	assert(m.str() == "1|A|B|C|100|\n2|A|A|A|100|\n");
}

void test_citire() {
	std::istringstream m("1|A|A|A|100|\n2|B|B|B|100|\n");
	Oferta a, b;
	m >> a >> b;
	assert(a.get_denumire() == "A");
	assert(a.get_destinatie() == "A");
	assert(a.get_tip() == "A");
	assert(a.get_id() == 1);
	assert(a.get_pret() == 100);

	assert(b.get_denumire() == "B");
	assert(b.get_destinatie() == "B");
	assert(b.get_tip() == "B");
	assert(b.get_id() == 2);
	assert(b.get_pret() == 100);


	std::istringstream incomplet{ "1|A|salut|" };
	try {
		incomplet >> a;
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	std::istringstream incorect{ "AA|AA|AA|AA|20|" };
	try {
		incorect >> a;
		assert(false);
	}
	catch (...) {
		assert(true);
	}
}

void test_equals() {
	Oferta a{ 1, "A", "A", "A", 1 };
	Oferta b{ 1, "A", "A", "A", 1 };
	Oferta c{ 2, "A", "b", "A", 1 };
	assert(a.equals(b));
	assert(! a.equals(c));
	assert(b.equals(a));
}

void Testing::run_oferta_tests(){
	test_oferta_get_set();
	test_operator_egalitate();
	test_dto();
	test_scriere();
	test_citire();
	test_equals();
}
