#pragma once

#include "lc_client/eng_graphics/i_window.h"
#include <QtGlobal>
#include <array>
#include "viewer.h"

class Window : public IWindow
{
public:
    Window(Viewer* pViewer, int width, int height, std::array<int, 2> aspectRatio, bool vSync, float fov);

    void init();
    void startFrame();
    void update();
    bool windowShouldClose();
    void terminate();
    IInput* getInput();
    void setMode(WindowMode mode);
    WindowMode getMode();
    void setResizeCallback(std::function<void(int, int)> callback);

    /**
     * Breaks encapsulation
     * remove it and
     *
     * DO NOT USE IT
     *
     * NEVER
     *
     * IN THE NAME OF FLANDRE
     * IN THE NAME OF CHRIST
     *
     * DO NOT USE IT
     */
    [[noreturn, deprecated]] GLFWwindow* getGlfwWindow()
    {
        Q_ASSERT_X(false,
                   "model/core/graphics/windows.h",
                   "DO NOT USE getGlfwWindow(). NEVER. IN THE NAME OF FLANDRE. IN THE NAME OF "
                   "CHRIST. DO NOT USE IT.");
        throw "";
    };

    std::array<int, 2> getAspectRatio();
    float getFov();
    void setFov(float fov);
    std::array<int, 2> getSize();

private:
    int m_width;
    int m_height;
    std::array<int, 2> m_pAspectRatio;
    bool m_vSync;
    float m_fov;
    WindowMode m_windowMode;
    Viewer* m_pViewer = nullptr;
};
