#pragma once

#include "oferta.h"

/*
* reprezentarea entitatii Repository
* oferte - sir de referinte la entitati de tip Oferta
* dimensiune - numar intreg
* capacitate - numar intreg
*/
typedef struct {
	Oferta** oferte;
	int dimensiune;
	int capacitate;
}Repository;

/*
* returneaza numarul de elemente din repo
*/
int len(Repository*);

/*
* returneaza repository-ul in urma modificarii capacitatii de memorare
*/
Repository* redimensionare_repo(Repository*, int);

/*
* returneaza o entitate creata de tip Repository
*/
Repository* creeaza_repo();

/*
* returneaza repository-ul in urma adaugarii unei oferte
*/
Repository* adauga_oferta(Repository*, Oferta*);

/*
* returneaza repository-ul in urma stergerii unei oferte
*/
Repository* sterge_oferta(Repository*, Oferta*);

/*
* modifica o oferta existenta din repository
*/
void modificare_oferta(Repository*, Oferta*, Oferta*);

/*
* returneaza elementele unui repository
*/
Repository* get_all(Repository*);

/*
* returneaza true daca o oferta se afla in repo
*/
int gaseste_oferta(Repository*, Oferta*);

/*
* elibereaza memoria ocupata de un repository
*/
void eliberare_repo(Repository* repo);

/** Creeaza un deep copy a repository-ului curent
	@param de_copiat - pointer la repo de copiat
	@return pointer la deep copy a repo
*/
Repository* repo_copy(Repository* de_copiat);

