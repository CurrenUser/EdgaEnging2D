#include "Shaders.h"

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

void Shaders::CompileShader(shader_type shader_type, std::string src_shader_path ) {

Loader::Loader loader;
std::string shader_src_str = loader.LoadShaderSrc(src_shader_path);
const char* shader_src = shader_src_str.c_str();

  switch (shader_type) {
	case Shaders::VERTICE:
		glShaderSource(vertex_shader, 1, &shader_src, nullptr);
		glCompileShader(vertex_shader);
		CompileError(vertex_shader);
		break;
	case Shaders::FRAGMENT:
		glShaderSource(fragment_shader, 1, &shader_src, nullptr);
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

void Shaders::SetUniForm1f(float f, std::string name) {
	glUniform1f(glGetUniformLocation(shader_program, name.c_str()), f);
}

void Shaders::SetUniForm4f(float x, float y, float z, float w, std::string name) {
	glUniform4f(glGetUniformLocation(shader_program, name.c_str()), x, y, z, w);
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