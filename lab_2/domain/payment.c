//
// Created by Stelian Stoian on 05/03/2021.
//

#include "payment.h"

payment create_payment(int id, int suma, int zi, PaymentType tip) {
    payment result;
    result.id = id;
    result.suma = suma;
    result.zi = zi;
    result.tip = tip;
    return result;
}
