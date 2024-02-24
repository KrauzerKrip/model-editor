#pragma once


#include "i_eng_resource.h"

// #include <cmrc/cmrc.hpp>
#include <string>

namespace eng {

	class Resource : public IResource {
	public:
		/**
		 * \param resourceRootPath - root path of resource dir (ends with /).
		 */
		Resource(std::string resourceRootPath);

		//auto getFile(std::string path) const -> cmrc::file;

		/**
		 * \brief A good choice will be to use it for directories iteration.
		 */
		//auto getFileSystem() const -> cmrc::embedded_filesystem;

		auto getFileResource(std::string path) const -> std::vector<unsigned char>;

		auto getFileResources(std::vector<std::string>& paths) const -> std::vector<std::vector<unsigned char>>;

	private:
		std::string m_resourceRootPath;
	};
}
