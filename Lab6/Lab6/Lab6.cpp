/** Laborator  6. 23/03/2021 Stelian Stoian
* Fisierul principal al programului.
* 6 Agentie de turism
* Creati o aplicatie care permite:
* gestiunea unei liste de oferte turistice. Oferta: denumire, destinatie, tip, pret
* adaugare, stergere, modificare si afisare  oferte turistice
* cautare oferta.
* filtrare oferte turistice dupa: destinatie, pret
* sortare oferte dupa: denumire, destinatie, tip + pret
*/
#include <iostream>
#include "tests/tests.h"
#include <crtdbg.h>

int main()
{   
    Testing::run_all_tests();
    std::cout << "Test success\n";

    _CrtDumpMemoryLeaks();
}