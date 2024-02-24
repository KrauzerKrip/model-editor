#pragma once

#include <functional>

#include "core/game.h"
#include "editor_mode_handler.h"
#include "project/project.h"
#include <QObject>
#include <QThread>

class Editor
{

public:
    Editor(Viewer* pViewer);

    Viewer* getViewer();
    EditorModeHandler& getModeHandler();
    void activateViewer();

private:
    EditorModeHandler m_modeHandler;
    Project* m_pProject = nullptr;
    Game* m_pGame = nullptr;
    Viewer* m_pViewer = nullptr;
    QThread* m_pViewerThread;
};
