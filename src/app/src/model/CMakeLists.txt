project(model)

add_subdirectory("project")
add_subdirectory("inspector")
add_subdirectory("core")

target_sources(app PRIVATE
    editor.h
    editor.cpp
    "editor_mode_handler.h"
    "editor_mode_handler.cpp"
    "viewer_thread.h"
    "viewer_thread.cpp"
)
