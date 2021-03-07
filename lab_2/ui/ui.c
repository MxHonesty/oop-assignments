//
// Created by Stelian Stoian on 07/03/2021.
//

#include "ui.h"
#include <stdio.h>

void run() {
    service_payments service;
    construct_service(&service); // Construeiste service-ul.

    int running = 1;

    while(running){
        char optiune;
        printf("\n\n1-Adaugare\n2-Stergere\n3-Modificare\n4-Afisare\nq-Iesire\n");
        printf("Alegeti o optiune: ");
        scanf("%c", &optiune);
        fflush(stdin);  // Dau flush dupa fiecare citire ca se se ignore inputul in plus.
        switch (optiune) {
            case '1':  // Adaugare
                ui_adaugare(&service);
                break;
            case '2':  // Stergere
                ui_stergere(&service);
                break;
            case '3':  // Modificare
                ui_modificare(&service);
                break;
            case '4':  // Afisare
                ui_print_all(&service);
                break;
            case 'q':
                running = 0;
                break;
            default:
                printf("Optiunea nu este recunoscuta!");
        }
    }


    destroy_service(&service);
}

void ui_print_all(service_payments* srv) {
    for(int i=0; i<srv->repo.maxim_curent; i++){
        char* s = afisare_payment(srv->repo.payments[i]);
        printf("%s", s);
        free(s);
    }
}

void ui_adaugare(service_payments *srv) {
    int* ptr = citire_payment();
    if(ptr == NULL){
        return;
    }

    adaugare_payment(srv, ptr[0], ptr[1], ptr[2], ptr[3]);
}

int citire_int(const char *text) {
    char string[20];
    printf("%s", text);
    scanf("%15s", string);
    fflush(stdin);
    int rez = strtol(string, NULL, 10);
    return rez;
}

void ui_stergere(service_payments *srv) {
    int id;
    id = citire_int("id: ");
    if(id <= 0){
        printf("Id invalid\n");
        return;
    }
    fflush(stdin);

    int negasit = stergere_payment(srv, id);
    if(negasit == 1)
        printf("Elementul nu a fost gasit\n");
}

void ui_modificare(service_payments *srv) {
    int id = citire_int("id: ");
    if(id == 0){
        printf("Id invalid\n");
        return;
    }
    fflush(stdin);
    int* ptr = citire_payment();
    if(ptr == NULL){
        return;
    }

    modificare_payment(srv, id, ptr[0], ptr[1], ptr[2], ptr[3]);
    free(ptr);
}

int *citire_payment() {
    int* ptr = malloc(sizeof(int) * 4);
    int id, suma, zi, tip;
    id = citire_int("id: ");
    if(id <= 0){
        printf("Id invalid\n");
        return NULL;
    }
    fflush(stdin);

    suma = citire_int("suma: ");
    if(suma <= 0){
        printf("Suma invalida\n");
        return NULL;
    }
    fflush(stdin);

    zi = citire_int("zi: ");
    if(zi <= 0){
        printf("Zi invalida\n");
        return NULL;
    }
    fflush(stdin);

    tip = citire_int("tip: ");
    if(tip <= 0){
        printf("Tip invalid\n");
        return NULL;
    }
    fflush(stdin);

    ptr[0] = id;
    ptr[1] = suma;
    ptr[2] = zi;
    ptr[3] = tip;
    return ptr;
}
