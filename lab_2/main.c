#include "./tests/tests.h"
#include "./ui/ui.h"

int main() {
    run_all_tests();

    run();  // Main loop ui function.
    return 0;
}
