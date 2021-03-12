//
// Created by Stelian Stoian on 07/03/2021.
//

#include "test_domain.h"
#include <assert.h>
#include "../domain/payment.h"
#include <string.h>
#include "stdlib.h"

void test_payment_equals(){
    payment first = create_payment(1, 100, 2, TIP_TELEFON_INTERNET);
    payment seconds = create_payment(1, 100, 2, TIP_TELEFON_INTERNET);
    payment third = create_payment(2, 100, 2, TIP_MANCARE);

    assert(payment_equals(first, seconds));
    assert(!payment_equals(first, third));
}

void test_afisare(){
    payment testing = create_payment(1, 1, 1, TIP_TRANSPORT);
    char* s = afisare_payment(testing);
    assert(!strcmp(s, "\nid: 1  suma: 1  zi: 1  tip: transport\n"));
    free(s);

    testing = create_payment(1, 1, 1, TIP_MANCARE);
    s = afisare_payment(testing);
    assert(!strcmp(s, "\nid: 1  suma: 1  zi: 1  tip: mancare\n"));
    free(s);

    testing = create_payment(1, 1, 1, TIP_IMBRACAMINTE);
    s = afisare_payment(testing);
    assert(!strcmp(s, "\nid: 1  suma: 1  zi: 1  tip: imbracaminte\n"));
    free(s);

    testing = create_payment(1, 1, 1, TIP_TELEFON_INTERNET);
    s = afisare_payment(testing);
    assert(!strcmp(s, "\nid: 1  suma: 1  zi: 1  tip: telefon\n"));
    free(s);

    testing = create_payment(1, 1, 1, TIP_ALTELE);
    s = afisare_payment(testing);
    assert(!strcmp(s, "\nid: 1  suma: 1  zi: 1  tip: altele\n"));
    free(s);
}

void run_all_doimain_tests() {
    test_payment_equals();
    test_afisare();
}
