cmake_minimum_required(VERSION 3.28)

project(control)

target_sources(editor PRIVATE
	"action_bind.h"
	"action_bind.cpp"
	
	
	"action_control.h"
	"action_control.cpp"
	"components.h"
	"mouse_raycast_system.h"
	"mouse_raycast_system.cpp"
 "mouse_raycast_observer.h"
 "selection_system.h"
 "selection_system.cpp"
 
  "control_system.h"
 "control_system.cpp"
 "mouse_raycast.h"
 "mouse_raycast.cpp"
 "character_control_system.h"
 "character_control_system.cpp"
)