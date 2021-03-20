#include "TestValidare.h"

#include <assert.h>
#include <string.h>
#include "oferta.h"
#include "validator.h"


void run_valid_tests() {
	char* adresa = "Strada nr 1";
	char* tip = "teren";
	int suprafata = 100;
	int pret = 2000;

	Oferta* oferta = creeaza_oferta(tip, suprafata, adresa, pret);
	assert(strcmp(validate_oferta(oferta), "") == 0);

	set_adresa_oferta(oferta, "");
	set_pret_oferta(oferta, -2);
	set_tip_oferta(oferta, "Tip");
	set_suprafata_oferta(oferta, -10);

	assert(strcmp(validate_oferta(oferta), "Tipul invalid!\nSuprafata invalida!\nAdresa invalida!\nPretul invalid!\n") == 0);
	assert(validate_criteriu("suprafata"));
	assert(validate_criteriu("supr") == 0);

	distruge_oferta(oferta);
}

void run_all_valid_tests() {
	run_valid_tests();
}