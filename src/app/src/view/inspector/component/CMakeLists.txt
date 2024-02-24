cmake_minimum_required(VERSION 3.13)

project(inspector_components)

add_subdirectory("widgets")
add_subdirectory("components")

target_sources(app
    PRIVATE
    "component.h"
    "component.cpp"
)
