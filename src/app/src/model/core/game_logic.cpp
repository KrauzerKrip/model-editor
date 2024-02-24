#include "game_logic.h"

GameLogic::GameLogic(IWindow* pWindow, Tier0* pTier0) {
    m_pRender = new Render(pWindow->getSize().at(0), pWindow->getSize().at(1), pWindow->getFov());
}

void GameLogic::init() {
    m_pRender->init();
}

void GameLogic::input() {}

void GameLogic::update() {}

void GameLogic::render() {
    m_pRender->render();
    m_framebufferTexture = m_pRender->getFramebufferTexture();
}

void GameLogic::cleanUp() {}

int GameLogic::getFramebufferTexture()
{
    return m_framebufferTexture;
}
