cmake_minimum_required(VERSION 3.17)
project(lab_2 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=leak")

add_executable(lab_2 main.c domain/payment.c domain/payment.h repository/repository.c repository/repository.h tests/test_repository.c tests/test_repository.h service/service_payment.c service/service_payment.h tests/test_service.c tests/test_service.h tests/test_domain.c tests/test_domain.h ui/ui.c ui/ui.h tests/tests.c tests/tests.h)