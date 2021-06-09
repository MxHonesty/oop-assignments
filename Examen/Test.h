#pragma once
class Test {
private:

	// Test case pentru citiri, scrieri, seteri si getteri pe Task.
	void test_task();

	// Test case pentru repository.
	void test_repo();

	// Test case pentru Functionalitatile din service.
	void test_service();

public:
	// Ruleaza toate testele.
	void run_all_tests() {
		test_task();
		test_repo();
		test_service();
	};
};
