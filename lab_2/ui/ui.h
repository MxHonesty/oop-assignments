//
// Created by Stelian Stoian on 07/03/2021.
//

#ifndef LAB_2_UI_H
#define LAB_2_UI_H

#include "../service/service_payment.h"

/**
 * Main function of the ui.
 * Contine loop-ul de executie.
 */
void run();

/** Functie ui de adaugare. */
void ui_adaugare(service_payments* srv);

/** Functie ui de stergere */
void ui_stergere(service_payments* srv);

/** Functie ui de modificare */
void ui_modificare(service_payments* srv);

/** Functie ui de printare */
void ui_print_all(service_payments* srv);

/** Functie de citire int cu handle pentru eroare. Are limita de 15 caractere
 * @param text - textul de aratat inainte de cititre
 * @return Returneaza numarul citit. Daca exista o eroare, se returneaza 0.
 */
int citire_int(const char* text);

/**
 * Citeste datele pentru un payment.
 * @return un pointer la un array cu 4 elemente alocat dinamic care contine id, suma, zi, tip. Sau null daca eroare.
 */
int* citire_payment();

/**
 * Citeste datele pentru un payment mai putin id-ul.
 * @return un pointer la un array cu 4 elemente alocat dinamic care contine suma, zi, tip. Sau null daca eroare.
 */
int* citire_payment_fara_id();

/**
 * Citeste un sir de caractere care reprezinta tipul. Acesta este convertit in int-ul corespunzator.
 * @return Returneaza tipul daca sirul citit este coret, returneaza -1 daca nu este un sir valid.
 */
int citire_tip();

/**
 * Metoda de sortare in functie de suma. Determina daca utilzatorul doreste sa sorteze crescator sau descrescator.
 */
void ui_sortare_suma(service_payments *srv);

/**
 * Metoda de sortarei n functie de tip. Determina daca utilizatorul doreste sa sorteze crescator sau descrescator.
 */
void ui_sortare_tip(service_payments *srv);

/**
 * Functie de ui pentru functionalitatea de filtrare a unui element dupa valoare.
 * @param srv
 */
void ui_filtrare_element(service_payments* srv);

/**
 * Functia de ui pentru functionalitatea de filtrare a unui element dupa tip.
 * @param srv
 */
void ui_filtrare_tip(service_payments* srv);


#endif //LAB_2_UI_H
