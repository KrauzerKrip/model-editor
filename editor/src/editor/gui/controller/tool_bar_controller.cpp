#include "tool_bar_controller.h"

ToolBarController::ToolBarController(ToolBar& taskBar) : m_taskBar(taskBar) {}

void ToolBarController::update() { m_taskBar.getActive(); }

