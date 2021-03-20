#include "TestList.h"
#include "List.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void test_add() {
	List a = create_list();
	for (int i = 0; i < 100; i++) {
		int* b = malloc(sizeof(int));
		if (b != NULL)
			*b = i;
		add_to_list(&a, b);
	}
	assert(a.lungime == 100);

	struct Nod* curent = a.prim;
	for (int i = 0; i < 100; i++) {
		int* valoare = curent->data;
		assert(*valoare == i);
		curent = curent->urmator;
	}
	
	int* salut = peek_date(&a);
	assert(*salut == 99);

	destroy_list(a);
}

void test_remove() {
	List a = create_list();
	for (int i = 0; i < 100; i++) {
		int* b = malloc(sizeof(int));
		if (b != NULL)
			*b = i;
		add_to_list(&a, b);
	}
	for (int i = 0; i < 90; i++)
		pop_list(&a);

	int* rez = peek_date(&a);
	assert(*rez == 9);

	destroy_list(a);
}

void test_leak() {
	List a = create_list();
	for (int i = 0; i < 10000; i++) {
		int* b = malloc(sizeof(int));
		if (b != NULL)
			*b = i;
		add_to_list(&a, b);
	}
	assert(a.lungime == 10000);
	destroy_list(a);
}

void run_all_list_tests(){
	test_add();
	test_remove();
	test_leak();
}
