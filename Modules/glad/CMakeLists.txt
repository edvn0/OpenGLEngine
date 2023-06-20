cmake_minimum_required(VERSION 3.25)

project(glad C)

add_library(glad STATIC glad.c)
target_include_directories(glad PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

