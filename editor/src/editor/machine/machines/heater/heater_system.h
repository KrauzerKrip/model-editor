#pragma once

#include "editor/machine/base_machine_system.h"


class HeaterSystem : public BaseMachineSystem {
public:
	HeaterSystem(entt::registry* pRegistry, PhysicalConstants* pPhysicalConstants);

	void frame(float deltaTime) override;
	void machineUpdate(float deltaTime) override;
};