cmake_minimum_required(VERSION 3.13)

project(top_toolbar)

target_sources(app
    PRIVATE
    "top_toolbar.h"
    "top_toolbar.cpp"
    "tool_button.h"
    "tool_button.cpp"
)
