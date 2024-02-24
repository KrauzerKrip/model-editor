cmake_minimum_required(VERSION 3.13)

project(core)

add_subdirectory("graphics")
add_subdirectory("input")

target_sources(app
    PRIVATE
    "game.h"
    "game.cpp"
    "game_logic.h"
    "game_logic.cpp"
)
