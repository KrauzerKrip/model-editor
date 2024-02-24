project(app)

add_subdirectory("src/controller")
add_subdirectory("src/model")
add_subdirectory("src/view")

target_include_directories(app
    PUBLIC
        $<INSTALL_INTERFACE:/include>
        $<INSTALL_INTERFACE:/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)
