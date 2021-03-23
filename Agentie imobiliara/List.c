#include "List.h"
#include "repo.h"
#include <stddef.h>
#include <stdlib.h>

List* create_list(){
	List* rez = malloc(sizeof(List));
	rez->lungime = 0;
	rez->capacitate = 10;
	rez->list = (void*)malloc(sizeof(void*) * rez->capacitate);
	return rez;
}

int dim(List* lista){
	return lista->lungime;
}

void destroy_list(List* de_distrus, Destructor des) {
	for (int i = 0; i < de_distrus->lungime; i++) {
		des(de_distrus->list[i]);
	}
	free(de_distrus->list);
	free(de_distrus);
}

void add_to_list(List* lista, void* data) {
	if (lista->lungime >= lista->capacitate)
		redim_lista(lista);
	lista->list[lista->lungime] = data;
	lista->lungime++;
}

void redim_lista(List* la_lista) {
	void** new_list = (void**)malloc(sizeof(void*) * la_lista->capacitate * 2);  // Dubleaza cap.
	for (int i = 0; i < la_lista->lungime; i++)
		new_list[i] = la_lista->list[i];

	free(la_lista->list);
	la_lista->list = new_list;
	la_lista->capacitate *= 2;
}

int search_element(List* lista, void* date, Comparatie comp){
	for (int i = 0; i < lista->lungime; i++)
		if (comp(lista->list[i], date))
			return i;

	return -1;
}

int is_in_list(List* lista, void* date){
	if (search_element(lista, date, equals_oferta) == -1)
		return 0;
	return 1;
}

void delete_from_list(List* lista, void* date, Destructor des){
	int poz = search_element(lista, date, equals_oferta);
	if (poz != -1){
		delete_by_index(lista, poz, des);  // Stergem prin index daca e valid.
	}
}

void delete_by_index(List* lista, int index, Destructor des){
	if (index >= 0 && index < lista->lungime) {
		des(lista->list[index]);  // Distrugem element
		for (int i = index; i < lista->lungime - 1; i++)
			lista->list[i] = lista->list[i + 1];
	}
	lista->lungime--;
}

void destroy_list_de_liste(List* lista){
	for (int i = 0; i < lista->lungime; i++)
		destroy_list(lista->list[i], distruge_oferta);
	free(lista->list);  // FOARTE IMPORTANT dealocam array-ul.
	free(lista);
}

void pop_lista_liste(List* lista){
	if (lista->lungime >= 1) {
		destroy_list(lista->list[lista->lungime - 1], distruge_oferta);  // Destruge lista membu.
		lista->lungime--;
	}
}

List* copy_list(List* lista_de_copiat){
	List* a = create_list();
	for (int i = 0; i < lista_de_copiat->lungime; i++) {
		Oferta* elem = lista_de_copiat->list[i];
		Oferta* elem_copy = creeaza_oferta(elem->tip, elem->suprafata, elem->adresa, elem->pret);
		add_to_list(a, elem_copy);
	}
	return a;
}

void* peek_date(List* lista) {
	return lista->list[lista->lungime - 1];
}

void pop_list(List* lista, Destructor des) {
	if (lista->lungime >= 1) {
		des(lista->list[lista->lungime - 1]);
		lista->lungime--;
	}
}

void modificare_element(List* lista, void* inlocuit, void* nou, Destructor des) {
	int poz = search_element(lista, inlocuit, equals_oferta);
	if (poz != -1) {  // Daca este in lista
		des(inlocuit);
		lista->list[poz] = nou;
	}
}