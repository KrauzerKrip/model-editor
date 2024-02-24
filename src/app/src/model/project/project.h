#pragma once

#include <string>

#include "file_work/i_creator.h"
#include "file_work/i_loader.h"
#include "file_work/i_saver.h"

class Project
{
public:
    Project(ISaver* pSaver, ILoader* pLoader, ICreator* pCreator);

    void load(std::string path);
    void save();
    void saveAs(std::string path);

private:
    std::string m_path;
    ISaver* m_pSaver = nullptr;
    ILoader* m_pLoader = nullptr;
    ICreator* m_pCreator = nullptr;
};
