#include "TestList.h"
#include "List.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void test_add() {
	List* a = create_list();
	add_to_list(a, creeaza_oferta("teren", 1, "A", 1));
	add_to_list(a, creeaza_oferta("teren", 2, "B", 2));
	add_to_list(a, creeaza_oferta("teren", 3, "C", 3));
	add_to_list(a, creeaza_oferta("teren", 4, "D", 4));
	add_to_list(a, creeaza_oferta("teren", 1, "A", 1));
	add_to_list(a, creeaza_oferta("teren", 2, "B", 2));
	add_to_list(a, creeaza_oferta("teren", 3, "C", 3));
	add_to_list(a, creeaza_oferta("teren", 4, "D", 4));
	add_to_list(a, creeaza_oferta("teren", 1, "A", 1));
	add_to_list(a, creeaza_oferta("teren", 2, "B", 2));
	add_to_list(a, creeaza_oferta("teren", 3, "C", 3));
	add_to_list(a, creeaza_oferta("teren", 4, "D", 4));

	assert(dim(a) == 12);
	destroy_list(a, distruge_oferta);
}

void test_delete() {
	List* a = create_list();
	add_to_list(a, creeaza_oferta("teren", 1, "A", 1));
	add_to_list(a, creeaza_oferta("teren", 2, "B", 2));
	add_to_list(a, creeaza_oferta("teren", 3, "C", 3));
	Oferta* de_sters = creeaza_oferta("teren", 4, "D", 4);
	add_to_list(a, de_sters);
	assert(dim(a) == 4);
	Oferta* comparatie = copy_oferta(de_sters);  // construim copie inainte de stergere
	delete_from_list(a, de_sters, distruge_oferta);
	delete_by_index(a, 0, distruge_oferta);
	assert(dim(a) == 2);
	assert(search_element(a, comparatie, equals_oferta) == -1);
	distruge_oferta(comparatie);
	destroy_list(a, distruge_oferta);


	List* b = create_list();
	for (int i = 0; i < 100; i++) {
		add_to_list(b, creeaza_oferta("teren", 1, "A", 1));
	}
	assert(dim(b) == 100);
	for (int i = 0; i < 50; i++)
		pop_list(b, distruge_oferta);
	assert(dim(b) == 50);

	destroy_list(b, distruge_oferta);
}

void test_cautare() {
	// Testam cu elementul pe diferite pozitii din lista.
	List* a = create_list();
	Oferta* cautat = creeaza_oferta("teren", 1, "A", 1);
	add_to_list(a, creeaza_oferta("teren", 2, "B", 2));
	add_to_list(a, creeaza_oferta("teren", 2, "B", 2));
	add_to_list(a, creeaza_oferta("teren", 2, "B", 2));
	add_to_list(a, cautat);
	assert(is_in_list(a, cautat) != 0);  // Este in lista.
	assert(search_element(a, cautat, equals_oferta) == 3);
	destroy_list(a, distruge_oferta);

	a = create_list();
	cautat = creeaza_oferta("teren", 1, "A", 1);
	add_to_list(a, cautat);
	add_to_list(a, creeaza_oferta("teren", 2, "B", 2));
	add_to_list(a, creeaza_oferta("teren", 2, "B", 2));
	add_to_list(a, creeaza_oferta("teren", 2, "B", 2));
	assert(is_in_list(a, cautat) != 0);  // Este in lista.
	assert(search_element(a, cautat, equals_oferta) == 0);
	destroy_list(a, distruge_oferta);

	a = create_list();
	cautat = creeaza_oferta("teren", 1, "A", 1);
	add_to_list(a, creeaza_oferta("teren", 2, "B", 2));
	add_to_list(a, cautat);
	add_to_list(a, creeaza_oferta("teren", 2, "B", 2));
	add_to_list(a, creeaza_oferta("teren", 2, "B", 2));
	assert(is_in_list(a, cautat) != 0);  // Este in lista.
	assert(search_element(a, cautat, equals_oferta) == 1);
	destroy_list(a, distruge_oferta);

	a = create_list();
	cautat = creeaza_oferta("teren", 1, "A", 1);
	add_to_list(a, creeaza_oferta("teren", 2, "B", 2));
	add_to_list(a, creeaza_oferta("teren", 2, "B", 2));
	add_to_list(a, creeaza_oferta("teren", 2, "B", 2));
	assert(is_in_list(a, cautat) == 0);  // Este in lista.
	assert(search_element(a, cautat, equals_oferta) == -1);
	distruge_oferta(cautat);
	destroy_list(a, distruge_oferta);
}

void test_lista_de_liste() {
	List* a = create_list();
	List* b = create_list();
	List* c = create_list();

	add_to_list(a, creeaza_oferta("teren", 1, "A", 1));
	add_to_list(a, creeaza_oferta("teren", 1, "A", 1));
	add_to_list(a, creeaza_oferta("teren", 1, "A", 1));

	List* lista = create_list();
	add_to_list(lista, a);
	add_to_list(lista, b);
	add_to_list(lista, c);

	assert(dim(lista) == 3);
	pop_lista_liste(lista);
	assert(dim(lista) == 2);
	destroy_list_de_liste(lista);
}

void test_copiere_lista() {
	List* a = create_list();
	add_to_list(a, creeaza_oferta("teren", 1, "A", 1));
	add_to_list(a, creeaza_oferta("teren", 1, "A", 1));
	add_to_list(a, creeaza_oferta("teren", 1, "A", 1));
	assert(dim(a) == 3);
	List* b = copy_list(a);
	assert(dim(b) == 3);
	pop_list(b, distruge_oferta);
	assert(dim(b) == 2 && dim(a) == 3);
	pop_list(a, distruge_oferta);
	assert(dim(b) == 2 && dim(a) == 2);

	destroy_list(a, distruge_oferta);
	destroy_list(b, distruge_oferta);


	List* c = create_list();
	List* d = copy_list(c);
	assert(dim(c) == 0 && dim(d) == 0);
	destroy_list(c, distruge_oferta);
	destroy_list(d, distruge_oferta);
}

void test_modificare() {
	List* a = create_list();
	Oferta* of = creeaza_oferta("teren", 2, "B", 2);
	Oferta* control = creeaza_oferta("teren", 2, "B", 2);
	Oferta* comparatie = creeaza_oferta("casa", 3, "C", 3);
	add_to_list(a, creeaza_oferta("teren", 1, "A", 1));
	add_to_list(a, of);
	add_to_list(a, creeaza_oferta("teren", 1, "A", 1));
	add_to_list(a, creeaza_oferta("teren", 1, "A", 1));
	modificare_element(a, of, creeaza_oferta("casa", 3, "C", 3), distruge_oferta);
	assert(is_in_list(a, control) == 0);
	assert(is_in_list(a, comparatie) == 1);
	assert(search_element(a, comparatie, equals_oferta) == 1);

	destroy_list(a, distruge_oferta);
	distruge_oferta(control);
	distruge_oferta(comparatie);
	
}

void run_all_list_tests(){
	test_add();
	test_cautare();
	test_delete();
	test_lista_de_liste();
	test_copiere_lista();
	test_modificare();
}

