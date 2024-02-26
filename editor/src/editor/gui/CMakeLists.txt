cmake_minimum_required(VERSION 3.13)

project(gui)

add_subdirectory("view")
add_subdirectory("controller")

target_sources(editor PRIVATE
	"gui.h"
	"gui.cpp"
	"demo.h"
)