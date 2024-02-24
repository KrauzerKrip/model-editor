#pragma once

#include "model/core/graphics/viewer.h"
#include <exception>

class Game
{
public:
    Game(Viewer* pViewer);

private:
    void printException(const std::exception& e, int level = 0);
};
