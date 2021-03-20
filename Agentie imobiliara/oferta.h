#pragma once

/*
* reprezentarea entitatii Oferta (campuri)
*/
typedef struct {
	char* tip, *adresa;
	int suprafata, pret;
}Oferta;

/*
* reprezentarea entitatii VectorOferte
* size - dimensiune (nr intreg)
* oferte - vector dinamic de oferte
*/
typedef struct {
	int size;
	Oferta** oferte;
}VectorOferte;


/*
creeaza o entitate de Oferta
*/
Oferta* creeaza_oferta(char*, int, char*, int);

/*
returneaza tipul unei oferte
return - pointer la char
*/
char* get_tip_oferta(Oferta*);

/*
returneaza suprafata unei oferte
return - numar intreg
*/
int get_suprafata_oferta(Oferta*);

/*
returneaza adresa unei oferte
return - pointer la char
*/
char* get_adresa_oferta(Oferta*);

/*
returneaza pretul unei oferte
return - numar intreg
*/
int get_pret_oferta(Oferta*);

/*
seteaza tipul unei oferte (pointer la char)
*/
void set_tip_oferta(Oferta*, char*);

/*
seteaza suprafata unei oferte (numar intreg)
*/
void set_suprafata_oferta(Oferta*, int);

/*
seteaza adresa unei oferte (pointer la char)
*/
void set_adresa_oferta(Oferta*, char*);

/*
seteaza pretul unei oferte (numar intreg)
*/
void set_pret_oferta(Oferta*, int);

/*
elibereaza memoria ocupata de o entitate
*/
void distruge_oferta(Oferta*);

/*
returneaza true daca cele doua oferte sunt echivalente,
false in caz contrar
*/
int equals_oferta(Oferta*, Oferta*);
