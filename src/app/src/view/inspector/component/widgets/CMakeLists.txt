cmake_minimum_required(VERSION 3.13)

project(inspector_component_widgets)

target_sources(app
    PRIVATE
    "vector3f_view.h"
    "vector3f_view.cpp"
    "string_view.h"
    "string_view.cpp"
)
