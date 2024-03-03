cmake_minimum_required(VERSION 3.13)

project(model)

add_subdirectory("file_work")

target_sources(editor PRIVATE
	"editor.h"
	"editor.cpp"
	"project.h"
	"project.cpp"
	"components.h"
)