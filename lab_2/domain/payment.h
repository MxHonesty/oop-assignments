//
// Created by Stelian Stoian on 05/03/2021.
//

#ifndef LAB_2_PAYMENT_H
#define LAB_2_PAYMENT_H
/**
 * Pastreaza codurile pentru fiecare tip.
 */
typedef enum{
    TIP_MANCARE,
    TIP_TRANSPORT,
    TIP_TELEFON_INTERNET,
    TIP_IMBRACAMINTE,
    TIP_ALTELE,
    NUMAR_TIPURI
} PaymentType ;

/**
 * Structura unei cheltuieli.
 * Pastreaza o suma, o zi si un tip.
 * Toate elementele acestui struct pot fi acesate din exterior deci nu exista nevoia de a crea getteri, setteri.
 */
typedef struct{
    int id;
    int suma;
    int zi;
    int tip;
} payment;

/**
 * Creeaza si returneaza o structura de tip payment.
 * @param suma - valoarea sumei.
 * @param zi - valoarea zilei
 * @param tip - tipul sumei. Valoare de la 0-4 conform PaymentType
 * @return payment
 */
payment create_payment(int id, int suma, int zi, PaymentType tip );


#endif //LAB_2_PAYMENT_H
