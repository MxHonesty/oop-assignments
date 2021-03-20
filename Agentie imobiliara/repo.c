#include "repo.h"

#include <stdlib.h>
#include <stdio.h>

Repository* creeaza_repo() {
	/*
	* returneaza o entitate noua de tip Repository*
	*/
	Repository* repo = (Repository*)malloc(sizeof(Repository));
	repo->capacitate = 0;
	repo->dimensiune = 0;
	repo->oferte = NULL;
	return repo;
}

Repository* redimensionare_repo(Repository* repo, int capacitate) {
	/*
	* returneaza o entitate de tip Repository* cu o capacitate data
	* repo - Repository*
	* capacitate - numar intreg
	*/
	Oferta** copie_oferte;

	copie_oferte = (Oferta**)malloc(capacitate * sizeof(Oferta*));

	if (copie_oferte == NULL) return repo;

	for (int i = 0; i < repo->dimensiune; ++i) {
		copie_oferte[i] = creeaza_oferta(get_tip_oferta(repo->oferte[i]), get_suprafata_oferta(repo->oferte[i]),
			get_adresa_oferta(repo->oferte[i]), get_pret_oferta(repo->oferte[i]));;
	}
	int dim = repo->dimensiune;

	eliberare_repo(repo);
	repo = creeaza_repo();
	repo->oferte = copie_oferte;
	repo->capacitate = capacitate;
	repo->dimensiune = dim;

	return repo;
}

Repository* adauga_oferta(Repository* repo, Oferta* oferta_noua) {
	/*
	* returneaza pointer la primul element din repo in urma adaugarii unei oferte
	* repo - repository*
	* oferta_noua - Oferta*
	*/
	Oferta* oferta = creeaza_oferta(get_tip_oferta(oferta_noua), get_suprafata_oferta(oferta_noua),
		get_adresa_oferta(oferta_noua), get_pret_oferta(oferta_noua));

	if (repo->dimensiune < repo->capacitate) {
		repo->oferte[repo->dimensiune++] = oferta;
	}
	else {
		if (repo->capacitate == 0) repo = redimensionare_repo(repo, 1);
		else repo = redimensionare_repo(repo, 2 * repo->capacitate);
		repo->oferte[repo->dimensiune++] = oferta;
	}
	
	return repo;
}

Repository* sterge_oferta(Repository* repo, Oferta* oferta) {
	/*
	* returneaza pointer la primul element in urma stergerii unei oferte
	* repo - reopsitory*
	* oferta - Oferta*, existenta deja in repo
	*/

	for (int i=0; i < repo->dimensiune; ++i)
		if (equals_oferta(repo->oferte[i], oferta)) {
			for (int j = i; j < repo->dimensiune - 1; ++j) {
				set_tip_oferta(repo->oferte[j], get_tip_oferta(repo->oferte[j+1]));
				set_adresa_oferta(repo->oferte[j], get_adresa_oferta(repo->oferte[j + 1]));
				set_suprafata_oferta(repo->oferte[j], get_suprafata_oferta(repo->oferte[j + 1]));
				set_pret_oferta(repo->oferte[j], get_pret_oferta(repo->oferte[j + 1]));
			}
			repo->dimensiune--;
			distruge_oferta(repo->oferte[repo->dimensiune]);
			break;
		}

	
	return repo;
	
}

Repository* get_all(Repository* repo) {
	/*
	* returneaza o entitate de tip VectorOferte (sir de oferte)(nr de elemente + elemente)
	* repo - repository*
	*/
	return repo;
}

void modificare_oferta(Repository* repo, Oferta* oferta_veche, Oferta* oferta_noua) {
	/*
	* actualizeaza in memorie campurile unei oferte existente 
	* repo - repository*
	* oferta_veche - Oferta*
	* oferta_noua - Oferta*
	*/
	for (int i = 0; i < repo->dimensiune; ++i) {
		if (equals_oferta(repo->oferte[i], oferta_veche)) {
			set_tip_oferta(repo->oferte[i], get_tip_oferta(oferta_noua));
			set_adresa_oferta(repo->oferte[i], get_adresa_oferta(oferta_noua));
			set_suprafata_oferta(repo->oferte[i], get_suprafata_oferta(oferta_noua));
			set_pret_oferta(repo->oferte[i], get_pret_oferta(oferta_noua));
			break;
		}
	}
}

void eliberare_repo(Repository* repo) {
	/*
	* elibereaza memoria ocupata de un repository dat
	* repo - repository*
	*/
	for (int i = 0; i < repo->dimensiune; ++i) {
		distruge_oferta(repo->oferte[i]);
	}
	free(repo->oferte);
	free(repo);
}

Repository* repo_copy(Repository* de_copiat){
	Repository* new_repo = malloc(sizeof(Repository));
	new_repo->dimensiune = de_copiat->dimensiune;
	new_repo->capacitate = de_copiat->capacitate;
	new_repo->oferte = malloc(new_repo->capacitate * sizeof(Oferta*));
	for (int i = 0; i < new_repo->dimensiune; i++) {
		Oferta* old_oferta = de_copiat->oferte[i];
		Oferta* new_oferta = creeaza_oferta(old_oferta->tip, old_oferta->suprafata, old_oferta->adresa, old_oferta->pret);
		new_repo->oferte[i] = new_oferta;
	}

	return new_repo;
}

int gaseste_oferta(Repository* repo, Oferta* oferta) {
	/*
	* returneaza true(!=0) daca o oferta data se gaseste in repo,
	* false in caz contrar
	* repo - repository*
	* oferta - Oferta*
	*/
	for (int i = 0; i < repo->dimensiune; ++i) {
		if (equals_oferta(oferta, repo->oferte[i])) return 1;
	}

	return 0;
}

int len(Repository* repo) {
	/*
	* returneaza numarul de oferte din repo (nr intreg)
	* repo - repository*
	*/
	return repo->dimensiune;
}