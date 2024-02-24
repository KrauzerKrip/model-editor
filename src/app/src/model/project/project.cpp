#include "project.h"

Project::Project(ISaver* pSaver, ILoader* pLoader, ICreator* pCreator)
{
    m_pSaver = pSaver;
    m_pLoader = pLoader;
    m_pCreator = pCreator;
}
