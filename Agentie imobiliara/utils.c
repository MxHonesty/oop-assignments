#include "service.h"
#include "oferta.h"

#include <string.h>
#include <stdlib.h>

VectorOferte* sorteaza(Service* srv_oferte, char*cheie, char*criteriu, int (*cmp)(Oferta*, Oferta*, char*, char*)) {
	/*
	* returneaza o lista de oferte sortata dupa cheie si criteriu
	* cheie - sir de caractere: pret / tip
	* criteriu - sir de caractere: crescator / descrescastor
	* cmp - pointer la functia de comparare
	*/
	VectorOferte* oferte;
	oferte = (VectorOferte*)malloc(sizeof(VectorOferte));
	oferte->size = dim(srv_oferte->elems);
	oferte->oferte = (Oferta**)malloc(oferte->size * sizeof(Oferta*));

	for (int i = 0; i < oferte->size; ++i)
		oferte->oferte[i] = srv_oferte->elems->list[i];

	for (int i = 0; i < oferte->size; ++i)
		for (int j = i + 1; j < oferte->size; ++j)
			if (cmp(oferte->oferte[i], oferte->oferte[j], cheie, criteriu) == 0) {
				Oferta* oferta_aux;
				oferta_aux = oferte->oferte[i];
				oferte->oferte[i] = oferte->oferte[j];
				oferte->oferte[j] = oferta_aux;
			}
	return oferte;

}