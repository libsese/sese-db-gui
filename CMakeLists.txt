cmake_minimum_required(VERSION 3.18)
cmake_policy(SET CMP0042 NEW)

include(VcpkgTools.cmake)
sese_auto_find_vcpkg()

project(sese-db-gui)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCE_FILE "${CMAKE_CURRENT_LIST_DIR}/addon/*.cpp")

include_directories(${CMAKE_JS_INC})

add_library(DBExport SHARED ${SOURCE_FILE} ${CMAKE_JS_SRC})
# 必须是全局的头文件位置
# target_link_directories(DBExport PRIVATE ${CMAKE_JS_INC})
target_link_libraries(DBExport PRIVATE ${CMAKE_JS_LIB})

if (WIN32)
  target_link_libraries(DBExport PRIVATE "delayimp.lib")
endif ()

# 依赖处理
execute_process(COMMAND node -p "require('node-addon-api').include"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE NODE_ADDON_API_DIR
)
string(REPLACE "\n" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
string(REPLACE "\"" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
target_include_directories(DBExport PRIVATE ${NODE_ADDON_API_DIR})
add_definitions(-DNAPI_VERSION=6)
add_definitions(-DNAPI_EXPERIMENTAL)
add_definitions(-DNAPI_CPP_EXCEPTIONS)

find_package(sese CONFIG REQUIRED)
target_link_libraries(DBExport PUBLIC Sese::Core)

add_executable(Export addon/Test.cpp)

target_link_libraries(Export PRIVATE DBExport)

set_target_properties(
        Export PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/lib"
)