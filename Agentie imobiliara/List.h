#pragma once


typedef struct {
	void** list;
	int capacitate;  // Lungimea maxima
	int lungime;  // Lungimea curenta
}List;

/** Constructor al listei.
* Initializeza o lista de lungime 0.
* @return o noua lista.
*/
List create_list();

/** Destructor al listei.
* Elibereaza tot spatiul alocat.
* @param de_distrus - lista pe care dorim sa o eliberam.
*/
void destroy_list(List de_distrus);


/** Elibereaza o lista care contine repo-uri 
	@param de_distrus - nodul dorit
*/
void destroy_repo_list(List de_distrus);

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
*/
void pop_list(List* lista); // TODO

/** Elimina ultimul repo din lista. Daca lista are mai putin de 2
*	elemente atunci nu se modifica nimic.
	@param lista - lista din care dorim sa eliminam elementul.
*/
void pop_repo_list(List* lista);

/** Functie redimensionare */
void redim_lista(List* la_lista);

void add_repo_to_list(List* lista, void* data);

void redim_repo_lista(List* la_lista);