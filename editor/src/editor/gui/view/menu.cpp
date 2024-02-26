#include "menu.h"

#include <imgui.h>


using namespace ImGui;


void Menu::frame() {
	SetNextWindowPos(ImVec2(-1, 0));
	SetNextWindowSize(ImVec2(1922, 54));

	if (BeginMainMenuBar()) {
		if (BeginMenu("File")) {
			if (MenuItem("New")) {}
			if (MenuItem("Open")) {}
			Separator();
			if (MenuItem("Save")) {}
			if (MenuItem("Save as")) {}

			EndMenu();
		}
		EndMainMenuBar();
	}
}
