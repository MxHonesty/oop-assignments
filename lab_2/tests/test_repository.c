//
// Created by Stelian Stoian on 05/03/2021.
//

#include "test_repository.h"
#include <stdio.h>

void test_repository() {
    // Am creat un element, adagat, sters, si adaugat un nou element
    repository_payment repo = create_repository_payment();
    payment de_adaugat = create_payment(1, 100, 27, TIP_MANCARE);
    add_payment(&repo, de_adaugat);

    printf("%d %d %d\n", repo.payments[0].id, repo.payments[0].suma, repo.payments[0].zi);

    remove_payment(&repo, 1);
    payment new_payment = create_payment(1, 200, 1, TIP_ALTELE);
    add_payment(&repo, new_payment);

    printf("%d %d %d\n", repo.payments[0].id, repo.payments[0].suma, repo.payments[0].zi);

}

void test_remove(){
    repository_payment repo = create_repository_payment();
    add_payment(&repo, create_payment(1, 200, 1, TIP_IMBRACAMINTE));
    add_payment(&repo, create_payment(2, 200, 20, TIP_ALTELE));
    remove_payment(&repo, 1);
    printf("%d %d %d\n", repo.payments[0].id, repo.payments[0].suma, repo.payments[0].zi);
}

void test_search(){
    repository_payment repo = create_repository_payment();
    add_payment(&repo, create_payment(1, 200, 2, TIP_TELEFON_INTERNET));
    payment* ptr = search_payment(repo, 1);
    printf("%d %d %d\n", ptr->id, ptr->suma, ptr->zi);
}

void test_update(){
    repository_payment repo = create_repository_payment();
    add_payment(&repo, create_payment(1, 200, 1, TIP_IMBRACAMINTE));
    update_payment(repo, 1, create_payment(2, 1, 3, TIP_TELEFON_INTERNET));

    printf("%d %d %d\n", repo.payments[0].id, repo.payments[0].suma, repo.payments[0].zi);
}

void run_all_repository_tests() {
    test_repository();
    test_remove();
    //test_update();
    test_search();
}
