//
// Created by Stelian Stoian on 05/03/2021.
//

#include "test_repository.h"
#include <assert.h>

/**
 * Testeaza functionalitatea de adaugare din repository
 */
void test_repository() {
    // Am creat un element, adagat, sters, si adaugat un nou element
    repository_payment repo = create_repository_payment();
    payment de_adaugat = create_payment(1, 100, 27, TIP_MANCARE);
    add_payment(&repo, de_adaugat);
    assert(payment_equals(repo.payments[0], de_adaugat));

    remove_payment(&repo, 1);
    payment new_payment = create_payment(1, 200, 1, TIP_ALTELE);
    add_payment(&repo, new_payment);
    assert(payment_equals(repo.payments[0], new_payment));

    destroy_repository_payment(repo);
}

/**
 * Testeaza eliminarea din repository.
 */
void test_remove(){
    repository_payment repo = create_repository_payment();
    add_payment(&repo, create_payment(1, 200, 1, TIP_IMBRACAMINTE));
    add_payment(&repo, create_payment(2, 200, 20, TIP_ALTELE));
    remove_payment(&repo, 1);
    assert(payment_equals(repo.payments[0], create_payment(2, 200, 20, TIP_ALTELE)));

    destroy_repository_payment(repo);
}

/**
 * Testeaza functionalitatea de cautare a unui payment in repo.
 */
void test_search(){
    repository_payment repo = create_repository_payment();
    add_payment(&repo, create_payment(2, 100, 2, TIP_ALTELE));
    add_payment(&repo, create_payment(1, 200, 2, TIP_TELEFON_INTERNET));
    payment* ptr = search_payment(repo, 1);
    assert(payment_equals(*ptr, create_payment(1, 200, 2, TIP_TELEFON_INTERNET)));
    assert(payment_equals(*search_payment(repo, 2), create_payment(2, 100, 2, TIP_ALTELE)));

    destroy_repository_payment(repo);
}

/**
 * Testeaza functionalitatea de update.
 */
void test_update(){
    repository_payment repo = create_repository_payment();
    add_payment(&repo, create_payment(1, 200, 1, TIP_IMBRACAMINTE));
    update_payment(repo, 1, create_payment(2, 1, 3, TIP_TELEFON_INTERNET));

    assert(payment_equals(*search_payment(repo, 2), create_payment(2, 1, 3, TIP_TELEFON_INTERNET)));
    assert(!payment_equals(*search_payment(repo, 2), create_payment(1, 200, 1, TIP_IMBRACAMINTE)));

    destroy_repository_payment(repo);
}

/**
 * Testeaza functionalitatea functiei de apartententa la repo.
 */
void test_este_inclus(){
    repository_payment repo = create_repository_payment();
    add_payment(&repo, create_payment(1, 100, 1, TIP_TRANSPORT));
    add_payment(&repo, create_payment(10, 300, 2, TIP_MANCARE));
    payment payment_cautat = create_payment(5, 1000, 100, TIP_TELEFON_INTERNET);
    add_payment(&repo, payment_cautat);

    assert(is_payment_included(repo, payment_cautat));
    assert(!is_payment_included(repo, create_payment(1000, 2, 3, TIP_TELEFON_INTERNET)));
}

void test_copiere_lista(){
    repository_payment repo = create_repository_payment();
    add_payment(&repo, create_payment(1, 1, 1, TIP_ALTELE));
    add_payment(&repo, create_payment(2, 2, 2, TIP_MANCARE));
    payment* lista = copiere_lista(&repo);
    for(int i=0; i<repo.maxim_curent; i++)
        assert(payment_equals(lista[i], repo.payments[i]));  // Verifica valori egale

    // Verifica ca este copie
    update_payment(repo, 1, create_payment(3, 3, 3, TIP_IMBRACAMINTE));
    assert(!payment_equals(lista[0], *search_payment(repo, 3)));
}

void run_all_repository_tests() {
    test_repository();
    test_remove();
    test_search();
    test_update();
    test_este_inclus();
    test_copiere_lista();
}
