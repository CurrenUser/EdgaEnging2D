#include "Shaders.h"

Shaders::Shaders() {
	vertice_shader_src = "#version 460 core\n"
		"layout (location = 0) in vec3 position;\n"
		"uniform float size;\n"
		"void main() {\n"
		"gl_Position = vec4(size * position.x, size * position.y, size * position.z, 1.0);\n"
		"}\n\0";

	fragment_shader_src = "#version 460 core\n"
		"out vec4 frag_color;\n"
		"uniform vec4 color;\n"
		"void main() {\n"
		"frag_color = color;\n"
		"}\n\0";
}

void Shaders::CreateShader(shader_type shader_type) {
	switch (shader_type)
	{
	case Shaders::VERTICE:
		vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		break;
	case Shaders::FRAGMENT:
		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	default:
		break;
	}
}

void Shaders::CompileShader(shader_type shader_type) {

  switch (shader_type) {
	case Shaders::VERTICE:
		glShaderSource(vertex_shader, 1, &vertice_shader_src, nullptr);
		glCompileShader(vertex_shader);
		CompileError(vertex_shader);
		break;
	case Shaders::FRAGMENT:
		glShaderSource(fragment_shader, 1, &fragment_shader_src, nullptr);
		glCompileShader(fragment_shader);
		CompileError(fragment_shader);
		break;
	default:
		break;
  }

}

void Shaders::CreateProgram() {
	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);
	ShaderProgramError(shader_program);
}

void Shaders::UseProgram() {
	glUseProgram(shader_program);
}

void Shaders::DeleteShaders() {
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

GLuint Shaders::GetShaderProgram() {
	return shader_program;
}

void Shaders::CompileError(GLuint &shader) {
	GLint error_compile;
	GLchar log[512];

	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &error_compile);
	if (!error_compile) {
		glGetShaderInfoLog(shader, 512, nullptr, log);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << log << std::endl;
	}

}

void Shaders::ShaderProgramError(GLuint& program) {
	GLint error_compile;
	GLchar log[512];

	glGetProgramiv(program, GL_COMPILE_STATUS, &error_compile);
	if (!error_compile) {
		glGetProgramInfoLog(program, 512, nullptr, log);
		std::cout << "ERROR::Program::COMPILATION_FAILED\n" << log << std::endl;
	}

}