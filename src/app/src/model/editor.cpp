#include "editor.h"

#include <thread>
#include <qthread.h>

#include <model/project/file_work/i_creator.h>
#include <model/project/file_work/i_loader.h>
#include <model/project/file_work/i_saver.h>
#include <qassert.h>

#include "viewer_thread.h"

Editor::Editor(Viewer* pViewer)
{
    ICreator* pCreator = nullptr;
    ILoader* pLoader = nullptr;
    ISaver* pSaver = nullptr;

    m_pProject = new Project(pSaver, pLoader, pCreator);


    /*
        1. Create Viewer => create context
        2. Show Viewer, though let all app be shown
        3. Move Viewer and it`s context to a separate thread
    */

    m_pViewer = pViewer;
}

EditorModeHandler& Editor::getModeHandler()
{
    return m_modeHandler;
}

void Editor::activateViewer()
{
    //m_pViewer->initializeGL();
}
