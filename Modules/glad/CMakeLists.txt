cmake_minimum_required(VERSION 3.25)

project(glad C)

add_library(${PROJECT_NAME} STATIC glad.c)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})