//
// Created by Stelian Stoian on 07/03/2021.
//

#include "test_service.h"
#include "../service/service_payment.h"
#include <assert.h>

void test_create_destroy(){
    service_payments service;
    construct_service(&service);
    assert(service.repo.payments != NULL);

    destroy_service(&service);
}

void test_adaugare(){
    service_payments service;
    construct_service(&service);

    adaugare_payment(&service, 2, 2, 2, TIP_TELEFON_INTERNET);
    adaugare_payment(&service, 1, 1, 1, TIP_MANCARE);
    payment cel_adaugat = create_payment(1, 1, 1, TIP_MANCARE);

    assert(payment_equals(*search_payment(service.repo, 1), cel_adaugat));

    destroy_service(&service);
}

void test_stergere(){
    service_payments service;
    construct_service(&service);

    adaugare_payment(&service, 1, 1, 1, TIP_MANCARE);
    adaugare_payment(&service, 2, 2, 2, TIP_TELEFON_INTERNET);
    adaugare_payment(&service, 3, 3, 3, TIP_TRANSPORT);

    stergere_payment(&service, 1);
    payment* cautat = search_payment(service.repo, 1);
    assert(cautat == NULL);

    assert(payment_equals(service.repo.payments[0], create_payment(2, 2, 2, TIP_TELEFON_INTERNET)));
    assert(service.repo.marime == 10);
    assert(service.repo.maxim_curent == 2);

    assert(1 == stergere_payment(&service, 1000));

    destroy_service(&service);
}

void test_modificare(){
    service_payments  service;
    construct_service(&service);
    adaugare_payment(&service, 2, 2, 2, TIP_TRANSPORT);
    adaugare_payment(&service, 3, 3, 3, TIP_TELEFON_INTERNET);
    adaugare_payment(&service, 1, 1, 1, TIP_MANCARE);

    modificare_payment(&service, 1, 4, 4, 4, TIP_ALTELE);
    payment new_payment = create_payment(4, 4, 4, TIP_ALTELE);
    payment* cautat = search_payment(service.repo, 4);
    assert(payment_equals(*cautat, new_payment));
    cautat = search_payment(service.repo, 1);
    assert(cautat == NULL);

    assert(1 == modificare_payment(&service, 1000, 10, 10, 10, TIP_MANCARE));

    destroy_service(&service);
}

void test_redimensionare(){
    service_payments service;
    construct_service(&service);
    payment de_test = create_payment(1, 1, 1, TIP_ALTELE);
    for(int i=0; i<15; i++)
        add_payment(&service.repo, de_test);

    assert(service.repo.marime == 20);
    assert(service.repo.maxim_curent == 15);

    for(int i=0; i<15; i++)
        add_payment(&service.repo, de_test);

    assert(service.repo.marime == 40);
    assert(service.repo.maxim_curent == 30);

    destroy_service(&service);
}

#include <stdio.h>

void test_sort_suma(){
    service_payments service;
    construct_service(&service);
    adaugare_payment(&service, 1, 3, 1, TIP_ALTELE);
    adaugare_payment(&service, 2, 2, 1, TIP_ALTELE);
    adaugare_payment(&service, 3, 10, 1, TIP_ALTELE);
    adaugare_payment(&service, 10, 1, 1, TIP_ALTELE);

    payment* lista = sortare_suma(&service, 1);
    assert(payment_equals(lista[0], create_payment(10, 1, 1, TIP_ALTELE)));
    assert(payment_equals(lista[1], create_payment(2, 2, 1, TIP_ALTELE)));
    assert(payment_equals(lista[2], create_payment(1, 3, 1, TIP_ALTELE)));
    assert(payment_equals(lista[3], create_payment(3, 10, 1, TIP_ALTELE)));
    free(lista);

    lista = sortare_suma(&service, 0);
    assert(payment_equals(lista[0], create_payment(3, 10, 1, TIP_ALTELE)));
    assert(payment_equals(lista[1], create_payment(1, 3, 1, TIP_ALTELE)));
    assert(payment_equals(lista[2], create_payment(2, 2, 1, TIP_ALTELE)));
    assert(payment_equals(lista[3], create_payment(10, 1, 1, TIP_ALTELE)));
    free(lista);
}

/**
 * Ruleaza toate testele din service.
 */
void run_all_service_tests() {
    test_create_destroy();
    test_adaugare();
    test_stergere();
    test_modificare();
    test_redimensionare();
    test_sort_suma();
}
