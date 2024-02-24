cmake_minimum_required(VERSION 3.13)

set(QT_CREATOR_SKIP_CONAN_SETUP ON)

project(editor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
        src/mainwindow.ui
)


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core Gui OpenGL OpenGLWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core Gui OpenGL OpenGLWidgets)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(editor
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET editor APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(editor SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(editor
            ${PROJECT_SOURCES}
        )
    endif()
endif()

add_library(app
    src/app/src/model/core/input/CMakeLists.txt
    src/app/src/model/core/graphics/render.h src/app/src/model/core/graphics/render.cpp
    src/app/src/model/core/graphics/framebuffer.h src/app/src/model/core/graphics/framebuffer.cpp
    src/app/src/model/core/graphics/opengl_debugger.h src/app/src/model/core/graphics/opengl_debugger.cpp)

target_link_libraries(editor PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::OpenGL Qt${QT_VERSION_MAJOR}::OpenGLWidgets app)
target_link_libraries(app PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::OpenGL Qt${QT_VERSION_MAJOR}::OpenGLWidgets)

include(E:/Industry/industry/vcpkg/scripts/buildsystems/vcpkg.cmake)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(pugixml CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_path(LUABRIDGE_INCLUDE_DIRS "LuaBridge/List.h")
find_package(Lua REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(freetype CONFIG REQUIRED)

add_subdirectory("src/app")
add_library(lc_client)
add_subdirectory("lc_client")
add_library(stb INTERFACE)
add_subdirectory("libs")
add_subdirectory("res")


target_link_libraries(app PRIVATE lc_client)


set_property(TARGET editor PROPERTY COMPILE_WARNING_AS_ERROR ON)

set_target_properties(editor PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS editor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(editor)
endif()
