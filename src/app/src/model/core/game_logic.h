#pragma once

#include "lc_client/eng_graphics/i_window.h"
#include "lc_client/i_game_logic.h"
#include "lc_client/tier0/tier0.h"
#include "graphics/render.h"

class GameLogic : public IGameLogic
{
public:
    GameLogic(IWindow* pWindow, Tier0* pTier0);

    void init();
    void input();
    void update();
    void render();
    void cleanUp();
    int getFramebufferTexture();

private:
    Render* m_pRender = nullptr;

    int m_framebufferTexture = 0;
};
