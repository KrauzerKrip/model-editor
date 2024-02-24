#pragma once

#include "lc_client/eng_input/i_input.h"

class Input : public IInput
{
public:
    Input();

    bool isKeyPressed(std::string key);
    double getMousePosX();
    double getMousePosY();
    void addKeyCallback(std::string key, std::function<void()> callback);
};

