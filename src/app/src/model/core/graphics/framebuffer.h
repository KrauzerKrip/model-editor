#pragma once

#include <QOpenGLFramebufferObject>

class Framebuffer : public QOpenGLFramebufferObject
{
public:
    Framebuffer(int width, int height);
};

