#pragma once

class ISaver
{
protected:
    virtual ~ISaver() = default;

public:
    ISaver& operator=(const ISaver&) = delete;

    virtual void save() = 0;
};
