#include "TestService.h"

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "oferta.h"
#include "service.h"

void test_service_adaugare() {
	Service* srv = creeaza_service();  // Caz corect
	srv_adauga_oferta(srv, "teren", 1, "A", 1);
	srv_adauga_oferta(srv, "teren", 1, "B", 1);
	srv_adauga_oferta(srv, "teren", 1, "C", 1);
	srv_adauga_oferta(srv, "teren", 1, "D", 1);
	assert(dim(srv->elems) == 4);
	distruge_service(srv);

	srv = creeaza_service();  // Elemente identice
	srv_adauga_oferta(srv, "teren", 1, "A", 1);
	srv_adauga_oferta(srv, "teren", 1, "A", 1);
	srv_adauga_oferta(srv, "teren", 1, "A", 1);
	srv_adauga_oferta(srv, "teren", 1, "B", 1);
	srv_adauga_oferta(srv, "teren", 1, "C", 1);
	srv_adauga_oferta(srv, "teren", 1, "C", 1);
	srv_adauga_oferta(srv, "teren", 1, "C", 1);
	srv_adauga_oferta(srv, "teren", 1, "C", 1);
	srv_adauga_oferta(srv, "teren", 1, "C", 1);
	assert(dim(srv->elems) == 3);
	distruge_service(srv);

	srv = creeaza_service();  // Elemente invalide
	srv_adauga_oferta(srv, "A", 1, "A", 1);
	srv_adauga_oferta(srv, "A", 1, "A", 1);
	srv_adauga_oferta(srv, "A", 1, "A", 1);
	srv_adauga_oferta(srv, "A", 1, "A", 1);
	assert(dim(srv->elems) == 0);
	distruge_service(srv);
}

void test_service_update() {
	Service* srv = creeaza_service();
	srv_adauga_oferta(srv, "teren", 1, "A", 1);
	srv_adauga_oferta(srv, "teren", 1, "B", 1);
	srv_adauga_oferta(srv, "teren", 1, "C", 1);
	srv_adauga_oferta(srv, "teren", 1, "D", 1);
	srv_modifica_oferta(srv, "teren", "A", "casa", 2, "A", 2);  // Cazul corect
	assert(dim(srv->elems) == 4);
	Oferta* de_comparatie = creeaza_oferta("teren", 1, "A", 1);
	assert(!is_in_list(srv->elems, de_comparatie));
	distruge_oferta(de_comparatie);
	de_comparatie = creeaza_oferta("casa", 2, "A", 2);
	assert(is_in_list(srv->elems, de_comparatie));
	distruge_oferta(de_comparatie);


	// Cazul cu element nou invalid.
	srv_modifica_oferta(srv, "casa", "B", "casa", 2, "ABA", 2);  // Nu exista
	assert(strcmp(srv->eroare, "oferta initiala este inexistenta!\n") == 0);
	de_comparatie = creeaza_oferta("casa", 2, "ABA", 2);
	assert(!is_in_list(srv->elems, de_comparatie));
	distruge_oferta(de_comparatie);


	// Cazul date de intrare invalide pentru oferta.
	srv_modifica_oferta(srv, "teren", "C", "incorect", 10, "salut", 10);
	assert(strcmp(srv->eroare, "Tipul invalid!\n") == 0);

	distruge_service(srv);
}


void test_service_stergere() {
	Service* srv = creeaza_service();
	Oferta* de_comparatie;
	
	srv_adauga_oferta(srv, "teren", 1, "A", 1);
	srv_adauga_oferta(srv, "teren", 1, "B", 1);
	srv_adauga_oferta(srv, "teren", 1, "C", 1);
	srv_adauga_oferta(srv, "teren", 1, "D", 1);
	// Cazul corect.
	srv_sterge_oferta(srv, "teren", "C");
	de_comparatie = creeaza_oferta("teren", 1, "C", 1);
	assert(!is_in_list(srv->elems, de_comparatie));
	distruge_oferta(de_comparatie);

	// Cazul oferta inexistenta. 
	srv_sterge_oferta(srv, "casa", "A");
	assert(strcmp(srv->eroare, "oferta inexistenta!\n") == 0);

	// Oferta invalida.
	srv_sterge_oferta(srv, "imposibil", "A");
	assert(strcmp(srv->eroare, "Tipul invalid!\n") == 0);

	distruge_service(srv);
}

