project(model)

target_sources(app PRIVATE
    "project.h"
    "project.cpp"
    "file_work/i_saver.h"
    "file_work/i_loader.h"
    "file_work/i_creator.h"
)
