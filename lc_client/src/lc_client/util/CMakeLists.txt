cmake_minimum_required (VERSION 3.13)

project(util)

target_sources(lc_client 
    PRIVATE
        "i_eng_resource.h"
        "eng_resource.cpp"
        "eng_resource.h"
        "directories.h"
        "directories.cpp"
        "file_util.h"
        "file_util.cpp"
        "image.h"
        "image.cpp"
        "pack.h"
        "pack.cpp"
        "timer.h"
        "timer.cpp"
)