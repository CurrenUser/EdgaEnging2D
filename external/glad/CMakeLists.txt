message("Required min version 3.20")
cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(GLAD)
add_library(GLAD STATIC include/glad/glad.h src/glad.c)
target_include_directories(GLAD PUBLIC include/)