cmake_minimum_required(VERSION 3.13)

project(core_graphics)

target_sources(app PRIVATE
    "window.h"
    "window.cpp"
    "viewer.h"
    "viewer.cpp"
    "render.h"
    "render.cpp"
    "framebuffer.h"
    "framebuffer.cpp"
    "opengl_debugger.h"
    "opengl_debugger.cpp"
)
