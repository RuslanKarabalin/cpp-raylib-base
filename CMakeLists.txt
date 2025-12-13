cmake_minimum_required(VERSION 3.28)

project(
    cpp_raylib_base
    VERSION 1.0.0
    DESCRIPTION "C++ raylib template"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PROJECT_HEADERS_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_SOURCES_DIR ${PROJECT_SOURCE_DIR}/src)

set(PROJECT_ENTT_HEADERS_DIR ${PROJECT_SOURCE_DIR}/external/entt/include)
set(PROJECT_RAYLIB_HEADERS_DIR ${PROJECT_SOURCE_DIR}/external/raylib/include)

set(PROJECT_RAYLIB_LIB_DIR ${PROJECT_SOURCE_DIR}/external/raylib/lib)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCES_DIR}/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${PROJECT_HEADERS_DIR}
    ${PROJECT_ENTT_HEADERS_DIR}
    ${PROJECT_RAYLIB_HEADERS_DIR}
)

target_link_directories(${PROJECT_NAME} PRIVATE ${PROJECT_RAYLIB_LIB_DIR})

# add link to raylib in current directory
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
# or add raylib to executable
# target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/external/raylib/lib/libraylib.a)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
