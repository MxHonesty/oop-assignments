#pragma once
#include "oferta.h"

/*
* returneaza un sir vid daca oferta este valida,
* un sir de mesaje in caz contrar
*/
char* validate_oferta(Oferta*);

/*
* returneaza true (!= 0) daca un sir de caractere
* reprezinta un criteriu valid
*/
int validate_criteriu(char*);



