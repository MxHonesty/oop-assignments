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
	
	Service* srv_oferte = creeaza_service();

	run(srv_oferte);
	
	_CrtDumpMemoryLeaks();

	return 0;
}