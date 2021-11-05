#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include "../Loader/Loader.h"

class Shaders {
private:
	GLuint vertex_shader;
	GLuint fragment_shader;
	GLuint shader_program;
public:
	enum shader_type {
		VERTICE,
		FRAGMENT
	};

	void CreateShader(shader_type);
	void CompileShader(shader_type, std::string);
	void CompileError(GLuint &shader);
	void SetUniForm1f(float, std::string);
	void SetUniForm4f(float, float, float, float, std::string);
	void CreateProgram();
	void UseProgram();
	void DeleteShaders();
	GLuint GetShaderProgram();
	void ShaderProgramError(GLuint& shader);
};