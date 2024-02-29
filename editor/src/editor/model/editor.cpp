#include "editor.h"

#include "file_work/project_creator_xml.h"
//#include "file_work/project_loader_xml.h"
#include "file_work/project_saver_xml.h"
#include "file_work/pack_editor_json.h"


Editor::Editor(entt::registry* pRegistry, eng::IResource* pResource, FileWriter* pFileWriter)
	: m_project(new ProjectCreatorXml(pResource, pFileWriter), nullptr, new ProjectSaverXml(pResource, pFileWriter),
		  new PackEditorJson("game", pResource, pFileWriter), pRegistry) {}

Project& Editor::getProject() { return m_project; }

void Editor::loadModel() {}
