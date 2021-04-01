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
	a.add(10);
	a.add(10);
	assert(a.dim() == 5);
}

void test_Vector_get() {

}

void Testing::run_all_VectorDinamic_tests(){
	test_Vector_add();
	test_Vector_remove();
	test_Vector_get();
}
