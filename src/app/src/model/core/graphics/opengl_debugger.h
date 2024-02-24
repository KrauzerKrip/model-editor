#pragma once

#include <QObject>
#include <QOpenGLDebugMessage>
#include <QOpenGLDebugLogger>

class OpenGLDebugger : public QObject
{
    Q_OBJECT
public:
    explicit OpenGLDebugger(QOpenGLDebugLogger* pLogger);

signals:

public slots:
        void debugMessage(const QOpenGLDebugMessage &debugMessage);
};

