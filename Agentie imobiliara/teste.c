#include "TestDomain.h"
#include "TestRepo.h"
#include "TestService.h"
#include "TestUtils.h"
#include "TestValidare.h"
#include "TestList.h"

#include <stdio.h>


void run_all_tests() {
	//run_all_domain_tests();
	//run_all_valid_tests();
	//run_all_repo_tests();
	run_all_service_tests();
	//run_all_utils_tests();
	run_all_list_tests();
}