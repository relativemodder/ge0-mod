cmake_minimum_required(VERSION 3.14)

set(CMAKE_TOOLCHAIN_FILE "C:/Program Files/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(ge0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32) # Install dlls in the same directory as the executable on Windows
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

set(DEFAULT_BUILD_TYPE "Release" "RelWithDebInfo")

include_directories("C:/Program Files/vcpkg/installed/x86-windows/include")
link_directories("C:/Program Files/vcpkg/installed/x86-windows/lib")

add_library(ge0 SHARED src/main.cpp "src/utils/origs.hpp" "src/layers/EditLevelLayer.h" "src/utils/hooking.hpp"  "src/utils/linkutils.hpp"      "src/pch.hpp")

include(cmake/CPM.cmake)

CPMAddPackage("gh:relativemodder/mat-dash#3a3b639")
CPMAddPackage("gh:HJfod/cocos-headers#1ec524e")
CPMAddPackage("gh:HJfod/gd.h#056e90e")
CPMAddPackage("gh:HJfod/minhook#44b326e")
CPMAddPackage("gh:BepInEx/Dobby#1321565")

target_compile_definitions(ge0 PRIVATE CC_DLL=)

target_include_directories(ge0 PRIVATE
    ${gd.h_SOURCE_DIR}/include ${gd.h_SOURCE_DIR}
    ${minhook_SOURCE_DIR}/include
)

target_link_libraries(ge0 PRIVATE mat-dash cocos2d minhook dobby cpr)
