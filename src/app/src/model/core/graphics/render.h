#pragma once

#include <QOpenGLExtraFunctions>
#include <QOpenGLFunctions_4_3_Core>
#include "lc_client/eng_graphics/i_render.h"
#include <QOpenGLFramebufferObject>
#include <QOpenGLDebugMessage>
#include "opengl_debugger.h"

#include <memory>

class Render : public IRender,  protected QOpenGLExtraFunctions
{

public:
    Render(int width, int height, float fov);

    void init();
    void render();
    void clear();
    void cleanUp();
    int getFramebufferTexture();

private:
    unsigned int m_fbo;

    int m_width;
    int m_height;
    float m_fov;

    unsigned int m_texture;

    int shaderProgram;
    unsigned int VAO;

    int m_i = 0;

    OpenGLDebugger* m_pDebugger = nullptr;
};

