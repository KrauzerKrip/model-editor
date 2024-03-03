#pragma once

#include <tuple>
#include <string>

#include <entt/entt.hpp>

#include "lc_client/util/i_eng_resource.h"
#include "lc_client/eng_physics/physics_parser.h"
#include "project.h"
#include "file_work/file_writer.h"


enum class ToolMode {
	SELECT,
	MOVE,
	ROTATE,
	SCALE
};

class Editor {
public:
	Editor(
		entt::registry* pRegistry, eng::IResource* pResource, FileWriter* pFileWriter, PhysicsParser* pPhysicsParser);

	Project& getProject();
	void loadModel();
	std::vector<std::tuple<std::string, std::string>> getPackModels(std::string pack);
	void setToolMode(ToolMode mode);
	ToolMode getToolMode();
	void createCollider(ColliderType type);

private:
	IPackEditor* m_pPackEditor = nullptr;
	Project m_project;
	ToolMode m_toolMode;

	/**
	 * @brief Workaround. Needed because core physics.h getIntersections() adds collider (here m_utilColliderEntity) transform and owner transform.
	 */
	entt::entity m_utilColliderEntity;

	entt::registry* m_pRegistry = nullptr;
};