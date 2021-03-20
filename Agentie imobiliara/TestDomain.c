#include "TestDomain.h"

#include <assert.h>
#include <string.h>
#include "oferta.h"


void run_domain_tests() {
	char adresa[12] = "Strada nr 1";
	char tip[10] = "teren";
	int suprafata = 100;
	int pret = 2000;

	Oferta* oferta = creeaza_oferta(tip, suprafata, adresa, pret);

	assert(strcmp(get_tip_oferta(oferta), tip) == 0);
	assert(strcmp(get_adresa_oferta(oferta), adresa) == 0);
	assert(get_suprafata_oferta(oferta) == suprafata);
	assert(get_pret_oferta(oferta) == pret);

	Oferta* oferta_noua = creeaza_oferta(tip, suprafata + 100, adresa, pret + 200);
	assert(equals_oferta(oferta, oferta_noua));

	set_tip_oferta(oferta_noua, "apartament");
	assert(equals_oferta(oferta, oferta_noua) == 0);
	assert(strcmp(get_tip_oferta(oferta_noua), "apartament") == 0);

	set_suprafata_oferta(oferta_noua, suprafata * 2);
	assert(get_suprafata_oferta(oferta_noua) == suprafata * 2);

	set_adresa_oferta(oferta_noua, "Arad, Arad, Grivitei, 2");
	assert(strcmp(get_adresa_oferta(oferta_noua), "Arad, Arad, Grivitei, 2") == 0);

	set_pret_oferta(oferta_noua, pret * 2);
	assert(get_pret_oferta(oferta_noua) == pret * 2);

	distruge_oferta(oferta);
	distruge_oferta(oferta_noua);
}

void run_all_domain_tests() {
	run_domain_tests();
}