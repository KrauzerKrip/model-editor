#include "editor.h"

#include "file_work/project_creator_xml.h"
#include "file_work/project_loader_xml.h"
#include "file_work/project_saver_xml.h"
#include "file_work/pack_editor_json.h"

#include "lc_client/eng_model/entt/components.h"


Editor::Editor(
	entt::registry* pRegistry, eng::IResource* pResource, FileWriter* pFileWriter, PhysicsParser* pPhysicsParser)
	: m_pPackEditor(new PackEditorJson(pResource, pFileWriter)),
	  m_project(new ProjectCreatorXml(pResource, pFileWriter), new ProjectLoaderXml(pResource, pPhysicsParser),
		  new ProjectSaverXml(pResource, pFileWriter),
		  m_pPackEditor, pRegistry) {
	m_pRegistry = pRegistry;
	m_toolMode = ToolMode::SELECT;
}

Project& Editor::getProject() { return m_project; }

void Editor::loadModel() { 
	auto entity = m_pRegistry->create();
	m_pRegistry->emplace<Transform>(entity, Transform());
	m_pRegistry->emplace<ModelRequest>(entity, ModelRequest(m_project.getPack(), m_project.getName(), false));
	m_pRegistry->emplace<ShaderRequest>(entity, ShaderRequest("dev", "base", "base_material"));
}

std::vector<std::tuple<std::string, std::string>> Editor::getPackModels(std::string pack) {
	return m_pPackEditor->getPackModels(pack);
}

void Editor::setToolMode(ToolMode mode) {
	m_toolMode = mode; 
}

ToolMode Editor::getToolMode() { return m_toolMode; }

void Editor::createCollider(ColliderType type) { 
	auto entity = m_pRegistry->create();
	auto modelEntities = m_pRegistry->view<Colliders>();

	m_pRegistry->emplace<Transform>(entity);

	if (type == ColliderType::BOX) {
		m_pRegistry->emplace<BoxCollider>(entity);
	}

	for (auto&& [ent, colliders] : modelEntities.each()) {
		colliders.colliders.push_back(std::make_tuple(entity, type));
	}
}
