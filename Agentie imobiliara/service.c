#include "repo.h"
#include "validator.h"
#include "service.h"
#include "utils.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Service* creeaza_service(Repository* repo) {
	/*
	* returneaza o entitate noua de tip Service*
	* repo - Repository*
	*/
	Service* service;
	service = (Service*)malloc(sizeof(Service));
	service->repo_oferte = repo;
	service->repo_history = create_list();
	add_to_list(&service->repo_history, repo_copy(repo));
	return service;
}

void distruge_service(Service* de_sters) {
	destroy_repo_list(de_sters->repo_history);
	eliberare_repo(de_sters->repo_oferte);
	free(de_sters);
}

Service* srv_adauga_oferta(Service* srv_oferte, char* tip, int suprafata, char* adresa, int pret) {
	/*
	* returneaza o entitate de service in urma adaugarii unei oferte date prin campurile sale,
	* eventual semnaland si o eroare
	* srv_oferte - service
	* tip - sir de caractere
	* suprafata - numar intreg
	* adresa - sir de caractere
	* pret - numar intreg
	*/
	Oferta* oferta = creeaza_oferta(tip, suprafata, adresa, pret);
	strcpy(srv_oferte->eroare, "Operatie efectuata cu succes.\n");

	char eroare[100] = "";
	strcpy(eroare, validate_oferta(oferta));

	if (strlen(eroare) > 0) {
		strcpy(srv_oferte->eroare, eroare);
		distruge_oferta(oferta);
		return srv_oferte;
	}

	if (gaseste_oferta(srv_oferte->repo_oferte, oferta)) {
		strcpy(srv_oferte->eroare, "oferta deja existenta!\n");
		distruge_oferta(oferta);
		return srv_oferte;
	}

	srv_oferte->repo_oferte = adauga_oferta(srv_oferte->repo_oferte, oferta);

	distruge_oferta(oferta);

	add_to_list(&srv_oferte->repo_history, repo_copy(srv_oferte->repo_oferte));
	return srv_oferte;
}

Service* srv_modifica_oferta(Service* srv_oferte, char* tip_vechi, char* adresa_veche, char* tip, int suprafata, char* adresa, int pret){
	/*
	* returneaza o entitate de service in urma modificarii ofertei vechi date prin tip si adresa
	* cu campurile unei alteia noi, eventual semnaland si o eroare
	* srv_oferte - service
	* tip_vechi - sir de caractere
	* adresa_veche - sir de caractere
	* tip - sir de caractere
	* suprafata - numar intreg
	* adresa - sir de caractere
	* pret - numar intreg
	*/
	Oferta* oferta_noua = creeaza_oferta(tip, suprafata, adresa, pret);
	Oferta* oferta_veche = creeaza_oferta(tip_vechi, 1, adresa_veche, 1);
	strcpy(srv_oferte->eroare, "Operatie efectuata cu succes.\n");

	char eroare[150] = "";
	strcat(eroare, validate_oferta(oferta_veche));
	strcat(eroare, validate_oferta(oferta_noua));
	if (strlen(eroare) > 0) {
		strcpy(srv_oferte->eroare, eroare);
		distruge_oferta(oferta_noua);
		distruge_oferta(oferta_veche);
		return srv_oferte;
	}

	if (gaseste_oferta(srv_oferte->repo_oferte, oferta_veche) == 0) {
		strcpy(srv_oferte->eroare, "oferta initiala este inexistenta!\n");
		distruge_oferta(oferta_noua);
		distruge_oferta(oferta_veche);
		return srv_oferte;
	}

	modificare_oferta(srv_oferte->repo_oferte, oferta_veche, oferta_noua);

	distruge_oferta(oferta_noua);
	distruge_oferta(oferta_veche);


	add_to_list(&srv_oferte->repo_history, repo_copy(srv_oferte->repo_oferte));
	return srv_oferte;
}

Service* srv_sterge_oferta(Service* srv_oferte, char* tip, char* adresa) {
	/*
	* returneaza o entitate de service in urma stergerii ofertei date prin tip si adresa,
	* eventual semnaland si o eroare 
	* srv_oferte - service
	* tip - sir de caractere
	* adresa - sir de caractere
	*/
	Oferta* oferta = creeaza_oferta(tip, 1, adresa, 1);
	strcpy(srv_oferte->eroare, "Operatie efectuata cu succes.\n");

	char eroare[100] = "";
	strcpy(eroare, validate_oferta(oferta));
	if (strlen(eroare) > 0) {
		strcpy(srv_oferte->eroare, eroare);
		distruge_oferta(oferta);
		return srv_oferte;
	}

	if (gaseste_oferta(srv_oferte->repo_oferte, oferta) == 0) {
		strcpy(srv_oferte->eroare, "oferta inexistenta!\n");
		distruge_oferta(oferta);
		return srv_oferte;
	}

	srv_oferte->repo_oferte = sterge_oferta(srv_oferte->repo_oferte, oferta);
	add_to_list(&srv_oferte->repo_history, repo_copy(srv_oferte->repo_oferte));
	distruge_oferta(oferta);

	return srv_oferte;
}

Service* srv_afisare_oferte(Service* srv_oferte) {
	/*
	* returneaza o entitate de VectorOferte ce contine lista de oferte si dimensiunea
	* srv_oferte - service
	*/
	strcpy(srv_oferte->eroare, "");

	srv_oferte->repo_oferte = get_all(srv_oferte->repo_oferte);
	if (srv_oferte->repo_oferte->dimensiune == 0) strcpy(srv_oferte->eroare, "nu exista oferte deocamdata.\n");

	return srv_oferte;
}

