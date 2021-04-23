#include "VectorDinamic_tests.h"
#include "../VectorDinamic/VectorDinamic.h"
#include <cassert>

void test_Vector_add() {
	VectorDinamic<int> a;
	a.add(10);
	a.add(10);
	a.add(10);
	a.add(10);
	a.add(10);
	assert(a.dim() == 5);

	a.add(10);
	a.add(10);
	a.add(10);
	a.add(10);
	a.add(10);
	a.add(10);
	assert(a.dim() == 11);
}

void test_Vector_remove() {
	VectorDinamic<int> a;
	a.add(10);
	a.add(10);
	a.add(10);
	a.add(1);
	a.add(10);
	assert(a.dim() == 5);
	
	a.remove(0);
	a.remove(0);
	a.remove(0);
	assert(a.dim() == 2);

	assert(a.get(0) == 1);
	assert(a.get(1) == 10);
}

void test_Vector_Copiere() {
	VectorDinamic<int> a;
	a.add(10);
	a.add(10);
	a.add(10);

	VectorDinamic<int> b{ a };
	b.remove(0);
	b.remove(0);

	assert(b.dim() == 1);
	assert(a.dim() == 3);

	VectorDinamic<int> c;
	c = a;
	c.add(100);
	c.add(100);
	assert(c.dim() == 5 and a.dim() == 3);
}

void test_Iterator_Vector() {
	VectorDinamic<int> a;
	a.add(10);
	a.add(10);
	a.add(10);
	a.add(10);
	for (const auto& v : a) {
		assert(v == 10);
	}

	VectorDinamic<int> b;
	b.add(0);
	b.add(1);
	b.add(2);
	b.add(3);
	b.add(4);
	int i = 0;
	for (const auto& v : b) {
		assert(v == i);
		i++;
	}
}

void test_stl_algo() {
	VectorDinamic<int> a;
	a.add(10);
	a.add(8);
	a.add(9);
	a.add(6);
	a.add(1);
	
	const int sortat_corect[5]{ 1, 6, 8, 9, 10 };
	int i = 0;
	a.sort([](const int& on, const int& ot) noexcept {return on < ot; });
	for (const auto& el : a)
		assert(sortat_corect[i++] == el);
}

void test_exceptions() {
	VectorDinamic<int> a;
	assert(not a.begin().valid());

	try {
		a.begin().element();
		assert(false);
	}
	catch (const std::exception& e) {
		if (std::string{ e.what() } == "Index out of range")
			assert(true);
		else
			assert(false); // Wrong error.
	}
	
}

void test_clear() {
	VectorDinamic<int> a;
	a.add(10);
	a.add(10);
	a.add(10);
	a.add(10);
	a.add(10);
	a.add(10);
	assert(a.dim() == 6);
	a.clear();
	assert(a.dim() == 0);
}

void Testing::run_all_VectorDinamic_tests() {
	test_Vector_add();
	test_Vector_remove();
	test_Vector_Copiere();

	test_Iterator_Vector();

	test_stl_algo();

	test_exceptions();
	test_clear();
}
