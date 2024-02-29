#include "i_pack_editor.h"

#include "lc_client/util/i_eng_resource.h"
#include "file_writer.h"


class PackEditorJson : public IPackEditor {
public:
	PackEditorJson(eng::IResource* pResource, FileWriter* pFileWriter);

	void addModel(std::string pack, std::string name) override;
	std::vector<std::tuple<std::string, std::string>> getPackModels(std::string pack) override;

private:
	eng::IResource* m_pResource = nullptr;
	FileWriter* m_pFileWriter = nullptr;
};