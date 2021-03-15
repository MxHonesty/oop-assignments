//
// Created by Stelian Stoian on 07/03/2021.
//

#ifndef LAB_2_SERVICE_PAYMENT_H
#define LAB_2_SERVICE_PAYMENT_H

#include "../repository/repository.h"
#include "../domain/payment.h"

/**
 * Structura unui service.
 * Contine un repo.
 */
typedef struct {
    repository_payment repo;
}service_payments;

/**
 * Initializeaza service-ul.
 * @param service - pointer la service.
 */
void construct_service(service_payments* service);

/**
 * Distruge service-ul
 * @param service - pointer la service.
 */
void destroy_service(service_payments* service);

/**
 * Serviciu de adaugare unui payment in repository.
 * @param service - service-ul in care dorim sa efectuam operatia
 * @param id - id-ul paymentului
 * @param suma - suma paymentului
 * @param zi - ziua paymentului
 * @param tip - tipul paymentului
 * @return <li>Returneaza 0 daca adaugarea a fost efectuata cu succes.</li>
 */
int adaugare_payment(service_payments* service, int id, int suma, int zi, int tip);

/**
 * Functia de adaugare payment pentru utilizator. Genereaza automat id-uri.
 * @param service
 * @param suma
 * @param zi
 * @param tip
 * @return <li>Returneaza 0 daca adaugarea a fost efectuata cu succes.</li>
 */
int adaugare_payment_user(service_payments* service, int suma, int zi, int tip);

/**
 * Serviciu de stergere a unui payment din repository.
 * @param service - serviciul in care dorim sa efectuam operatia.
 * @param id - id-ul elementului eliminat
 * @return <li>Returneaza 0 daca eliminarea s-a executat cu succes.</li>
 * <li>Returneaza 1 daca nu a fost gasit elementul.</li>
 */
int stergere_payment(service_payments* service, int id);

/**
 * Modifica paymentul identificat prin id dat.
 * @param service - service-ul in care dorim sa executam operatia.
 * @param id - id-ul paymentului pe care dorim sa il modificam.
 * @param new_id - noul id
 * @param new_suma - noua suma
 * @param new_zi - noua zi
 * @param new_tip - noul tip
 * @return <li>Returneaza 0 daca modificarea a fost executata cu succes.</li>
 * <li>Returneaza 1 daca elementul cu id dat nu a fost gasit. </li>
 */
int modificare_payment(service_payments* service, int id, int new_id, int new_suma, int new_zi, int new_tip);

/**
* Sorteaza elementele dupa un criteriu dat ca functie.
* @param criteriu - functia cheie
* @param service service pe care dorim sa sortam.
* @return o copie a listei din service sortata
*/
payment* sortare_generala(service_payments* service, int(*criteriu)(payment), int crescator);

/**
 * Returneaza o lista de payment sortata dupa suma.
 * @param service - serviciul in care efectuam operatia
 * @param crescator - 1 daca sortarea se face crescator, 0 daca se face descrescator
 * @return returneaza o lista responsabilitatea de delocare cade asupra apelantului.
 */
payment* sortare_suma(service_payments* service, int crescator);

/**
 * Returneaza o lista de payment sortata dupa suma.
 * @param service - serviciul in care efectuam operatia
 * @param creascator - 1 daca vrem sortare crescatoare, 0 daca vrem descrescatoare.
 * @return returneaza un pointer la o lista de elemenente. Responsabilitatea de eliberarea a memorie cade asupra
 * apelantului.
 */
payment* sortare_tip(service_payments* service, int creascator);

/**
 * Vector de payment utilizat pentru operatia de filtru.
 * Pastreaza o lista de paymenturi alocata dinamic si o marime.
 */
typedef struct{
    payment* list;
    int marime;
}Vector;

/**
 * Filtreaza elementele din serviciul curent astfel incat sa ramana doar cele care apartin intervalului dat.
 * @param service - serviciul curent
 * @param inceput - valoarea de la care incepem
 * @param final - cea mai mare valoare admisa
 * @param tip_filtrare <li> 1 - Filtrare suma </li> <li>2 - Filtrare zi </li> <li>3 - Filtrare tip </li>
 * @return Vector - contine un pointer la lista si marimea ei <h1> Pointerul trebuie dealocat </h1
 */
Vector filtrare_elemente(service_payments* service, int inceput, int final, int tip_filtrare);

/**
 * Filtrare speciala pentru tip.
 * @param service
 * @param filtru - sir de caractere dat.
 * @return Vector pointer si lungime. <h1> Pointerul trebuie dealocat </h1
 */
Vector filtrare_elemente_tip_string(service_payments* service, char* filtru);

#endif //LAB_2_SERVICE_PAYMENT_H
