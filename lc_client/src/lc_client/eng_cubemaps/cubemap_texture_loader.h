#pragma once

#include <string>
#include <memory>

#include "lc_client/util/image.h"
#include "lc_client/util/eng_resource.h"


struct CubemapMaterial {
	eng::Image right;
	eng::Image left;
	eng::Image top;
	eng::Image bottom;
	eng::Image back;
	eng::Image front;
	
	CubemapMaterial(eng::Image right, eng::Image left, eng::Image top, eng::Image bottom, eng::Image back, eng::Image front) 
		: right(right),
		  left(left),
		  top(top),
		  bottom(bottom),
		  back(back),
		  front(front) {}

	CubemapMaterial(CubemapMaterial&& material) noexcept
		: right(std::move(material.right)),
		  left(std::move(material.left)),
		  top(std::move(material.top)),
		  bottom(std::move(material.bottom)),
		  back(std::move(material.back)),
		  front(std::move(material.front)) {}
};

class CubemapTextureLoader {
public:
	CubemapTextureLoader(std::string path, eng::IResource* pResource);

	std::unique_ptr<CubemapMaterial> getMaterial();

private:
	CubemapMaterial* m_pMaterial;

	void testLoadImages(eng::IResource* pResource, std::string path);

	const static std::string FILE_FORMAT;
};
