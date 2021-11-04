#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
class Shaders {
private:
	const GLchar* vertice_shader_src;
	const GLchar* fragment_shader_src;
	GLuint vertex_shader;
	GLuint fragment_shader;
	GLuint shader_program;
public:
	enum shader_type {
		VERTICE,
		FRAGMENT
	};

	Shaders();
	void CreateShader(shader_type);
	void CompileShader(shader_type);
	void CompileError(GLuint &shader);
	void CreateProgram();
	void UseProgram();
	void DeleteShaders();
	GLuint GetShaderProgram();
	void ShaderProgramError(GLuint& shader);
};