void test_service_undo() {
	Service* srv = creeaza_service();
	Oferta* de_comparatie;  // Pentru stocare elemente de comparatie.
	assert(dim(srv->repo_history) == 1);  // Lista istoric are minim un element.
	srv_adauga_oferta(srv, "teren", 1, "A", 1);
	srv_adauga_oferta(srv, "teren", 1, "B", 1);
	srv_adauga_oferta(srv, "teren", 1, "C", 1);
	srv_adauga_oferta(srv, "teren", 1, "D", 1);
	assert(dim(srv->repo_history) == 5);
	service_undo(srv);
	assert(dim(srv->repo_history) == 4);
	
	de_comparatie = creeaza_oferta("teren", 1, "D", 1);
	assert(!is_in_list(srv->elems, de_comparatie));
	distruge_oferta(de_comparatie);

	for (int i = 0; i < 10; i++)
		service_undo(srv);

	assert(dim(srv->repo_history) == 1);
	de_comparatie = creeaza_oferta("teren", 1, "A", 1);
	assert(!is_in_list(srv->elems, de_comparatie));
	distruge_oferta(de_comparatie);


	srv_adauga_oferta(srv, "teren", 1, "A", 1);
	srv_adauga_oferta(srv, "teren", 1, "B", 1);
	srv_adauga_oferta(srv, "teren", 1, "C", 1);
	srv_adauga_oferta(srv, "teren", 1, "D", 1);
	// Testam stergerea
	srv_sterge_oferta(srv, "teren", "A");
	assert(dim(srv->repo_history) == 6);
	de_comparatie = creeaza_oferta("teren", 1, "A", 1);
	assert(!is_in_list(srv->elems, de_comparatie));
	service_undo(srv);
	assert(is_in_list(srv->elems, de_comparatie));
	assert(dim(srv->repo_history) == 5);
	distruge_oferta(de_comparatie);

	distruge_service(srv);
}

void run_service_tests() {
	test_service_adaugare();
	test_service_update();
	test_service_stergere();
	test_service_undo();
}


void run_srv_sorteaza_tests() {
	Service* srv = creeaza_service();
	srv_adauga_oferta(srv, "apartament", 3, "B", 3);
	srv_adauga_oferta(srv, "teren", 4, "A", 4);
	srv_adauga_oferta(srv, "casa", 2, "C", 2);
	srv_adauga_oferta(srv, "casa", 1, "D", 1);

	VectorOferte* oferte = srv_sorteaza_oferte(srv, "pret", "imbosibil");  // Criteriu gresit
	assert(oferte->oferte == NULL);
	free(oferte);

	Oferta* de_comparat1 = creeaza_oferta("casa", 1, "D", 1);
	Oferta* de_comparat2 = creeaza_oferta("casa", 2, "C", 2);
	Oferta* de_comparat3 = creeaza_oferta("apartament", 3, "B", 3);
	Oferta* de_comparat4 = creeaza_oferta("teren", 4, "A", 4);

	oferte = srv_sorteaza_oferte(srv, "pret", "crescator");
	assert(equals_oferta(oferte->oferte[0], de_comparat1));
	assert(equals_oferta(oferte->oferte[1], de_comparat2));
	assert(equals_oferta(oferte->oferte[2], de_comparat3));
	assert(equals_oferta(oferte->oferte[3], de_comparat4));

	free(oferte->oferte);
	free(oferte);

	oferte = srv_sorteaza_oferte(srv, "pret", "descrescator");
	assert(equals_oferta(oferte->oferte[0], de_comparat4));
	assert(equals_oferta(oferte->oferte[1], de_comparat3));
	assert(equals_oferta(oferte->oferte[2], de_comparat2));
	assert(equals_oferta(oferte->oferte[3], de_comparat1));

	free(oferte->oferte);
	free(oferte);

	oferte = srv_sorteaza_oferte(srv, "tip", "crescator");
	assert(equals_oferta(oferte->oferte[0], de_comparat3));

	free(oferte->oferte);
	free(oferte);

	oferte = srv_sorteaza_oferte(srv, "tip", "descrescator");
	assert(equals_oferta(oferte->oferte[0], de_comparat4));

	free(oferte->oferte);
	free(oferte);

	distruge_oferta(de_comparat1);
	distruge_oferta(de_comparat2);
	distruge_oferta(de_comparat3);
	distruge_oferta(de_comparat4);


	distruge_service(srv);
}

void run_srv_filter_tests() {
	VectorOferte* oferte_filtrate;
	Service* srv_oferte = creeaza_service();

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

void run_sample_data_test() {
	Service* srv = creeaza_service();
	sample_data(srv);
	assert(dim(srv->elems) == 10);

	distruge_service(srv);
}

void test_afisare_oferte() {
	Service* srv = creeaza_service();
	
	srv_afisare_oferte(srv);
	assert(strcmp(srv->eroare, "nu exista oferte deocamdata.\n") == 0);

	srv_adauga_oferta(srv, "teren", 1, "A", 1);
	srv_afisare_oferte(srv);

	distruge_service(srv);
}

void run_all_service_tests(){
	run_service_tests();
	run_srv_filter_tests();
	run_srv_sorteaza_tests();
	run_sample_data_test();
	test_afisare_oferte();
}
