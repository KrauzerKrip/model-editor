#include "i_pack_editor.h"

#include "lc_client/util/i_eng_resource.h"
#include "file_writer.h"


class PackEditorJson : public IPackEditor {
public:
	PackEditorJson(std::string pack, eng::IResource* pResource, FileWriter* pFileWriter);

	void addModel(std::string name) override;

private:
	std::string m_pack;
	eng::IResource* m_pResource = nullptr;
	FileWriter* m_pFileWriter = nullptr;
};