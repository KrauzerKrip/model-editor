#include "editor.h"

#include "file_work/project_creator_xml.h"
//#include "file_work/project_loader_xml.h"
#include "file_work/project_saver_xml.h"


Editor::Editor(entt::registry* pRegistry, eng::IResource* pResource)
	: m_project("E:/Industry/industry/res/game/models", new ProjectCreatorXml(pResource), nullptr, nullptr, pRegistry) {}

Project& Editor::getProject() { return m_project; }