#include "oferta.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Oferta* creeaza_oferta(char* tip, int suprafata, char* adresa, int pret) {
	/*
	returneaza o entitate de oferta creata cu datele de intrare
	tip - sir de caractere
	suprafata - nr intreg
	adresa - sir de caractere
	pret - numar intreg
	*/
	Oferta* oferta = (Oferta*)malloc(sizeof(Oferta));
	
	if (oferta != NULL) {
		oferta->tip = malloc((strlen(tip) + 1) * sizeof(char));
		if (oferta->tip) strcpy(oferta->tip, tip);

		oferta->adresa = malloc((strlen(adresa) + 1) * sizeof(char));
		if (oferta->adresa) strcpy(oferta->adresa, adresa);

		oferta->suprafata = suprafata;
		oferta->pret = pret;
	}
	return oferta;
}

char* get_tip_oferta(Oferta *oferta) {
	/*
	returneaza tipul unei oferte date - sir de caractere
	oferta - Oferta*
	*/
	return oferta->tip;
}

int get_suprafata_oferta(Oferta* oferta) {
	/*
	returneaza suprafata unei oferte date - numar intreg
	oferta - Oferta*
	*/
	return oferta->suprafata;
}

char* get_adresa_oferta(Oferta* oferta) {
	/*
	returneaza adresa unei oferte date - sir de caractere
	oferta - Oferta*
	*/
	return oferta->adresa;
}

int get_pret_oferta(Oferta* oferta) {
	/*
	returneaza pretul unei oferte date - numar intreg
	oferta - Oferta*
	*/
	return oferta->pret;
}

void set_tip_oferta(Oferta* oferta, char* tip_nou) {
	/*
	* seteaza tipul unei oferte 
	* tip_nou - sir de caractere
	* oferta - Oferta*
	*/
	free(oferta->tip);
	oferta->tip = malloc((strlen(tip_nou) + 1) * sizeof(char));
	if (oferta->tip) strcpy(oferta->tip, tip_nou);
}

void set_suprafata_oferta(Oferta* oferta, int suprafata_noua) {
	/*
	* seteaza suprafata unei oferte 
	* suprafata_noua - numar intreg
	* oferta - Oferta*
	*/
	oferta->suprafata = suprafata_noua;
}

void set_adresa_oferta(Oferta* oferta, char* adresa_noua) {
	/*
	* seteaza adresa unei oferte 
	* adresa_noua - sir de caractere
	* oferta - Oferta*
	*/
	free(oferta->adresa);
	oferta->adresa = malloc((strlen(adresa_noua) + 1) * sizeof(char));
	if (oferta->adresa) strcpy(oferta->adresa, adresa_noua);
}

void set_pret_oferta(Oferta* oferta, int pret_nou) {
	/*
	* seteaza pretul unei oferte
	* pret_nou - numar intreg
	* oferta - Oferta*
	*/
	oferta->pret = pret_nou;
}

void distruge_oferta(Oferta* oferta) {
	/*
	* elibereaza spatiul ocupat de o oferta
	* oferta - Oferta
	*/
	free(oferta->tip);
	free(oferta->adresa);
	free(oferta);
}

int equals_oferta(Oferta* oferta1, Oferta* oferta2) {
	/*
	* returneaza true (!=0) daca doua oferte sunt echivalente (tip si adrese identice),
	* false (0) in caz contrar
	* oferta1, oferta2 - Oferta
	*/
	return strcmp(get_adresa_oferta(oferta1),get_adresa_oferta(oferta2)) == 0 && strcmp(get_tip_oferta(oferta1), get_tip_oferta(oferta2)) == 0;
}
