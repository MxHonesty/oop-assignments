//
// Created by Stelian Stoian on 07/03/2021.
//

#include "service_payment.h"
#include <string.h>

void construct_service(service_payments *service) {
    service->repo = create_repository_payment();
}

void destroy_service(service_payments *service) {
    destroy_repository_payment(service->repo);
}

int adaugare_payment(service_payments* service, int id, int suma, int zi, int tip) {
    payment new_payment = create_payment(id, suma, zi, tip);
    // TODO: Aici s-ar executa validarea.
    add_payment(&service->repo, new_payment);
    return 0;
}

int stergere_payment(service_payments *service, int id) {
    payment* cautat = search_payment(service->repo, id);
    if(cautat == NULL)
        return 1;
    remove_payment(&service->repo, id);
    return 0;
}

int modificare_payment(service_payments *service, int id, int new_id, int new_suma, int new_zi, int new_tip) {
    payment* cautat = search_payment(service->repo, id);
    if(cautat == NULL)
        return 1;

    payment new_payment = create_payment(new_id, new_suma, new_zi, new_tip);
    update_payment(service->repo, id, new_payment);
    return 0;
}

/**
 * Interschimba doua paymenturi
 * @param pay1
 * @param pay2
 */
void switch_payments(payment* pay1, payment* pay2){
    payment auxiliar = *pay1;
    *pay1= *pay2;
    *pay2 = auxiliar;
}

payment *sortare_suma(service_payments *service, int crescator) {
    payment* lista = copiere_lista(&service->repo);
    int marime = service->repo.maxim_curent;

    if(crescator == 1){
        for(int i=0; i<marime-1; i++)
            for(int j=i+1; j<marime; j++)
                if(lista[i].suma > lista[j].suma)
                    switch_payments(&lista[i], &lista[j]);
    } else if(crescator == 0){
        for(int i=0; i<marime-1; i++)
            for(int j=i+1; j<marime; j++)
                if(lista[i].suma < lista[j].suma)
                    switch_payments(&lista[i], &lista[j]);
    }

    return lista;
}

payment *sortare_tip(service_payments *service, int crescator) {
    payment* lista = copiere_lista(&service->repo);
    int marime = service->repo.maxim_curent;

    if(crescator == 1){
        for(int i=0; i<marime-1; i++)
            for(int j=i+1; j<marime; j++) {
                char* a = conversie_tip(lista[i].tip);
                char* b = conversie_tip(lista[j].tip);
                if (strcmp(a, b) > 0)
                    switch_payments(&lista[i], &lista[j]);
                free(a);
                free(b);
            }
    }
    else if(crescator == 0){
        for(int i=0; i<marime-1; i++)
            for(int j=i+1; j<marime; j++) {
                char* a = conversie_tip(lista[i].tip);
                char* b = conversie_tip(lista[j].tip);
                if (strcmp(a, b) < 0)
                    switch_payments(&lista[i], &lista[j]);
                free(a);
                free(b);
            }
    }

    return lista;
}