int cmp_f(Oferta* oferta1, Oferta* oferta2, char*cheie, char* criteriu) {
	/*
	* functie de comparatie, returneaza true daca doua oferte sunt intr-o relatie
	* printr-o anumita cheie
	* oferta1, oferta2 - Oferta*
	* cheie - sir de caractere ("pret", "tip")
	* criteriu - sir de caractere ("descrescator", "crescator")
	*/
	if (strcmp(cheie, "pret") == 0) 
		if (strcmp(criteriu, "crescator") == 0) return get_pret_oferta(oferta1) <= get_pret_oferta(oferta2);
		else return get_pret_oferta(oferta1) >= get_pret_oferta(oferta2);
	
	else {
		if (strcmp(criteriu, "crescator") == 0) return strcmp(get_tip_oferta(oferta1), get_tip_oferta(oferta2)) <= 0;
		return strcmp(get_tip_oferta(oferta1), get_tip_oferta(oferta2)) >= 0;
	}

}

VectorOferte* srv_sorteaza_oferte(Service* srv_oferte, char* cheie, char* criteriu) {
	/*
	* returneaza lista de oferte sortata dupa o cheie si un criteriu
	* cheie - sir de caractere 
	* criteriu - sir de caractere: crescator / descrescator
	*/
	if ((strcmp(cheie, "pret") == 0 || strcmp(cheie, "tip") == 0) && (strcmp(criteriu, "crescator") == 0 || strcmp(criteriu, "descrescator") == 0)) {
		return sorteaza (srv_oferte, cheie, criteriu, *cmp_f);
	}
	
	VectorOferte* Oferte;
	Oferte = (VectorOferte*)malloc(sizeof(VectorOferte));
	Oferte->size = -1;
	Oferte->oferte = NULL;
	return Oferte;
}


VectorOferte* srv_filtreaza_oferte(Service* srv_oferte, char* criteriu, char* criteriu_valoare, char* relatie, int valoare) {
	/*
	* returneaza o lista de oferte rezultata in urma filtrarii
	* srv_oferte - Service
	* criteriu - sir de caractere
	* criteriu_valoare - sir de caractere
	* relatie - sir de caractere
	* valoare - numar intreg: -1, 0, 1
	*/
	VectorOferte* Oferte;
	Oferte = (VectorOferte*)malloc(sizeof(VectorOferte));
	Oferte->size = 0;
	Oferte->oferte = (Oferta**)malloc(len(srv_oferte->repo_oferte) * sizeof(Oferta*));

	int rel = -1;

	if (strcmp(relatie, ">") == 0) rel = 1;

	for (int i = 0; i < len(srv_oferte->repo_oferte); ++i) {
		if (strcmp("adresa", criteriu) == 0) {  // Noua filtrare de adresa.
			if (strcmp(criteriu_valoare, get_adresa_oferta(srv_oferte->repo_oferte->oferte[i])) == 0)
				Oferte->oferte[Oferte->size++] = srv_oferte->repo_oferte->oferte[i];
		}
		else if (strcmp("tip", criteriu) == 0) {
			if (strcmp(criteriu_valoare, get_tip_oferta(srv_oferte->repo_oferte->oferte[i])) == 0)
				Oferte->oferte[Oferte->size++] = srv_oferte->repo_oferte->oferte[i];
		}
		else if (strcmp("suprafata", criteriu) == 0) {
			if ((get_suprafata_oferta(srv_oferte->repo_oferte->oferte[i]) - valoare) * rel > 0)
				Oferte->oferte[Oferte->size++] = srv_oferte->repo_oferte->oferte[i];
		}
		else {
			if ((get_pret_oferta(srv_oferte->repo_oferte->oferte[i]) - valoare) * rel > 0)
				Oferte->oferte[Oferte->size++] = srv_oferte->repo_oferte->oferte[i];
		}
	}

	return Oferte;
}

Service* sample_data(Service* srv){
	srv = srv_adauga_oferta(srv, "teren", 100, "Strada1", 1);
	srv = srv_adauga_oferta(srv, "teren", 90, "Strada2", 2);
	srv = srv_adauga_oferta(srv, "teren", 80, "Strada3", 4);

	srv = srv_adauga_oferta(srv, "casa", 70, "Strada1", 1);
	srv = srv_adauga_oferta(srv, "casa", 60, "Strada2", 2);
	srv = srv_adauga_oferta(srv, "casa", 50, "Strada3", 4);

	srv = srv_adauga_oferta(srv, "apartament", 40, "Strada1", 1);
	srv = srv_adauga_oferta(srv, "apartament", 30, "Strada2", 2);
	srv = srv_adauga_oferta(srv, "apartament", 20, "Strada3", 4);

	srv = srv_adauga_oferta(srv, "teren", 10, "Strada10", 2);
	return srv;
}

void service_undo(Service* srv){
	if (srv->repo_history.lungime > 1) {
		eliberare_repo(srv->repo_oferte);  // Eliberam repo curent
		pop_repo_list(&srv->repo_history);
		srv->repo_oferte = repo_copy(peek_date(&srv->repo_history));  // Setam repo curent la o copie a repo-ului din lista.
	}
}
