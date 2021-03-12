//
// Created by Stelian Stoian on 07/03/2021.
//

#include "ui.h"
#include <stdio.h>
#include <string.h>

void run() {
    service_payments service;
    construct_service(&service); // Construeiste service-ul.

    int running = 1;

    while(running){
        char optiune;
        printf("\n\n1-Adaugare\n2-Stergere\n3-Modificare\n4-Afisare\n5-Sortare Suma\n6-Sortare Tip\n"
               "7-Filtrare Element\n8-Filtrare Tip\nq-Iesire\n");
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
            case '5':  // Sortare Suma
                ui_sortare_suma(&service);
                break;
            case '6':   // Sortare tip
                ui_sortare_tip(&service);
                break;
            case '7':  // Filtrare element
                ui_filtrare_element(&service);
                break;
            case '8':  // Filtrare Tip
                ui_filtrare_tip(&service);
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
    int* ptr = citire_payment_fara_id();
    if(ptr == NULL){
        return;
    }

    adaugare_payment_user(srv, ptr[0], ptr[1], ptr[2]);
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
    if(zi <= 0 || zi > 31){
        printf("Zi invalida\n");
        return NULL;
    }
    fflush(stdin);

    tip = citire_tip("tip: ");
    if(tip < 0){
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

/**
 * Afiseaza pe ecram lista de paymenturi data.
 * @param lista
 * @param marime
 */
void ui_afisare_lista(payment* lista, int marime){
    for(int i = 0; i<marime; i++){
        char* s = afisare_payment(lista[i]);
        printf("%s", s);
        free(s);
    }
}

void ui_sortare_suma(service_payments *srv) {
    int crescator = citire_int("1-Crescator, 2-Descrescator: ");
    if(crescator == 1) {
        payment *lista = sortare_suma(srv, 1);
        ui_afisare_lista(lista, srv->repo.maxim_curent);
        free(lista);
    }
    else if(crescator == 2){
        payment* lista = sortare_suma(srv, 0);
        ui_afisare_lista(lista, srv->repo.maxim_curent);
        free(lista);
    }
    else
        printf("Optiune de sortare invalida.");

}

void ui_sortare_tip(service_payments *srv) {
    int crescator = citire_int("1-Crescator, 2-Descrescator: ");
    if(crescator == 0)
        printf("Optiune de sortare invalida. ");
    else if(crescator == 1){
        payment *lista = sortare_tip(srv, 1);
        ui_afisare_lista(lista, srv->repo.maxim_curent);
        free(lista);
    }
    else if(crescator == 2){
        payment* lista = sortare_tip(srv, 0);
        ui_afisare_lista(lista, srv->repo.maxim_curent);
        free(lista);
    }
}

int citire_tip(const char* text) {
    char sir[30];
    int tip = -1;
    printf("%s", text);
    scanf("%30s", sir);
    fflush(stdin);
    if(strcmp(sir, "mancare") == 0)
        tip = TIP_MANCARE;
    else if(strcmp(sir, "transport") == 0)
        tip = TIP_TRANSPORT;
    else if(strcmp(sir, "telefon") == 0)
        tip = TIP_TELEFON_INTERNET;
    else if(strcmp(sir, "imbracaminte") == 0)
        tip = TIP_IMBRACAMINTE;
    else if(strcmp(sir, "altele") == 0)
        tip = TIP_ALTELE;

    return tip;
}

void ui_filtrare_element(service_payments* srv){
    int tipul_filtrului = citire_int("Tipul filtrului 1-Suma, 2-Zi, 3-Tip: ");
    if(tipul_filtrului < 1 || tipul_filtrului > 3){
        printf("%s", "Tip invalid");
        return;
    }

    int inceput = citire_int("Limita inferioara (-1 - fara limita inferioara): ");
    if(inceput < -1 || inceput == 0){
        printf("%s", "Limita invalida");
        return;
    }
    printf("\n");
    int final = citire_int("Limina superioara (-1 - fara limita superioara): ");
    if(final < -1 || final == 0){
        printf("%s", "Limita invalida");
        return;
    }

    // Initializam valorile la cea mai mica, respectiv cea mai mare daca nu este pusa o limita.
    if(inceput == -1)
        inceput = 0;
    if(final == -1)
        final = valoare_maxima(srv->repo);

    Vector rez;
    rez = filtrare_elemente(srv, inceput, final, tipul_filtrului);

    if(rez.marime <= 0){
        printf("Nu au fost gasite elemente cu aceste conditii.");
        return;
    }
    ui_afisare_lista(rez.list, rez.marime);
    free(rez.list);
}

void ui_filtrare_tip(service_payments* srv){
    char filtru[20];  // Filtrul pe care il citim.
    printf("Tipul dorit: ");
    scanf("%20s", filtru);
    fflush(stdin);

    Vector elemente = filtrare_elemente_tip_string(srv, filtru);
    if(elemente.marime > 0)
        ui_afisare_lista(elemente.list, elemente.marime);
    else
        printf("Nu au fost gasite elemente cu tipul %s", filtru);
    free(elemente.list);
}

int *citire_payment_fara_id() {
    int* ptr = malloc(sizeof(int) * 3);
    int suma, zi, tip;

    suma = citire_int("suma: ");
    if(suma <= 0){
        printf("Suma invalida\n");
        return NULL;
    }
    fflush(stdin);

    zi = citire_int("zi: ");
    if(zi <= 0 || zi > 31){
        printf("Zi invalida\n");
        return NULL;
    }
    fflush(stdin);

    tip = citire_tip("tip: ");
    if(tip < 0){
        printf("Tip invalid\n");
        return NULL;
    }
    fflush(stdin);

    ptr[0] = suma;
    ptr[1] = zi;
    ptr[2] = tip;
    return ptr;
}


// TODO id dat din service