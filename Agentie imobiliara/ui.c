#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "service.h"
#include "oferta.h"
#include "validator.h"

Service* ui_adaugare_oferta(Service* srv_oferte) {
	/*
	* functie ui de adaugare a unei oferte
	* returneaza o entitate service - repo-ul actualizat + mesajul redat in urma operatiei
	* srv_oferte - service
	*/
	int e1, e2, e3, e4;
	char tip[50], adresa[50], leftovers[50] = "";
	float suprafata = 0, pret = 0;

	printf("   introduceti datele ofertei de adaugat.\n");

	printf("   tipul ofertei: ");
	e1 = scanf("%s", tip);
	if (e1 == 0) strcpy(tip, "");
	printf("   adresa: ");
	e2 = scanf("\n%[^\n]", adresa);
	if (e2 == 0) strcpy(adresa, "");
	printf("   suprafata: ");
	e3 = scanf("%f", &suprafata);
	if (e3 == 0) suprafata = -1, scanf("%s", leftovers);
	printf("   pretul: ");
	e4 = scanf("%f", &pret);
	if (e4 == 0) pret = -1, scanf("%s", leftovers);

	srv_oferte = srv_adauga_oferta(srv_oferte, tip, (int)suprafata, adresa, (int)pret);

	printf(srv_oferte->eroare);
	return srv_oferte;
}

Service* ui_actualizare_oferta(Service* srv_oferte) {
	/*
	* functie ui de modificare a unei oferte
	* returneaza o entitate service - repo-ul actualizat + mesajul redat in urma operatiei
	* srv_oferte - service
	*/
	int e1, e2, e3, e4;
	char tip_vechi[20], adresa_veche[50], leftovers[50], tip[50], adresa[50];
	float suprafata = 0, pret = 0;

	printf("   introduceti datele ofertei de modificat.\n");
	printf("   tipul ofertei: ");
	e1 = scanf("%s", tip_vechi);
	if (e1 == 0) strcpy(tip_vechi, "");
	printf("   adresa: ");
	e2 = scanf("\n%[^\n]", adresa_veche);
	if (e2 == 0) strcpy(adresa_veche, "");

	printf("   Introduceti datele ofertei actualizate.\n");

	printf("   tipul ofertei: ");
	e1 = scanf("%s", tip);
	if (e1 == 0) strcpy(tip, "");
	printf("   adresa: ");
	e2 = scanf("\n%[^\n]", adresa);
	if (e2 == 0) strcpy(adresa, "");
	printf("   suprafata: ");
	e3 = scanf("%f", &suprafata);
	if (e3 == 0) suprafata = -1, scanf("%s", leftovers);
	printf("   pretul: ");
	e4 = scanf("%f", &pret);
	if (e4 == 0) pret = -1, scanf("%s", leftovers);

	srv_oferte = srv_modifica_oferta(srv_oferte, tip_vechi, adresa_veche, tip, (int)suprafata, adresa, (int)pret);

	printf(srv_oferte->eroare);

	return srv_oferte;
}

Service* ui_stergere_oferta(Service* srv_oferte) {
	/*
	* functie ui de stergere a unei oferte
	* returneaza o entitate service - repo-ul actualizat + mesajul redat in urma operatiei
	* srv_oferte - service
	*/
	int e1, e2;
	char tip[50] = "", adresa[50] = "";

	printf("   Introduceti datele ofertei de sters.\n");
	printf("   tipul ofertei: ");
	e1 = scanf("%s", tip);
	if (e1 == 0) strcpy(tip, "");
	printf("   adresa: ");
	e2 = scanf("\n%[^\n]", adresa);
	if (e2 == 0) strcpy(adresa, "");

	srv_oferte = srv_sterge_oferta(srv_oferte, tip, adresa);

	printf(srv_oferte->eroare);

	return srv_oferte;
}

void ui_vizualizare_oferte(Service* srv_oferte) {
	/*
	* functie ui de vizualizarea ofertelor sortate
	* srv_oferte - Service
	*/
	printf("Introduceti criteriile dupa care doriti sa ordonati ofertele:\n");
	char cheie[50], criteriu[50];
	printf("Campul (tip / pret): ");
	scanf("\n%[^\n]", cheie);
	printf("Criteriu (crescator / descrescator): ");
	scanf("\n%[^\n]", criteriu);

	VectorOferte* oferte_sortate = srv_sorteaza_oferte(srv_oferte, cheie, criteriu);

	printf("\n");

	if (oferte_sortate->size == -1) printf("Criteriile introduse sunt incorecte!\n");
	else {
		if (oferte_sortate->size == 0) printf("Nu exista oferte deocamdata.\n");
		else {
			for (int i = 0; i < oferte_sortate->size; ++i)
				printf("tip: %s | suprafata: %d | adresa: %s | pret: %d\n", get_tip_oferta(oferte_sortate->oferte[i]),
					get_suprafata_oferta(oferte_sortate->oferte[i]), get_adresa_oferta(oferte_sortate->oferte[i]), get_pret_oferta(oferte_sortate->oferte[i]));
		}
	}

	free(oferte_sortate->oferte);
	free(oferte_sortate);
}

