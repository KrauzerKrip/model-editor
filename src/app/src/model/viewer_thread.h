#pragma once

#include <QObject>
#include <QThread>
#include <QOpenGLFunctions_4_3_Core>
#include <QOffscreenSurface>
#include "core/graphics/viewer.h"

class Viewer;
/*
    ViewerThread calls update() of Viewer (asks for paintGL) but before it renders on framebuffer texture. Viewer shows this framebuffer texture.
*/
class ViewerThread : public QThread, protected QOpenGLFunctions_4_3_Core
{
    Q_OBJECT

public:
    QOffscreenSurface *m_surface = nullptr;
    QOpenGLContext *m_context = nullptr;

    ViewerThread(Viewer* pViewer)
    {
        m_context = new QOpenGLContext();
        m_surface = new QOffscreenSurface();
        m_pViewer = pViewer;
    }

    int getFramebufferTexture();

public slots:
    void initializeGL()
    {
        m_context->makeCurrent(m_surface);
        initializeOpenGLFunctions();

        glViewport(0, 0, 1920, 1080);
        glClearColor(0 / 255, 0 / 255, 255 / 255, 1.0f);
    }

protected:
    void run();

signals:
    void updateViewer();

private:
    void printException(const std::exception& e, int level = 0);

    QThread m_thread;
    Viewer* m_pViewer;
    int m_framebufferTexture;
};
