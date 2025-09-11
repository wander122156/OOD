cmake_minimum_required(VERSION 3.30)
project(OOD_3curse_)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_subdirectory(SimUDuck/googletest)

add_executable(SimUDuck
        SimUDuck/SimUDuck.cpp)


add_executable(tests
        SimUDuck/tests/test.cpp
        SimUDuck/tests/MockFlyBehavior.h
        SimUDuck/tests/MockQuackBehavior.h
        SimUDuck/tests/MockDanceBehavior.h)

target_link_libraries(tests gtest_main gmock_main)
