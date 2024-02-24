#include "editor_mode_handler.h"

EditorModeHandler::EditorModeHandler() {}

void EditorModeHandler::setMode(EditorMode mode)
{
    m_mode = mode;
    m_callback(mode);
}

void EditorModeHandler::setModeChangeCallback(std::function<void(EditorMode mode)> callback)
{
    m_callback = callback;
}

EditorMode EditorModeHandler::getMode()
{
    return m_mode;
}
