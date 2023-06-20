cmake_minimum_required(VERSION 3.25)

project(Engine CXX)

file(GLOB_RECURSE implementations implementations/*.cpp)
set(implementations_dir "implementations")
set(third_party ${CMAKE_SOURCE_DIR}/Modules)

set(sources
	src/startup/startup.cpp
	src/graphics/graphics.cpp
	src/graphics/context.cpp
	src/graphics/window.cpp
	src/graphics/shader.cpp
	src/graphics/mesh.cpp
	src/graphics/vertex_array.cpp
	src/graphics/buffer_object.cpp
	src/common/logger.cpp
	src/common/logger_provider.cpp
	src/common/verify.cpp
	src/processing/background_service.cpp)

file(GLOB_RECURSE headers include/*.hpp)
file(GLOB_RECURSE headers_implementations implementations/*.hpp)

add_library(${PROJECT_NAME} STATIC ${sources} ${implementations} ${headers} ${headers_implementations})
target_include_directories(${PROJECT_NAME} PUBLIC include PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${implementations_dir} ${third_party} ${third_party}/glm)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw glad fmt::fmt spdlog::spdlog glm::glm tinyobjloader)

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -Wpedantic -Wno-volatile -Wno-unused-function)
endif()

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -Wpedantic -Wno-unused-function)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
	target_compile_definitions(${PROJECT_NAME} PRIVATE RELEASE_BUILD)
endif()
