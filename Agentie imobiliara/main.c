#include "teste.h"
#include "ui.h"
#include "service.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h> 
#include <stdio.h>
#include <stdlib.h>

int main() {
	run_all_tests();
	printf("Teste trecute cu succes!\n");

	/*
	Repository* repo_oferte;
	repo_oferte = creeaza_repo();
	Service* srv_oferte = creeaza_service(repo_oferte);

	run(srv_oferte);
	*/
	_CrtDumpMemoryLeaks();

	return 0;
}