void ui_filtrare_oferte(Service* srv_oferte) {
	/*
	* functie ui de vizualizare a ofertelor sortate
	* srv_oferte - Service
	*/
	VectorOferte* oferte_filtrate = NULL;

	char criteriu[50], rel[50], eroare[100] = "", valoare_tip[50], valoare_adresa[150];
	float valoare;

	printf("Introduceti criteriul dupa care se va filtra lista (suprafata / tip / pret / adresa)\n");
	printf("Criteriu: ");
	scanf("\n%[^\n]", criteriu);

	if (validate_criteriu(criteriu) == 0)
		printf("Criteriul introdus nu este valid.\n");
	else {
		if (strcmp(criteriu, "tip") == 0) {
			printf("Valoare de comparatie (teren / casa / apartament): ");
			scanf("\n%[^\n]", valoare_tip);
			oferte_filtrate = srv_filtreaza_oferte(srv_oferte, criteriu, valoare_tip, "", 0);
		}
		else if (strcmp(criteriu, "adresa") == 0) {
			printf("Adresa de comparatie: ");
			scanf("\n%[^\n]", valoare_adresa);
			oferte_filtrate = srv_filtreaza_oferte(srv_oferte, criteriu, valoare_adresa, "", 0);
		}
		else {
			printf("Relatia de filtrare( < , >): ");
			scanf("\n%[^\n]", rel);
			if (strcmp("<", rel) != 0 && strcmp(">", rel) != 0) strcat(eroare, "Relatia de comaparatie este invalida!\n");

			printf("Valoare de comparatie: ");
			int e1 = scanf("%f", &valoare);
			if (e1 == 0) strcat(eroare, "Valoarea trebuie sa fie un numar!\n");

			if (strlen(eroare) == 0) oferte_filtrate = srv_filtreaza_oferte(srv_oferte, criteriu, "", rel, (int)valoare);
		}
		if (strlen(eroare)) printf(eroare);
		else {
			if (oferte_filtrate->size == 0) printf("Nu s-au gasit oferte care corespund.\n");
			else {
				for (int i = 0; i < oferte_filtrate->size; ++i)
					printf("tip: %s | suprafata: %d | adresa: %s | pret: %d\n", get_tip_oferta(oferte_filtrate->oferte[i]),
						get_suprafata_oferta(oferte_filtrate->oferte[i]), get_adresa_oferta(oferte_filtrate->oferte[i]), get_pret_oferta(oferte_filtrate->oferte[i]));
				//free(oferte_filtrate->oferte);
				//free(oferte_filtrate);
			}
		}
		if (oferte_filtrate != NULL)
		{
			if (oferte_filtrate->oferte != NULL)
				free(oferte_filtrate->oferte);
			free(oferte_filtrate);
		}
	}
}

void ui_afisare_oferte(Service* srv_oferte) {
	/*
	* functie de afisare a tuturor ofertelor
	* srv_oferte - service
	*/
	Service* lista_oferte = srv_afisare_oferte(srv_oferte);

	printf(lista_oferte->eroare);

	for (int i = 0; i < lista_oferte->repo_oferte->dimensiune; ++i)
		printf("tip: %s | suprafata: %d | adresa: %s | pret: %d\n", get_tip_oferta(lista_oferte->repo_oferte->oferte[i]),
			get_suprafata_oferta(lista_oferte->repo_oferte->oferte[i]), get_adresa_oferta(lista_oferte->repo_oferte->oferte[i]), get_pret_oferta(lista_oferte->repo_oferte->oferte[i]));
}

/** Functia de ui pentru functionalitatea de undo.
	@param srv - service in care dorim sa efectuam undo.
*/
void ui_undo(Service* srv) {
	service_undo(srv);
}

void afisare_comenzi() {
	/*
	* afiseaza comenzile posibile din meniu
	*/
	printf("\nComenzi posibile:\n");
	printf("   adauga    - adaugarea unei oferte noi\n");
	printf("   sterge    - stergerea unei oferte existente\n");
	printf("   update    - actualizarea unei oferte existente\n");
	printf("   sorteaza  - vizualizarea ofertelor ordonate dupa o categorie\n");
	printf("   filtreaza - filtrarea ofertelor dupa un criteriu\n");
	printf("   afiseaza  - afisarea tuturor ofertelor\n");
	printf("   undo      - anuleaza ultima modificare\n");
	printf("   exit      - iesirea din aplicatie\n");
}

void run(Service* srv_oferte) {
	/*
	* functia run responsabila de rularea interfatei ui
	* srv_oferte - service
	*/
	char cmd[10];

	while (1) {
		afisare_comenzi();
		printf("\n>>> ");
		scanf("%s", &cmd);

		if (strcmp(cmd, "exit") == 0) break;
		else if (strcmp(cmd, "adauga") == 0) srv_oferte = ui_adaugare_oferta(srv_oferte);
		else if (strcmp(cmd, "update") == 0) srv_oferte = ui_actualizare_oferta(srv_oferte);
		else if (strcmp(cmd, "sorteaza") == 0) ui_vizualizare_oferte(srv_oferte);
		else if (strcmp(cmd, "filtreaza") == 0) ui_filtrare_oferte(srv_oferte);
		else if (strcmp(cmd, "afiseaza") == 0) ui_afisare_oferte(srv_oferte);
		else if (strcmp(cmd, "sterge") == 0) srv_oferte = ui_stergere_oferta(srv_oferte);
		else if (strcmp(cmd, "undo") == 0) ui_undo(srv_oferte);
		else printf("comanda invalida!\n");
	}

	distruge_service(srv_oferte);
}
