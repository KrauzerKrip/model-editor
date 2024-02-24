#pragma once

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QOpenGLWindow>
#include <QOpenGLFunctions_4_3_Core>
#include "model/viewer_thread.h"
#include <QOpenGLDebugMessage>
#include <QOpenGLExtraFunctions>

class ViewerThread;

class Viewer : public QOpenGLWindow, QOpenGLExtraFunctions
{

    Q_OBJECT

public:
    Viewer();
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

public slots:
    void debugMessage(const QOpenGLDebugMessage &debugMessage);

private:
    ViewerThread* m_pViewerThread = nullptr;
    unsigned int m_shaderProgram;
    unsigned int m_framebufferVao;

    bool isInited = false;
};
