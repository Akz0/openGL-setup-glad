#pragma once
#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

class Shader
{
private:
	std::string name;
	GLenum shaderType;
	GLuint source;
	std::string shaderCode;

public:
	Shader(GLenum shaderType) {
		this->shaderType = shaderType;
	}
	GLuint* getSource() {
		return &source;
	}
	void readShader(const std::string);
	void compileShader();

	~Shader() {
		glDeleteShader(source);
	}

};

