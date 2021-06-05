#include "Test.h"
#include "Produs.h"
#include <cassert>
#include <sstream>
#include "Repository.h"

void Test::test_produs(){
	Produs prod1{ 0, "A", "A", 0, 0 };
	Produs prod2{ 0, "A", "A", 0, 0 };
	std::istringstream input{"10|DEN|TIP|10|11|\n11|DEN|TIP|11|11|"};

	input >> prod1 >> prod2;

	assert(prod1.get_id() == 10);
	assert(prod2.get_id() == 11);

	assert(prod1.get_denumire() == "DEN");
	assert(prod2.get_denumire() == "DEN");


	assert(prod1.get_ca() == 10);
	assert(prod2.get_ca() == 11);
}

void Test::test_repository() {
	std::istringstream in{"10|DEN|TIP|10|11|\n11|DEN|TIP|11|11|\n"};
	Repository repo{ in };

	const auto& el = repo.get_produs(10);
	assert(el.get_id() == 10);

	const auto& el2 = repo.get_produs(11);
	assert(el2.get_id() == 11);
}

void Test::run_all_tests() {
	test_produs();
	test_repository();
}
