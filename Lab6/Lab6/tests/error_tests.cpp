#include "error_tests.h"
#include "../errors/ServiceError.h"
#include "../errors/RepoError.h"
#include "../errors/UiError.h"
#include <cassert>


void ServiceError_test() {
	try {
		throw ServiceError{ "Ceva rau!" };
	}
	catch (const ServiceError& e) {
		assert(std::string{ e.what() } == "Ceva rau!");
	}
}

void RepoError_test() {
	try {
		throw RepoError{ "Ceva rau!" };
	}
	catch (const RepoError& e) {
		assert(std::string{ e.what() } == "Ceva rau!");
	}
}

void UI_Error_test() {
	try {
		throw UiError{ "Ceva rau!" };
	}
	catch (const UiError& e) {
		assert(std::string{ e.what() } == "Ceva rau!");
	}
}

void Testing::run_all_error_tests() {
	ServiceError_test();
	RepoError_test();
	UI_Error_test();
}
