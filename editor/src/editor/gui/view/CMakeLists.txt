cmake_minimum_required(VERSION 3.13)

project(gui_view)


target_sources(editor PRIVATE
	"menu.h"
	"menu.cpp"
	"tool_bar.h"
	"tool_bar.cpp"
	"inspector.h"
	"inspector.cpp"
)