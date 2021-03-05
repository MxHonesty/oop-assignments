//
// Created by Stelian Stoian on 05/03/2021.
//

#include "repository.h"

/** Numarul de elemente initiale dintr-un repository. */
const int NUMAR_ELEMENTE_INITIALE = 10;

repository_payment create_repository_payment() {
    repository_payment result;
    payment* ptr = malloc(NUMAR_ELEMENTE_INITIALE * sizeof(payment));
    result.payments = ptr;
    result.marime = 10;
    result.maxim_curent = 0;
    return result;
}

void destroy_repository_payment(repository_payment repo_de_dealocat) {
    free(repo_de_dealocat.payments);
}

void add_payment(repository_payment* repo, payment de_copiat) {
    repo->payments[repo->maxim_curent] = de_copiat;
    repo->maxim_curent = repo->maxim_curent + 1;
}

payment *search_payment(repository_payment repo, int id_cautat) {
    payment* result = NULL;
    for(int i=0; i<repo.maxim_curent; i++){
        if (repo.payments[i].id == id_cautat) {
            result = &repo.payments[i];
            break;
        }
    }

    return result;
}

void update_payment(repository_payment repo, int id_updatat, payment new_payment) {
    payment* payment_cautat = search_payment(repo, id_updatat);
    if(payment_cautat != NULL){  // Daca a fost gasit
        *payment_cautat = new_payment;  // copiem new_payment in spatiul alocat celui vechi.
    }
}

void remove_payment(repository_payment* repo, int id_removed) {
    int gasit = -1;  // Cautare pozitie element cu id.
    for(int i=0; i<repo->maxim_curent; i++){
        if(id_removed == repo->payments[i].id)
            gasit = i;
    }

    if(gasit != -1){
        for(int i=gasit; i<repo->maxim_curent; i++)
            repo->payments[i] = repo->payments[i+1];

        repo->maxim_curent--;
    }
}
