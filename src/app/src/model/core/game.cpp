#include "game.h"

#include <iostream>
#include <string>

#include "game_logic.h"
#include "lc_client/eng_graphics/i_window.h"
#include "graphics/window.h"
#include "lc_client/loop.h"
#include "lc_client/tier0/tier0.h"
#include "graphics/viewer.h"

Game::Game(Viewer* pViewer)
{
    std::string title = "Local` Engine";
    // int width = 1080;
    // int height = 720;
    int width = 1920;
    int height = 1080;
    bool vSync = true;

    int targetFPS = 60;
    int targetUPS = 60;

    Tier0* pTier0 = nullptr;

    IWindow* pWindow = nullptr;
    IGameLogic* pGameLogic = nullptr;
    Loop* pLoop = nullptr;

    try {
        Tier0* pTier0 = new Tier0();
        std::array<int, 2> aspectRatio = std::array<int, 2>({{16, 9}});
        pWindow = new Window(pViewer, width, height, aspectRatio, vSync, 45.0);
        IGameLogic* pGameLogic = new GameLogic(pWindow, pTier0);
        Loop* pLoop = Loop::createInstance(pWindow, pGameLogic, targetFPS, targetUPS);

        pLoop->init();
        pLoop->startLoop();

        pLoop->cleanUp();
        pWindow->terminate(); // mb in loop
    } catch (std::runtime_error& exception) {
        printException(exception);
        exit(-1);
    }

    if (pLoop) {
        delete pLoop;
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

    exit(0);
}

void Game::printException(const std::exception& e, int level)
{
    std::cerr << std::string(level, ' ') << "Exception: " << e.what() << '\n';
    try {
        std::rethrow_if_nested(e);
    } catch (const std::exception& nestedException) {
        printException(nestedException, level + 1);
    } catch (...) {
    }
}
