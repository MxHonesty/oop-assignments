#pragma once

#include <stdlib.h>
#include "List.h"

/*
* reprezentarea entitatii de service
* repo_oferte - respository* (Oferte)
* repo_history - lista de undo
* eroare - sir de caractere (mesaj sugestiv in urma operatiei)
*/
typedef struct{
	List* repo_history;  // Lista de lista (stari ale elems).
	List* elems;  // Lista elemente curente.
	char eroare[150];
}Service;
// TODO: De renuntat la REPO. Rescriem service astfel incat sa folosim lista.
// TODO: De rescris lista pentru abstractizare.

/*
* returneaza o entitate noua de tip Service*
* repo - Repository*
*/
Service* creeaza_service();  // MOD

/** Elibereaza toata memoria aferenta service-ului */
void distruge_service(Service* de_sters);

/*
* adauga o oferta data prin campurile sale la repo
* in urma validarii
* returneaza o entitate service (actualizata)
* @param srv_oferte - service
* @param tip - sir de caractere
* @param suprafata - numar intreg
* @param adresa - sir de caractere
* @param pret - numar intreg
*/
Service* srv_adauga_oferta(Service*, char* , int , char* , int);

/*
* modifica o oferta data prin campurile sale vechi de identificare(tip, adresa) din repo
* in urma validarii
* returneaza o entitate service (actualizata)
*/
Service* srv_modifica_oferta(Service*,char*, char*, char*, int, char*, int);

/*
* sterge o oferta data prin campurile sale de identificare(tip, adresa) la repo
* in urma validarii
* returneaza o entitate service (actualizata)
*/
Service* srv_sterge_oferta(Service*,char*, char*);

/*
* returneaza pointer la Service ce contine lista de oferte
* si un mesaj efect al operatiei
*/
Service* srv_afisare_oferte(Service*);

/*
* returneaza o entitate de VectorOferte continand lista de oferte
* rezultata si dimensiunea sa
*/
VectorOferte* srv_sorteaza_oferte(Service*, char*, char*);

/*
* returneaza o entitate de VectorOferte continand lista de oferte
* rezultata si dimensiunea sa
*/
VectorOferte* srv_filtreaza_oferte(Service*, char*, char*, char*, int);

/*
* Genereaza un sample de nr date noi
* @param nr - numarul de entry-uri noi.
*/
Service* sample_data(Service* srv);

/** Executa functionalitatea de undo la nivel de service.
	@param srv - service in care dorim sa executam operatia.
*/
void service_undo(Service* srv);