//
// Created by Stelian Stoian on 05/03/2021.
//

#include "payment.h"
#include <stdio.h>
#include <stdlib.h>

payment create_payment(int id, int suma, int zi, PaymentType tip) {
    payment result;
    result.id = id;
    result.suma = suma;
    result.zi = zi;
    result.tip = tip;
    return result;
}

int payment_equals(payment comp1, payment comp2) {
    if(comp1.zi == comp2.zi && comp1.suma == comp2.suma && comp1.tip == comp2.tip && comp1.id == comp2.id)
        return 1;
    return 0;
}

/**
 * Genereaza un string de maxim 100 de caractere care reprezinta un payment.
 * @param de_afisat - paymentul dorit
 * @return un pointer la un string alocat dinamic. Are limitarea de 100 de caractere.
 */
char* afisare_payment(payment de_afisat) {
    char* s = malloc(sizeof(char) * 100);
    sprintf(s,"\nid: %d  suma: %d  zi: %d  tip: %d\n", de_afisat.id, de_afisat.suma, de_afisat.zi, de_afisat.tip);
    return s;
}
