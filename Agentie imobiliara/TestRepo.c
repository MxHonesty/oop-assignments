#include "TestRepo.h"

#include <assert.h>
#include <string.h>
#include "repo.h"


void run_repo_tests() {
	Repository* repo;
	repo = creeaza_repo();

	assert(gaseste_oferta(repo, NULL) == 0);

	char* adresa = "Strada nr 1";
	char* tip = "teren";
	int suprafata = 100;
	int pret = 2000;
	Oferta* oferta1 = creeaza_oferta(tip, suprafata, adresa, pret);

	repo = adauga_oferta(repo, oferta1);
	assert(len(repo) == 1);
	assert(equals_oferta(repo->oferte[0], oferta1));

	char* adresa2 = "Strada nr 2";
	char* tip2 = "casa";
	Oferta* oferta2 = creeaza_oferta(tip2, suprafata, adresa2, pret);

	repo = adauga_oferta(repo, oferta2);
	assert(len(repo) == 2);
	assert(equals_oferta(repo->oferte[1], oferta2));

	assert(gaseste_oferta(repo, oferta1));
	assert(gaseste_oferta(repo, oferta2));

	repo = get_all(repo);
	assert(repo->dimensiune == 2);
	assert(equals_oferta(oferta1, repo->oferte[0]));
	assert(equals_oferta(oferta2, repo->oferte[1]));

	char* adresa3 = "Strada nr 3";
	char* tip3 = "casa";
	suprafata = 100;
	pret = 2000;
	Oferta* oferta3 = creeaza_oferta(tip3, suprafata, adresa3, pret);

	modificare_oferta(repo, oferta1, oferta3);
	repo = get_all(repo);
	assert(equals_oferta(repo->oferte[0], oferta3));
	assert(strcmp(get_adresa_oferta(repo->oferte[0]), adresa3) == 0);

	repo = sterge_oferta(repo, oferta2);

	assert(len(repo) == 1);
	assert(gaseste_oferta(repo, oferta2) == 0);

	repo = sterge_oferta(repo, oferta3);

	assert(len(repo) == 0);

	distruge_oferta(oferta3);
	distruge_oferta(oferta1);
	distruge_oferta(oferta2);
	eliberare_repo(repo);
}

void run_all_repo_tests() {
	run_repo_tests();
}