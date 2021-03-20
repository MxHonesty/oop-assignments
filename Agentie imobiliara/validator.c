#include "oferta.h"

#include <string.h>
#include <stdio.h>


char eroare[70];

char* validate_oferta (Oferta* oferta) {
	/*
	* returneaza un sir vid daca oferta este valida,
	* un sir de mesaje in caz contrar
	* oferta - Oferta
	*/
	strcpy(eroare, "");

	if (strcmp(get_tip_oferta(oferta), "teren") && strcmp(get_tip_oferta(oferta), "apartament")
		&& strcmp(get_tip_oferta(oferta), "casa")) {
		strcat(eroare, "Tipul invalid!\n");
	}

	if (get_suprafata_oferta(oferta) <= 0) {
		strcat(eroare, "Suprafata invalida!\n");
	}

	if (strlen(get_adresa_oferta(oferta)) == 0) {
		strcat(eroare, "Adresa invalida!\n");
	}

	if (get_pret_oferta(oferta) <= 0) {
		strcat(eroare, "Pretul invalid!\n");
	}

	return eroare;
}


int validate_criteriu(char* criteriu) {
	/*
	* returneaza true daca un criteriu este valid (suprafata, tip, pret)
	* criteriu - sir de caractere
	*/
	if (strcmp(criteriu, "suprafata") * strcmp(criteriu, "tip") * strcmp(criteriu, "pret") * strcmp(criteriu, "adresa") != 0) return 0;
	return 1;
}