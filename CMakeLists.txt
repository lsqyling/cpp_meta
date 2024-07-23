cmake_minimum_required(VERSION 3.20)

project(cpp_meta VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

if (MSVC)
    add_compile_options("/utf-8")
endif ()
if (WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif ()

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "build type" FORCE)
endif ()
message(STATUS "build type: ${CMAKE_BUILD_TYPE}")

# generate library
add_library(meta INTERFACE)
add_library(meta::meta ALIAS meta)
target_include_directories(meta
        INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)


add_subdirectory(test)

#install dir
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_LIST_DIR}/install)
message(STATUS "Installed directory: ${CMAKE_INSTALL_PREFIX}")

set(meta_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
include(cmake/install.cmake)
install(FILES README.md LICENSE
        DESTINATION doc)
