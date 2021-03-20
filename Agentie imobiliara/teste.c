#include "TestDomain.h"
#include "TestRepo.h"
#include "TestService.h"
#include "TestUtils.h"
#include "TestValidare.h"
#include "TestList.h"

#include <stdio.h>


void run_all_tests() {
	run_all_domain_tests();
	printf("Domain done.");
	run_all_valid_tests();
	printf("Valid done.");
	run_all_repo_tests();
	printf("Repo done.");
	run_all_service_tests();
	printf("Service done.");
	run_all_utils_tests();
	printf("Utils done. ");
	run_all_list_tests();
	printf("List done.");
}