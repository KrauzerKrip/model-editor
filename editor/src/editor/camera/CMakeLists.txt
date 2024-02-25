cmake_minimum_required(VERSION 3.13)

project(camera)

target_sources(editor PRIVATE
	"camera_controller.h"
	"orbital_camera_controller.h"
	"orbital_camera_controller.cpp"
)