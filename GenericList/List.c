#include "List.h"
#include <stddef.h>
#include <stdlib.h>

List create_list(){
	List rez;
	rez.prim = NULL;
	rez.ultim = NULL;
	rez.lungime = 0;

	return rez;
}

void destroy_nod(struct Nod* de_distrus) {
	free(de_distrus->data);
	free(de_distrus);
}

void destroy_list(List de_distrus) {
	if (de_distrus.lungime == 0) {
		return;  // Nu este nimic de eliberat.
	}
	else {
		while (de_distrus.prim != NULL) {  // Eliberam pana ajungem la null.
			struct Nod* urmator = de_distrus.prim->urmator;
			destroy_nod(de_distrus.prim);  // Eliberam datele din nodul curent.
			de_distrus.prim = urmator;
		}
	}
}

struct Nod* creade_nod(void* data) {
	struct Nod* new_node = (struct Nod*)malloc(sizeof(struct Nod));
	if (new_node != NULL) {
		new_node->data = data;
	}
	return new_node;
}

void add_to_list(List* lista, void* data) {
	struct Nod* nou = creade_nod(data);
	nou->urmator = NULL;
	if (lista->lungime == 0) {
		// Cazul primului element
		nou->precedent = NULL;
		lista->prim = nou;
		lista->ultim = nou;
	}
	else {
		lista->ultim->urmator = nou;  // Noul nod devine urmatorul fostului ultim.
		nou->precedent = lista->ultim;
		lista->ultim = nou;
	}

	lista->lungime++;
}

void* peek_date(List* lista) {
	if (lista->ultim != NULL) {
		return lista->ultim->data;
	}
	else
		return NULL; // List empty.
}

void pop_list(List* lista) {
	struct Nod* a = lista->ultim;
	lista->ultim->precedent->urmator = NULL;
	lista->lungime--;
	lista->ultim = a->precedent;
	destroy_nod(a);
}
