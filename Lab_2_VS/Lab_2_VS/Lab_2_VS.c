#include "./tests/tests.h"
#include "./ui/ui.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main() {
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    run_all_tests();

    run();  // Main loop ui function.

    _CrtDumpMemoryLeaks();
    return 0;
}
