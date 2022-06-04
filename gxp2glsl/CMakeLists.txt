cmake_minimum_required(VERSION 3.22)

project(gxp2glsl)

set(CMAKE_CXX_STANDARD 17)
set(STANDARD_NUM 17)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include PUBLIC)
include_directories(../external/rpcs3/include PUBLIC)
include_directories(../vita3k/util/include PUBLIC)


set(SPIRV_CROSS_CLI OFF CACHE BOOL "")
set(SPIRV_CROSS_ENABLE_TESTS OFF CACHE BOOL "")
set(SPIRV_CROSS_ENABLE_HLSL OFF CACHE BOOL "")
set(SPIRV_CROSS_ENABLE_MSL OFF CACHE BOOL "")
set(SPIRV_CROSS_ENABLE_CPP OFF CACHE BOOL "")
set(SPIRV_CROSS_ENABLE_REFLECT OFF CACHE BOOL "")
add_subdirectory(../external/SPIRV-Cross SPIRV-Cross)
add_subdirectory(../external/glslang glslang)

add_subdirectory(../vita3k/features features)
add_subdirectory(../vita3k/gxm gxm)

add_compile_definitions(VITA3K_CPP17)
add_subdirectory(../vita3k/shader shader)
set_target_properties(shader-tests PROPERTIES EXCLUDE_FROM_ALL True)


add_executable(gxp2glsl main.cpp)

target_include_directories(gxp2glsl PUBLIC ../vita3k/features/include)
target_include_directories(gxp2glsl PUBLIC ../vita3k/shader/include)
target_include_directories(gxp2glsl PUBLIC ../vita3k/gxm/include)
target_include_directories(gxp2glsl PUBLIC ../external/SPIRV-Cross)

target_link_libraries(gxp2glsl shader)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fdiagnostics-color=always")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fdiagnostics-color=always")


add_library(spdlog empty.c)
add_library(rpcs3 empty.c)
add_library(fmt log.cpp fs.cpp)
