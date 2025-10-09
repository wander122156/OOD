cmake_minimum_required(VERSION 3.30)
project(Shapes)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
        sfml
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1
)

FetchContent_MakeAvailable(sfml)


add_executable(Shapes
        src/main.cpp

        src/CPoint.cpp
        src/ConvexAdapter.cpp
        src/RectangleAdapter.cpp
        src/CircleAdapter.cpp

        include/IShape.h
        include/CircleAdapter.h
        include/ConvexAdapter.h
        include/RectangleAdapter.h
)

include_directories(include)

configure_file(
        ${CMAKE_SOURCE_DIR}/shapes.txt
        ${CMAKE_CURRENT_BINARY_DIR}/shapes.txt
        COPYONLY
)

add_executable(tests
        src/CPoint.cpp
        src/ConvexAdapter.cpp
        src/RectangleAdapter.cpp
        src/CircleAdapter.cpp
        include/IShape.h
        tests/test.cpp
)

target_link_libraries(Shapes
        sfml-graphics
        sfml-window
        sfml-system
)
