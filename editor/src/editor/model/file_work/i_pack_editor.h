#pragma once

#include <string>
#include <tuple>
#include <vector>


class IPackEditor {
public:
	virtual void addModel(std::string pack, std::string name) = 0;
	virtual std::vector<std::tuple<std::string, std::string>> getPackModels(std::string pack) = 0;
};