#pragma once

#include "oferta.h"

typedef void (*Destructor)(Oferta* o);
typedef int (*Comparatie)(Oferta* o, Oferta* b);

typedef struct {
	void** list;
	int capacitate;  // Lungimea maxima
	int lungime;  // Lungimea curenta
}List;

/** Constructor al listei.
* Initializeza o lista de lungime 0.
* @return pointer la o noua lista.
*/
List* create_list();

/** Returneaza dimensiunea listei date */
int dim(List* lista);

/** Destructor al listei.
* Elibereaza tot spatiul alocat.
* @param de_distrus - lista pe care dorim sa o eliberam.
* @param des - destructor de apelat asupra elementelor.
*/
void destroy_list(List* de_distrus, Destructor des);

/** Adauga date la finalul listei.
* @param lista - pointer la lista in care dorim sa adaugam.
* @param data - pointer la datele alocate dinamic pe 
* care dorim sa le introducem in lista.
*/
void add_to_list(List* lista, void* data);

/** Returneaza un pointer la datele din urma listei
* @param lista - lista din care dorim ultimul element.
* @return pointer la ultimul element din lista.
* Daca lista este goala, retunreaza NULL.
*/
void* peek_date(List* lista);

/** Elimina ultimul element din lista. Daca lista este goala, nu se modifica nimic.
* @param lista - lista din care dorim sa eleiminam ultimul element.
* @param des - destructor functie de apelat asupra elementului din lista.
*/
void pop_list(List* lista, Destructor des);

/** Elimina ultimul repo din lista. Daca lista are mai putin de 2
*	elemente atunci nu se modifica nimic.
	@param lista - lista din care dorim sa eliminam elementul.
*/

/** Functie redimensionare */
void redim_lista(List* la_lista);

/** Determina pozitia elementului de la adresa data este in lista 
*	@param lista - lista de elmente
*	@param date - pointer la date
*	@return pozitia elementului in reprezentarea listei sau -1 daca nu a fost gasit.
*/
int search_element(List* lista, void* date, Comparatie comp);

/** Determina daca elementul este in lista
*	@return true daca este, false daca nu.
*/
int is_in_list(List* lista, void* date);

/** Sterge elementul dat prin pointer din lista.
* @param lista - pointer la lista
* @param date - pointer la datele de sters
* @param des - destructor dorit asupra obiectului gasit.
*/
void delete_from_list(List* lista, void* date, Destructor des);

/** Sterge elementul de pe pozitia data din lista 
*	@param lista - pointer la lista 
*	@param index - indexul elementului din lista.
*	@param des - destructor
*/
void delete_by_index(List* lista, int index, Destructor des);

/** Destructor pentru lista de liste */
void destroy_list_de_liste(List* lista);

/** Elimina ultimul element din lista de liste */
void pop_lista_liste(List* lista);

/** Creeaza o copie a listei date 
*	Se creeaza o copie a listei chiar daca este goala. Trebuie dealocat.
*/
List* copy_list(List* lista_de_copiat);

/** Inlocuieste un element dat.
*	@param lista - lista in care inlocuim
*	@param inlocuit - elementul pe care il inlocuim.
*	@param nou - noul element
*	@param des - destructorul elementului
*/
void modificare_element(List* lista, void* inlocuit, void* nou, Destructor des);