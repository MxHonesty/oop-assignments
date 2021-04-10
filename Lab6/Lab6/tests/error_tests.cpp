#include "error_tests.h"
#include "../errors/ServiceError.h"
#include "../errors/RepoError.h"
#include "../errors/UiError.h"
#include "../errors/CosError.h"
#include <cassert>
#include "../errors/FileError.h"

/** Test Exceptie de Service */
void ServiceError_test() {
	try {
		throw ServiceError{ "Ceva rau!" };
	}
	catch (const ServiceError& e) {
		assert(std::string{ e.what() } == "Ceva rau!");
	}
}

/** Test Exceptie de Repo */
void RepoError_test() {
	try {
		throw RepoError{ "Ceva rau!" };
	}
	catch (const RepoError& e) {
		assert(std::string{ e.what() } == "Ceva rau!");
	}
}

/** Test Exceptie de UI */
void UI_Error_test() {
	try {
		throw UiError{ "Ceva rau!" };
	}
	catch (const UiError& e) {
		assert(std::string{ e.what() } == "Ceva rau!");
	}
}

/** Test Exceptie de Cos */
void CosError_test() {
	try {
		throw CosError{ "Ceva rau!" };
	}
	catch (const CosError& e) {
		assert(std::string{ e.what() } == "Ceva rau!");
	}
}

/** Test Exceptie de File */
void FileError_test() {
	try {
		throw FileError{ "Ceva rau!" };
	}
	catch (const FileError& e) {
		assert(std::string{ e.what() } == "Ceva rau!");
	}
}

void Testing::run_all_error_tests() {
	ServiceError_test();
	RepoError_test();
	UI_Error_test();
	CosError_test();
	FileError_test();
}
