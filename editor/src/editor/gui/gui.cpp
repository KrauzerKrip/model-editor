#include "gui.h"

#include <imgui.h>

using namespace ImGui;

Gui::Gui(Tier0* pTier0, IInput* pInput, entt::registry* pRegistry) {
	
}

void Gui::frame() {
    SetNextWindowPos(ImVec2(0, 0));
    SetNextWindowSize(ImVec2(1920, 54));

	if (Begin("Window", 0, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoCollapse)) {
        if (BeginMenuBar())
        {
            if (BeginMenu("File"))
            {
                if (MenuItem("New")) {}
                if (MenuItem("Open")) {}
                Separator();
                if (MenuItem("Save")) {}
                if (MenuItem("Save as")) {}

                EndMenu();
            }
            EndMenuBar();
        }

        End();
	}


}
