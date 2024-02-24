#include "viewer_thread.h"

#include "core/game.h"
#include <iostream>
#include <string>

#include "core/game_logic.h"
#include "core/graphics/window.h"
#include "core/graphics/viewer.h"
#include "lc_client/eng_graphics/i_window.h"
#include "lc_client/tier0/tier0.h"

int ViewerThread::getFramebufferTexture()
{
    return m_framebufferTexture;
}

void ViewerThread::run() {
    std::string title = "Local` Engine";
    // int width = 1080;
    // int height = 720;
    int width = 1280;
    int height = 720;
    bool vSync = true;

    int targetFPS = 60;
    int targetUPS = 60;

    Tier0* pTier0 = nullptr;

    Window* pWindow = nullptr;
    GameLogic* pGameLogic = nullptr;

    try {
        Tier0* pTier0 = new Tier0();
        std::array<int, 2> aspectRatio = std::array<int, 2>({{16, 9}});
        pWindow = new Window(m_pViewer, width, height, aspectRatio, vSync, 45.0);
        pGameLogic = new GameLogic(pWindow, pTier0);
        //Loop* pLoop = Loop::createInstance(pWindow, pGameLogic, targetFPS, targetUPS);

        //pLoop->init();
        pWindow->init();
        pGameLogic->init();
        //pLoop->startLoop();
        //double lastTime = 0.0;

        //float deltaTime = 0.0f;

        while (!pWindow->windowShouldClose()) {
            //double currentTime = glfwGetTime();
            //deltaTime = currentTime - lastTime;
            //lastTime = currentTime;
            //Time::m_deltaTime = deltaTime;

            pWindow->startFrame();
            pGameLogic->input();

            pGameLogic->update();

            m_context->makeCurrent(m_surface);
            pGameLogic->render();
            m_framebufferTexture = pGameLogic->getFramebufferTexture();
            m_context->doneCurrent();
            //pWindow->update();
            emit updateViewer();
        }

        pWindow->terminate(); // mb in loop
    } catch (std::runtime_error& exception) {
        printException(exception);
        exit(-1);
    }

    if (pWindow) {
        delete pWindow;
    }
    if (pGameLogic) {
        delete pGameLogic;
    }
    if (pTier0) {
        delete pTier0;
    }
}



void ViewerThread::printException(const std::exception& e, int level)
{
    std::cerr << std::string(level, ' ') << "Exception: " << e.what() << '\n';
    try {
        std::rethrow_if_nested(e);
    } catch (const std::exception& nestedException) {
        printException(nestedException, level + 1);
    } catch (...) {
    }
}

