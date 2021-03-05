cmake_minimum_required(VERSION 3.17)
project(lab_2 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab_2 main.c domain/payment.c domain/payment.h repository/repository.c repository/repository.h tests/test_repository.c tests/test_repository.h)