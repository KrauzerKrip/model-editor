cmake_minimum_required(VERSION 3.13)

project(side_toolbar)

target_sources(app
    PRIVATE
    "side_toolbar.h"
    "side_toolbar.cpp"
    "tool_button.h"
    "tool_button.cpp"
)
