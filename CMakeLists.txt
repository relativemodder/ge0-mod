cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ge0)

add_library(ge0 SHARED src/main.cpp)

include(cmake/CPM.cmake)

CPMAddPackage("gh:matcool/mat-dash#294126a")
CPMAddPackage("gh:HJfod/cocos-headers#1ec524e")
CPMAddPackage("gh:HJfod/gd.h#056e90e")
CPMAddPackage("gh:TsudaKageyu/minhook#4a45552")

target_compile_definitions(ge0 PRIVATE CC_DLL=)

target_include_directories(ge0 PRIVATE
    ${gd.h_SOURCE_DIR}/include ${gd.h_SOURCE_DIR}
    ${minhook_SOURCE_DIR}/include
)

target_link_libraries(ge0 mat-dash cocos2d minhook)
