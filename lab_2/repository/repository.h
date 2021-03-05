//
// Created by Stelian Stoian on 05/03/2021.
//

#ifndef LAB_2_REPOSITORY_H
#define LAB_2_REPOSITORY_H

#include "../domain/payment.h"
#include <stdlib.h>

/**
 * Structura care este responsabila pentru stocarea paymenturilor.
 * Contine un pointer la un array de paymenturi si marimea acestuia.
 * <li> <b>payments</b> - pointer catre array alocat dinamic de payment </li>
 * <li> <b>maxim_curent</b> - urmoatoare pozitie pe care se poate scrie in array. </li>
 * <li> <b>marime</b> - marimea curenta a array-ului </li> <br>
 * Pastreaza in maxim_curent urmatoarea pozitie pe care se poate scrie.
 * Acest array isi modifica marimea dinamic.
 */
typedef struct {
    payment* payments;
    int maxim_curent;
    int marime;
}repository_payment;

/**
 * Creeaza si returneaza un repository_payment
 * @return Un repository initializat cu NUMAR_ELEMENTE_INITIALE pozitii.
 */
repository_payment create_repository_payment();

/**
 * Elibereaza memoria ocupata de array-ul de payment-uri
 * @param repo_de_dealocat - repository-ul pe care dorim sa il eliberam.
 */
void destroy_repository_payment(repository_payment repo_de_dealocat);

/**
 * Adauga un payment in repository.
 * <h2>!!! se aduaga o copie a paymentului NU O REFERINTA !!!</h2>
 * @param repo - repository-ul in care dorim sa adaugam.
 * @param de_adaugat - paymentul pe care dorim sa il adaugam.
 *
 * TODO: De adaugat mecanism de redimensionare array dinamic cand se depaseste marimea data.
 */
void add_payment(repository_payment* repo, payment de_copiat);

/**
 * Cauta si returneaza un pointer la paymentul identificat prin id-ul dat.
 * @param repo - repository-ul in care se doreste efectuata cautarea.
 * @param id_cautat - id-ul pe care il cautam.
 * @return pointer la paymentul gasit. <b> In cazul in care paymentul cu acest id
 * nu este gasit se returneaza pointer null. </b>
 */
payment* search_payment(repository_payment repo, int id_cautat);

/**
 * Inlocuieste elementul de id id_updatat cu <b>o copie</b> a new_payment
 * @param repo - repository in care dorim sa executam modificarea
 * @param id_updatat - id-ul elementului pe care dorim sa il updatam
 * @param new_payment - noul payment de aduagat.
 */
void update_payment(repository_payment repo, int id_updatat, payment new_payment);

/**
 * Elimina elementul cu id dat din repository.
 * @param repo - repository din care dorim sa stergem
 * @param id_removed - id-ul elementului pe care dorim sa il stergem.
 */
void remove_payment(repository_payment* repo, int id_removed);

#endif //LAB_2_REPOSITORY_H
