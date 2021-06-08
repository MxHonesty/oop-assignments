#include "Test.h"
#include <sstream>
#include "Task.h"
#include <string>
#include <vector>
#include <cassert>
#include "Repository.h"

void Test::test_cititre_task() {
	std::istringstream in{ "0|DescA|Atare|Alex|Salut|#|\n1|DescB|Btare|#|\n" };
	Task tsk1{ 0, "A", "A", std::vector<std::string>{} };
	Task tsk2{ 0, "A", "A", std::vector<std::string>{} };
	in >> tsk1 >> tsk2;

	assert(tsk1.get_id() == 0);
	assert(tsk2.get_id() == 1);

	assert(tsk1.get_programatori()[0] == "Alex");
	assert(tsk1.get_programatori().size() == 2);
	assert(tsk2.get_programatori().size() == 0);
}

void Test::test_citire_repo() {
	Repository repo{ "data.txt" };
	const auto& vec = repo.get_all();
	assert(vec.size() == 5);
}

void Test::run_all_tests() {
	test_cititre_task();
	test_citire_repo();
}
