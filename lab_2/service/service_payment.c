//
// Created by Stelian Stoian on 07/03/2021.
//

#include "service_payment.h"

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
