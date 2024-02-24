#pragma once

#include <string>

#include "background.h"
#include "lc_client/eng_graphics/texture.h"
#include "lc_client/eng_gui/widgets/dependencies.h"


class ImageBackground : public Background {
public:
	ImageBackground(std::string path, GuiDependencies dependencies);

	void render(const Rectangle& rectangle, const Layer& layer) override;

private:
	GuiDependencies m_dependencies;

	Texture* m_pTexture = nullptr;
	BackgroundRender* m_pBackgroundRender = nullptr;
};
