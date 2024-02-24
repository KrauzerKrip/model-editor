#include "opengl_debugger.h"

#include <iostream>

OpenGLDebugger::OpenGLDebugger(QOpenGLDebugLogger* pLogger)
    : QObject()
{
        connect(pLogger, &QOpenGLDebugLogger::messageLogged, this, &OpenGLDebugger::debugMessage);
}

void OpenGLDebugger::debugMessage(const QOpenGLDebugMessage &debugMessage)
{
        std::cerr << "Render: " << debugMessage.message().toStdString() << std::endl;
}
