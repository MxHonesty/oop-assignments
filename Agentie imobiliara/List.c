#include "List.h"
#include "repo.h"
#include <stddef.h>
#include <stdlib.h>

List create_list(){
	List rez;
	rez.lungime = 0;
	rez.capacitate = 10;
	rez.list = (void*)malloc(sizeof(void*) * rez.capacitate);
	return rez;
}

void destroy_repo_list(List de_distrus) {
	for (int i = 0; i < de_distrus.lungime; i++) {
		Repository* repo = de_distrus.list[i];
		eliberare_repo(repo);
	}
	free(de_distrus.list);
}

void destroy_list(List de_distrus) {
	for (int i = 0; i < de_distrus.lungime; i++) {
		free(de_distrus.list[i]);
	}
	free(de_distrus.list);
}

void add_to_list(List* lista, void* data) {
	if (lista->lungime >= lista->capacitate)
		redim_lista(lista);
	lista->list[lista->lungime] = data;
	lista->lungime++;
}

void add_repo_to_list(List* lista, void* data) {
	if (lista->lungime >= lista->capacitate)
		redim_repo_lista(lista);
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

void redim_repo_lista(List* la_lista) {
	void** new_list = (void**)malloc(sizeof(void*) * la_lista->capacitate * 2);  // Dubleaza cap.
	for (int i = 0; i < la_lista->lungime; i++)
		new_list[i] = la_lista->list[i];

	free(la_lista->list);
	la_lista->list = new_list;
	la_lista->capacitate *= 2;
}

void* peek_date(List* lista) {
	return lista->list[lista->lungime - 1];
}

void pop_list(List* lista) {
	if (lista->lungime >= 1) {
		free(lista->list[lista->lungime - 1]);
		lista->lungime--;
	}
}

void pop_repo_list(List* lista) {
	if (lista->lungime >= 1) {
		eliberare_repo(lista->list[lista->lungime - 1]);
		lista->lungime--;
	}
}
