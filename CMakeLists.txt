cmake_minimum_required(VERSION 3.20)
project(lab_5c C)

set(CMAKE_C_STANDARD 11)

add_executable(lab_5c main.c libs/experiments/experiments.c libs/experiments/experiments.h)

add_subdirectory(libs)
target_link_libraries(lab_5c experiments)