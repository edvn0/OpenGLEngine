cmake_minimum_required(VERSION 3.26)

project(Engine CXX C)

file(GLOB_RECURSE implementations implementations/*.cpp)
set(implementations_dir "implementations")
set(third_party ${CMAKE_SOURCE_DIR}/Modules)

set(sources
	src/startup/startup.cpp
	src/graphics/graphics.cpp
	src/graphics/context.cpp
	src/graphics/window.cpp
	src/graphics/shader.cpp
	src/common/logger.cpp
	src/common/logger_provider.cpp
	src/common/verify.cpp
	src/processing/background_service.cpp
	${third_party}/glad/glad.c)

file(GLOB_RECURSE headers include/*.hpp)
file(GLOB_RECURSE headers_implementations implementations/*.hpp)

add_library(${PROJECT_NAME} STATIC ${sources} ${implementations} ${headers} ${headers_implementations})
target_include_directories(${PROJECT_NAME} PUBLIC include PRIVATE ${implementations_dir} ${third_party} ${third_party}/glad ${third_party}/glm)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw fmt::fmt spdlog::spdlog glm::glm)

if((${CMAKE_CXX_COMPILER_ID} MATCHES "Clang") OR(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU"))
	target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
	target_compile_definitions(${PROJECT_NAME} PRIVATE RELEASE_BUILD)
endif()
