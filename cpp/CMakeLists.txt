cmake_minimum_required(VERSION 3.14)
project(wasm-emscripten-template)

set(CMAKE_CXX_STANDARD 20)

add_definitions(-DWEBGPU_ENABLE)

get_filename_component(PROJECT_PARENT_DIR ${PROJECT_SOURCE_DIR} DIRECTORY)

# 设置输出目录
if ($ENV{WASMENV})
    SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_PARENT_DIR}/lib/wasm)
    SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_PARENT_DIR}/lib/wasm)
    SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_PARENT_DIR}/lib/wasm)
endif()

# 设置编译参数
if ($ENV{WASMENV})
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --bind -O3")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --bind -O3")
endif()

# 定义环境变量相关的宏，用于项目中环境判断
if ($ENV{WASMENV})
    add_definitions(-DBROWSER_ENV)
endif()

add_subdirectory(${PROJECT_SOURCE_DIR}/third_party/glm/glm)
include_directories(${PROJECT_SOURCE_DIR}/third_party/glm)

add_subdirectory(src)
