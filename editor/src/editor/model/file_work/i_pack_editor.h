#pragma once

#include <string>


class IPackEditor {
public:
	virtual void addModel(std::string name) = 0;
};