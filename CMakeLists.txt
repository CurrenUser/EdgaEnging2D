message("Required min version 3.20")
cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

#VARIABLES
SET(ENGINE_NAME "EdgaEngine2D")
SET(DEVELOPERS "CurrentUser")

SET(SOURCES
	src/Renderer/Shaders.cpp
	src/Loader/Loader.cpp 
	src/main.cpp
	src/imgui/imgui_widgets.cpp
	src/imgui/imgui.cpp            
	src/imgui/imgui_impl_opengl3.cpp  
	src/imgui/imgui_demo.cpp       
	src/imgui/imgui_draw.cpp       
	src/imgui/imgui_impl_glfw.cpp  
	src/imgui/imgui_tables.cpp
)

SET(HEADERS
	src/Renderer/Shaders.h 
	src/Loader/Loader.h
	src/imgui/imconfig.h           
	src/imgui/imgui_impl_glfw.h
	src/imgui/imstb_rectpack.h
	src/imgui/imgui.h              
	src/imgui/imgui_impl_opengl3.h         
	src/imgui/imstb_textedit.h
	src/imgui/imgui_impl_opengl3_loader.h  
	src/imgui/imstb_truetype.h
	src/imgui/imgui_internal.h
)


message("This cmake file for building " ${ENGINE_NAME} "developers:" ${DEVELOPERS} )
message("CMAKE_CURRENT_BINARY_DIR:"${CMAKE_CURRENT_BINARY_DIR})
message("CMAKE_CURRENT_SOURCE_DIR:"${CMAKE_CURRENT_SOURCE_DIR})

#PROJECT
project(${ENGINE_NAME} VERSION 0.0.1)
add_executable(${ENGINE_NAME} ${SOURCES} ${HEADERS})
set_target_properties(${ENGINE_NAME} PROPERTIES
					  CXX_STANDARD 11
					  CXX_STANDARD_REQUIRED ON
					  )

# SETTINGS FOR GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(external/glfw)
target_link_libraries(${ENGINE_NAME} glfw)

# SETTINGS FOR GLAD
add_subdirectory(external/glad)
target_link_libraries(${ENGINE_NAME} GLAD)

add_custom_command(TARGET ${ENGINE_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/resources/ ${PROJECT_BINARY_DIR})