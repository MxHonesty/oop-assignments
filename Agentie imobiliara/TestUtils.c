#include "TestUtils.h"

#include <assert.h>
#include <string.h>
#include "oferta.h"
#include "validator.h"
#include "repo.h"
#include "service.h"
#include "utils.h"


int cmp(Oferta* oferta1, Oferta* oferta2, char* cheie, char* criteriu) {
	if (strcmp(cheie, "pret") == 0)
		if (strcmp(criteriu, "crescator") == 0) return get_pret_oferta(oferta1) < get_pret_oferta(oferta2);
		else return get_pret_oferta(oferta1) > get_pret_oferta(oferta2);
	else {
		if (strcmp(criteriu, "crescator") == 0) return strcmp(get_tip_oferta(oferta1), get_tip_oferta(oferta2)) < 0;
		return strcmp(get_tip_oferta(oferta1), get_tip_oferta(oferta2)) > 0;
	}
}

void run_utils_tests() {
	VectorOferte* oferte_sortate;

	Repository* repo_oferte;
	repo_oferte = creeaza_repo();
	Service* srv_oferte = creeaza_service(repo_oferte);

	srv_oferte = srv_adauga_oferta(srv_oferte, "casa", 100, "Adresa1", 2000);
	srv_oferte = srv_adauga_oferta(srv_oferte, "teren", 100, "Adresa2", 4000);
	srv_oferte = srv_adauga_oferta(srv_oferte, "apartament", 100, "Adresa3", 5000);
	srv_oferte = srv_adauga_oferta(srv_oferte, "casa", 100, "Adresa4", 1000);

	oferte_sortate = sorteaza(srv_oferte, "tip", "crescator", *cmp);
	assert(strcmp(get_adresa_oferta(oferte_sortate->oferte[0]), "Adresa3") == 0);
	assert(strcmp(get_adresa_oferta(oferte_sortate->oferte[1]), "Adresa4") == 0);
	assert(strcmp(get_adresa_oferta(oferte_sortate->oferte[2]), "Adresa1") == 0);
	assert(strcmp(get_adresa_oferta(oferte_sortate->oferte[3]), "Adresa2") == 0);
	free(oferte_sortate->oferte);
	free(oferte_sortate);

	oferte_sortate = sorteaza(srv_oferte, "tip", "descrescator", *cmp);
	assert(strcmp(get_adresa_oferta(oferte_sortate->oferte[0]), "Adresa2") == 0);
	assert(strcmp(get_adresa_oferta(oferte_sortate->oferte[1]), "Adresa4") == 0);
	assert(strcmp(get_adresa_oferta(oferte_sortate->oferte[2]), "Adresa1") == 0);
	assert(strcmp(get_adresa_oferta(oferte_sortate->oferte[3]), "Adresa3") == 0);
	free(oferte_sortate->oferte);
	free(oferte_sortate);

	oferte_sortate = sorteaza(srv_oferte, "pret", "crescator", *cmp);;
	assert(strcmp(get_adresa_oferta(oferte_sortate->oferte[0]), "Adresa4") == 0);
	assert(strcmp(get_adresa_oferta(oferte_sortate->oferte[1]), "Adresa1") == 0);
	assert(strcmp(get_adresa_oferta(oferte_sortate->oferte[2]), "Adresa2") == 0);
	assert(strcmp(get_adresa_oferta(oferte_sortate->oferte[3]), "Adresa3") == 0);
	free(oferte_sortate->oferte);
	free(oferte_sortate);

	oferte_sortate = sorteaza(srv_oferte, "pret", "descrescator", *cmp);
	assert(strcmp(get_adresa_oferta(oferte_sortate->oferte[0]), "Adresa3") == 0);
	assert(strcmp(get_adresa_oferta(oferte_sortate->oferte[1]), "Adresa2") == 0);
	assert(strcmp(get_adresa_oferta(oferte_sortate->oferte[2]), "Adresa1") == 0);
	assert(strcmp(get_adresa_oferta(oferte_sortate->oferte[3]), "Adresa4") == 0);

	free(oferte_sortate->oferte);
	free(oferte_sortate);
	eliberare_repo(srv_oferte->repo_oferte);
	free(srv_oferte);
}

void run_all_utils_tests() {
	run_utils_tests();
}