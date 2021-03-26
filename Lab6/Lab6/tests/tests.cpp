#include "tests.h"
#include "oferta_tests.h"
#include "repository_tests.h"
#include "service_tests.h"

void Testing::run_all_tests() {
	Testing::run_oferta_tests();  // Teste entitate oferta.
	Testing::run_oferta_repository_tests();  // Teste repository oferta.
	Testing::run_all_service_tests();  // Teste service oferta.
}
