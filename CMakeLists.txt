SET(ENGINE_NAME "EdgaEngine2D")
SET(DEVELOPERS "CurrentUser")

message("This cmake file for building " ${ENGINE_NAME} "developers:" ${DEVELOPERS} )
message("Required min version 3.20")

cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(${ENGINE_NAME})
add_executable(${ENGINE_NAME} src/main.cpp)

# Settings for glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(external/glfw)
target_link_libraries(${ENGINE_NAME} glfw)
add_subdirectory(external/glad)
target_link_libraries(${ENGINE_NAME} GLAD)