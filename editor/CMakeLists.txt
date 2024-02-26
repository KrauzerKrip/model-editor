cmake_minimum_required(VERSION 3.13)

project(editor)

add_executable(editor "src/editor/main.cpp" "src/editor/main.h" "src/editor/game.cpp" "src/editor/game.h")

add_subdirectory("src/editor/gui")
add_subdirectory("src/editor/loader_fabric")
add_subdirectory("src/editor/camera")
add_subdirectory("src/editor/control")
add_subdirectory("src/editor/character")
add_subdirectory("src/editor/graphics")

find_package(imguizmo CONFIG REQUIRED)
target_link_libraries(editor PRIVATE imguizmo::imguizmo)

target_include_directories(editor
    PUBLIC
        $<INSTALL_INTERFACE:/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)
