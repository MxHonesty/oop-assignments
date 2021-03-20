#include "TestService.h"

#include <assert.h>
#include <string.h>
#include "oferta.h"
#include "service.h"


void run_srv_sorteaza_tests() {
	VectorOferte* oferte_sortate;

	Repository* repo_oferte;
	repo_oferte = creeaza_repo();
	Service* srv_oferte = creeaza_service(repo_oferte);

	oferte_sortate = srv_sorteaza_oferte(srv_oferte, "tip", "crescator");
	assert(oferte_sortate->size == 0);
	free(oferte_sortate->oferte);
	free(oferte_sortate);
	oferte_sortate = srv_sorteaza_oferte(srv_oferte, "ti", "crescator");
	assert(oferte_sortate->size == -1);
	free(oferte_sortate->oferte);
	free(oferte_sortate);
	oferte_sortate = srv_sorteaza_oferte(srv_oferte, "tip", "cresator");
	assert(oferte_sortate->size == -1);
	free(oferte_sortate->oferte);
	free(oferte_sortate);

	srv_oferte = srv_adauga_oferta(srv_oferte, "casa", 100, "Adresa1", 2000);
	srv_oferte = srv_adauga_oferta(srv_oferte, "teren", 100, "Adresa2", 4000);
	srv_oferte = srv_adauga_oferta(srv_oferte, "apartament", 100, "Adresa3", 5000);
	srv_oferte = srv_adauga_oferta(srv_oferte, "casa", 100, "Adresa4", 1000);

	oferte_sortate = srv_sorteaza_oferte(srv_oferte, "tip", "crescator");
	assert(strcmp(get_adresa_oferta(oferte_sortate->oferte[0]), "Adresa3") == 0);
	assert(strcmp(get_adresa_oferta(oferte_sortate->oferte[1]), "Adresa1") == 0);
	assert(strcmp(get_adresa_oferta(oferte_sortate->oferte[2]), "Adresa4") == 0);
	assert(strcmp(get_adresa_oferta(oferte_sortate->oferte[3]), "Adresa2") == 0);
	free(oferte_sortate->oferte);
	free(oferte_sortate);

	oferte_sortate = srv_sorteaza_oferte(srv_oferte, "tip", "descrescator");
	assert(strcmp(get_adresa_oferta(oferte_sortate->oferte[0]), "Adresa2") == 0);
	assert(strcmp(get_adresa_oferta(oferte_sortate->oferte[1]), "Adresa1") == 0);
	assert(strcmp(get_adresa_oferta(oferte_sortate->oferte[2]), "Adresa4") == 0);
	assert(strcmp(get_adresa_oferta(oferte_sortate->oferte[3]), "Adresa3") == 0);
	free(oferte_sortate->oferte);
	free(oferte_sortate);

	oferte_sortate = srv_sorteaza_oferte(srv_oferte, "pret", "crescator");
	assert(strcmp(get_adresa_oferta(oferte_sortate->oferte[0]), "Adresa4") == 0);
	assert(strcmp(get_adresa_oferta(oferte_sortate->oferte[1]), "Adresa1") == 0);
	assert(strcmp(get_adresa_oferta(oferte_sortate->oferte[2]), "Adresa2") == 0);
	assert(strcmp(get_adresa_oferta(oferte_sortate->oferte[3]), "Adresa3") == 0);
	free(oferte_sortate->oferte);
	free(oferte_sortate);

	oferte_sortate = srv_sorteaza_oferte(srv_oferte, "pret", "descrescator");
	assert(strcmp(get_adresa_oferta(oferte_sortate->oferte[0]), "Adresa3") == 0);
	assert(strcmp(get_adresa_oferta(oferte_sortate->oferte[1]), "Adresa2") == 0);
	assert(strcmp(get_adresa_oferta(oferte_sortate->oferte[2]), "Adresa1") == 0);
	assert(strcmp(get_adresa_oferta(oferte_sortate->oferte[3]), "Adresa4") == 0);
	free(oferte_sortate->oferte);
	free(oferte_sortate);

	distruge_service(srv_oferte);
}

void run_srv_filter_tests() {
	VectorOferte* oferte_filtrate;

	Repository* repo_oferte;
	repo_oferte = creeaza_repo();
	Service* srv_oferte = creeaza_service(repo_oferte);

	srv_oferte = srv_adauga_oferta(srv_oferte, "casa", 100, "Adresa1", 2000);
	srv_oferte = srv_adauga_oferta(srv_oferte, "teren", 100, "Adresa2", 4000);
	srv_oferte = srv_adauga_oferta(srv_oferte, "apartament", 100, "Adresa3", 5000);
	srv_oferte = srv_adauga_oferta(srv_oferte, "casa", 100, "Adresa2", 1000);

	oferte_filtrate = srv_filtreaza_oferte(srv_oferte, "tip", "casa", "", 0);
	assert(oferte_filtrate->size == 2);
	free(oferte_filtrate->oferte);
	free(oferte_filtrate);

	oferte_filtrate = srv_filtreaza_oferte(srv_oferte, "pret", "", "<", 1500);
	assert(oferte_filtrate->size == 1);
	free(oferte_filtrate->oferte);
	free(oferte_filtrate);

	oferte_filtrate = srv_filtreaza_oferte(srv_oferte, "suprafata", "", ">", 50);
	assert(oferte_filtrate->size == 4);
	free(oferte_filtrate->oferte);
	free(oferte_filtrate);

	oferte_filtrate = srv_filtreaza_oferte(srv_oferte, "adresa", "Adresa3", "<", 50);
	assert(oferte_filtrate->size == 1);
	free(oferte_filtrate->oferte);
	free(oferte_filtrate);

	oferte_filtrate = srv_filtreaza_oferte(srv_oferte, "adresa", "Adresa2", "<", 50);
	assert(oferte_filtrate->size == 2);
	free(oferte_filtrate->oferte);
	free(oferte_filtrate);

	distruge_service(srv_oferte);
}

