cmake_minimum_required(VERSION 3.13)

project(view)

add_subdirectory("side_toolbar")
add_subdirectory("inspector")
add_subdirectory("top_toolbar")

target_sources(app
    PRIVATE
    "menu_bar.h"
    "menu_bar.cpp"
    "main_layout.h"
    "main_layout.cpp"
)



