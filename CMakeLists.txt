cmake_minimum_required(VERSION 3.25)

project(OpenGLLinux CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Modules)
add_subdirectory(Engine)
add_subdirectory(Application)
