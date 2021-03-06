//
// Created by Ronan on 11/01/2021.
//
#include "iostream"
#include "Shader.h"
#include "Helpers/FileHelper.h"


Shader::Shader(const std::string &name) {
	_id = glCreateProgram();
	GLuint vertex = loadShader(name + ".vert", GL_VERTEX_SHADER);
	GLuint fragments = loadShader(name + ".frag", GL_FRAGMENT_SHADER);

	glAttachShader(_id, vertex);
	glAttachShader(_id, fragments);
	glLinkProgram(_id);

	glDetachShader(_id, vertex);
	glDeleteShader(vertex);

	glDetachShader(_id, fragments);
	glDeleteShader(fragments);

	GLint linkSuccess;
	glGetProgramiv(_id, GL_LINK_STATUS, &linkSuccess);

	if (linkSuccess == GL_FALSE) {
		int length;
		glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &length);

		std::string error;
		error.resize(length - 1);
		glGetProgramInfoLog(_id, length, nullptr, error.data());

		throw std::runtime_error("Error while linking shaders to program: " + error);
	}
}

Shader::~Shader() {
	glDeleteProgram(_id);
}

GLuint Shader::loadShader(const std::string &path, GLenum type) {
	GLuint shader = glCreateShader(type);
	std::string source;

	try {
		source = FileHelper::readAllText("resources/shaders/" + path);
	}
	catch (const std::ios_base::failure &e) {
		std::cout << "Unable to open shader file \"" << path << "\"" << std::endl;
		throw e;
	}
	const char *source_c = source.c_str();

	glShaderSource(shader, 1, &source_c, nullptr);
	glCompileShader(shader);

	GLint compileSuccess;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileSuccess);

	if (compileSuccess == GL_FALSE) {
		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

		std::string error;
		error.resize(length - 1);
		glGetShaderInfoLog(shader, length, nullptr, error.data());

		throw std::runtime_error("Error while compiling shader: " + error);
	}
	return shader;
}

void Shader::bind() {
	glUseProgram(_id);
}

GLuint Shader::getId() const {
	return _id;
}
