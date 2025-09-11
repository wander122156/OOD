cmake_minimum_required(VERSION 3.30)
project(4-lab)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_subdirectory(googletest)

add_executable(4-lab
        src/main.cpp
        src/ShapeParser.cpp
        src/CPoint.cpp
        src/CLineSegment.cpp
        src/CTriangle.cpp
        src/CRectangle.cpp
        src/CCircle.cpp
        include/IShape.h
        include/ShapeParser.h
        include/IShapeStrategy.h
        include/ICanvas.h
)

include_directories(include)

add_executable(tests
        src/ShapeParser.cpp
        src/CPoint.cpp
        src/CLineSegment.cpp
        src/CTriangle.cpp
        src/CRectangle.cpp
        src/CCircle.cpp
        include/IShape.h
        include/ShapeParser.h
        tests/test.cpp
)

target_link_libraries(tests gtest)
