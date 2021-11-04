SET(ENGINE_NAME "EdgaEngine2D")
SET(DEVELOPERS "CurrentUser")

message("This cmake file for building " ${ENGINE_NAME} "developers:" ${DEVELOPERS} )
message("Required min version 3.20")

cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(${ENGINE_NAME})
add_executable(${ENGINE_NAME} src/main.cpp 
src/Shaders.h 
src/Shaders.cpp 
src/imgui/imconfig.h           
src/imgui/imgui_impl_glfw.h            
src/imgui/imgui_widgets.cpp
src/imgui/imgui.cpp            
src/imgui/imgui_impl_opengl3.cpp       
src/imgui/imstb_rectpack.h
src/imgui/imgui.h              
src/imgui/imgui_impl_opengl3.h         
src/imgui/imstb_textedit.h
src/imgui/imgui_demo.cpp       
src/imgui/imgui_impl_opengl3_loader.h  
src/imgui/imstb_truetype.h
src/imgui/imgui_draw.cpp       
src/imgui/imgui_internal.h
src/imgui/imgui_impl_glfw.cpp  
src/imgui/imgui_tables.cpp)

# Settings for glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(external/glfw)
target_link_libraries(${ENGINE_NAME} glfw)
add_subdirectory(external/glad)
target_link_libraries(${ENGINE_NAME} GLAD)