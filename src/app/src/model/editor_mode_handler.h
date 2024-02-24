#pragma once

#include <functional>

enum class EditorMode { SELECT, MOVE, ROTATE, CREATE_ENTITY };

class EditorModeHandler
{
public:
    EditorModeHandler();

    void setMode(EditorMode mode);
    void setModeChangeCallback(std::function<void(EditorMode mode)> callback);
    EditorMode getMode();

private:
    EditorMode m_mode;
    std::function<void(EditorMode mode)> m_callback;
};
