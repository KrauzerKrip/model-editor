#pragma once

#include <string>

class ICreator
{
protected:
    virtual ~ICreator() = default;

public:
    ICreator& operator=(const ICreator&) = delete;

    virtual void create(std::string path) = 0;
};
