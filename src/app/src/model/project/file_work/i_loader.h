#pragma once

#include <string>

class ILoader
{
protected:
    virtual ~ILoader() = default;

public:
    ILoader& operator=(const ILoader&) = delete;

    virtual void load(std::string path) = 0;
};
