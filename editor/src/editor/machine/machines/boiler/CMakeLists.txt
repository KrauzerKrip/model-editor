cmake_minimum_required(VERSION 3.13)

project(machines_boiler)

target_sources(editor PRIVATE
	"components.h"
	"boiler_system.h"
	"boiler_system.cpp"
)