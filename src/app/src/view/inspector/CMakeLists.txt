cmake_minimum_required(VERSION 3.13)

project(inspector)

add_subdirectory("component")

target_sources(app
    PRIVATE
    "inspector.h"
    "inspector.cpp"
    "component_view.h"
    "component_view.cpp"
)
