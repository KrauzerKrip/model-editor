cmake_minimum_required (VERSION 3.13)

project(eng_graphics)

target_sources(lc_client 
    PRIVATE
        "i_window.h"
        "i_render.h"
        "texture.h"
        "mesh_loader.h"
        "shader_loader.h"
        "skybox_render.h"
        "skybox_render.cpp"
        
        "shader_system.h"
        "shader_system.cpp"
        "material_system.h"
        "material_system.cpp"
        "graphics_settings.h"
        "graphics_settings.cpp"

        "openGL/gl_render.cpp"
        "openGL/gl_render.h"
        "openGL/gl_window.cpp"
        "openGL/gl_window.h"
        "openGL/gl_texture.h"
        "openGL/gl_texture.cpp"
        "openGL/gl_mesh_loader.h"
        "openGL/gl_mesh_loader.cpp"
        "openGL/gl_shader_loader.h"
        "openGL/gl_shader_loader.cpp"
        "openGL/gl_shader_uniform.h"
        "openGL/gl_framebuffer.h"
        "openGL/gl_framebuffer.cpp"
        "openGL/gl_skybox_render.h"
        "openGL/gl_skybox_render.cpp"
        "openGL/gl_cubemap.h"
        "openGL/gl_cubemap.cpp"
        "openGL/renders/gl_render_map.h"
        "openGL/renders/gl_render_map.cpp"
        "openGL/renders/gl_lighting.h"
        "openGL/renders/gl_lighting.cpp"
        "openGL/renders/gl_primitive_render.h"
        "openGL/renders/gl_primitive_render.cpp"
        "openGL/renders/gl_transparent_render.h"
        "openGL/renders/gl_transparent_render.cpp"
        "openGL/renders/gl_mesh_render.h"
        "openGL/renders/gl_mesh_render.cpp"
        "openGL/renders/gl_outline_render.h"
        "openGL/renders/gl_outline_render.cpp"
        "openGL/renders/gl_opaque_render.h"
        "openGL/renders/gl_opaque_render.cpp"


        "gui/text_render.h"
        "gui/background_render.h"
        "gui/zoffset_calculator.h"
        "gui/openGL/gl_text_render.h"
        "gui/openGL/gl_text_render.cpp"
        "gui/openGL/gl_background_render.h"
        "gui/openGL/gl_background_render.cpp"
        "gui/openGl/gl_widget_zoffset_calculator.h"
        "gui/openGl/gl_widget_zoffset_calculator.cpp"
        "gui/openGl/gl_text_zoffset_calculator.h"
        "gui/openGl/gl_text_zoffset_calculator.cpp"


        "entt/components.h"

        "camera/camera.h"
        "camera/camera.cpp"

 "openGL/gl_shader_uniform.cpp")