void run_service_tests() {
	Repository* repo_oferte;
	repo_oferte = creeaza_repo();
	Service* srv_oferte = creeaza_service(repo_oferte);

	char* adresa = "Strada nr 1";
	char* tip = "teren";
	int suprafata = 100;
	int pret = 2000;
	srv_oferte = srv_adauga_oferta(srv_oferte, tip, suprafata, adresa, pret);

	assert(srv_oferte->repo_oferte->dimensiune == 1);
	srv_oferte = srv_adauga_oferta(srv_oferte, tip, suprafata, adresa, pret);
	assert(strcmp(srv_oferte->eroare, "oferta deja existenta!\n") == 0);
	srv_oferte = srv_adauga_oferta(srv_oferte, "Casa", -1, "", -1);
	assert(strcmp(srv_oferte->eroare, "Tipul invalid!\nSuprafata invalida!\nAdresa invalida!\nPretul invalid!\n") == 0);
	srv_oferte = srv_adauga_oferta(srv_oferte, "apartament", 100, "Arad", 17500);
	Oferta* oferta = creeaza_oferta("apartament", 100, "Arad", 17500);
	srv_oferte = srv_afisare_oferte(srv_oferte);
	assert(srv_oferte->repo_oferte->dimensiune == 2);
	assert(equals_oferta(srv_oferte->repo_oferte->oferte[1], oferta));

	srv_oferte = srv_modifica_oferta(srv_oferte, "apartament", "Arad", "teren", 200, "Cluj", 35500);
	Oferta* oferta2 = creeaza_oferta("teren", 200, "Cluj", 35500);
	srv_oferte = srv_afisare_oferte(srv_oferte);
	assert(equals_oferta(srv_oferte->repo_oferte->oferte[1], oferta2));
	srv_oferte = srv_sterge_oferta(srv_oferte, "casa", "Bucuresti");
	assert(strcmp(srv_oferte->eroare, "oferta inexistenta!\n") == 0);
	srv_oferte = srv_sterge_oferta(srv_oferte, tip, adresa);

	assert(strcmp(srv_oferte->eroare, "Operatie efectuata cu succes.\n") == 0);
	srv_oferte = srv_sterge_oferta(srv_oferte, "", "");
	assert(strcmp(srv_oferte->eroare, "Tipul invalid!\nAdresa invalida!\n") == 0);

	srv_oferte = srv_modifica_oferta(srv_oferte, "", "", "", -1, "", -1);
	assert(strcmp(srv_oferte->eroare, "Tipul invalid!\nAdresa invalida!\nTipul invalid!\nSuprafata invalida!\nAdresa invalida!\nPretul invalid!\n") == 0);
	srv_oferte = srv_modifica_oferta(srv_oferte, "casa", "Ardeal", "casa", 2, "Cluj", 1000);
	assert(strcmp(srv_oferte->eroare, "oferta initiala este inexistenta!\n") == 0);

	distruge_oferta(oferta);
	distruge_oferta(oferta2);

	distruge_service(srv_oferte);
}

void run_srv_undo_test() {
	Repository* repo_oferte;
	repo_oferte = creeaza_repo();
	Service* srv = creeaza_service(repo_oferte);

	char* adresa = "Strada nr 1";
	char* tip = "teren";
	int suprafata = 100;
	int pret = 2000;
	srv = srv_adauga_oferta(srv, tip, suprafata, adresa, pret);
	
	char* adresa2 = "Strada nr 2";
	srv = srv_adauga_oferta(srv, tip, suprafata, adresa2, pret);

	Oferta* oferta_de_cautat = creeaza_oferta("teren", 100, "Strada nr 2", 2000);
	assert(gaseste_oferta(srv->repo_oferte, oferta_de_cautat));
	
	service_undo(srv);  // Executam undo.
	assert(!gaseste_oferta(srv->repo_oferte, oferta_de_cautat));

	
	
	
	
	distruge_oferta(oferta_de_cautat);
	distruge_service(srv);
}

void run_all_service_tests(){
	run_service_tests();
	run_srv_filter_tests();
	run_srv_sorteaza_tests();

	run_srv_undo_test();
}
