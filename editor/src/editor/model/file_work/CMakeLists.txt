cmake_minimum_required(VERSION 3.13)

project(model_file_work)

target_sources(editor PRIVATE
	"i_project_creator.h"
	"i_project_loader.h"
	"i_project_saver.h"
	"project_creator_xml.h"
	"project_creator_xml.cpp"
	"project_saver_xml.h"
	"project_saver_xml.cpp"

	"i_pack_editor.h"
	"pack_editor_json.h"
	"pack_editor_json.cpp"

	"project_data.h"

	"file_writer.h"
	"file_writer.cpp"
)