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
        include/Picture.h
        src/Picture.cpp
        include/IGroup.h
        include/Group.h
        include/RectD.h
        include/ShapesController.h
        src/ShapesController.cpp
        src/PictureService.cpp
        include/PictureService.h
        src/SelectionManager.cpp
        include/SelectionManager.h
        src/ShapeFactory.cpp
        include/ShapeFactory.h
        src/Group.cpp
)

include_directories(include)

configure_file(
        ${CMAKE_SOURCE_DIR}/shapes.txt
        ${CMAKE_CURRENT_BINARY_DIR}/shapes.txt
        COPYONLY
)

# Автоматическое копирование DLL файлов после сборки
add_custom_command(TARGET Shapes POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:sfml-graphics>"
        $<TARGET_FILE_DIR:Shapes>
)

add_custom_command(TARGET Shapes POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:sfml-window>"
        $<TARGET_FILE_DIR:Shapes>
)

add_custom_command(TARGET Shapes POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:sfml-system>"
        $<TARGET_FILE_DIR:Shapes>
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

# Для Windows добавляем системные библиотеки
if (WIN32)
    target_link_libraries(Shapes opengl32 winmm)
endif ()