#include "tests.h"
#include "oferta_tests.h"
#include "repository_tests.h"
#include "service_tests.h"
#include "VectorDinamic_tests.h"
#include "service_tests.h"
#include "validator_test.h"
#include "Cos_tests.h"
#include "error_tests.h"
#include "FileRepoTests.h"

void Testing::run_all_tests() {
	Testing::run_oferta_tests();  // Teste entitate oferta.
	Testing::run_oferta_repository_tests();  // Teste repository oferta.
	Testing::run_all_service_tests();  // Teste service oferta.
	Testing::run_all_VectorDinamic_tests();
	Testing::run_validator_tests();
	Testing::run_all_cos_tests();
	Testing::run_all_error_tests();
	Testing::run_file_repo_tests();
}
