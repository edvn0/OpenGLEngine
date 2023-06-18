cmake_minimum_required(VERSION 3.26)

project(Application CXX)

set(third_party ${CMAKE_SOURCE_DIR}/Modules)

set(sources src/main.cpp src/my_layer.cpp)
file(GLOB_RECURSE headers include/*.hpp)

add_executable(${PROJECT_NAME} ${sources} ${headers})
target_link_libraries(${PROJECT_NAME} PRIVATE Engine)
target_include_directories(${PROJECT_NAME} PRIVATE include ${third_party} ${third_party}/glfw/include ${third_party}/glm)

if((${CMAKE_CXX_COMPILER_ID} MATCHES "Clang") OR(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU"))
	target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
	target_compile_definitions(${PROJECT_NAME} PRIVATE RELEASE_BUILD)
endif()
