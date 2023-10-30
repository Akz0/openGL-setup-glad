#pragma once

#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "Shader.h"

class Vertex
{
private:
	GLuint VertexBufferObject;
	GLuint VertexArrayObject;
	GLuint* ShaderPogram;
	Shader* VertexShader;
	Shader* FragmentShader;

public:
	Vertex() {
		VertexShader = new Shader(GL_VERTEX_SHADER);
		FragmentShader = new Shader(GL_FRAGMENT_SHADER);
	}
	void setVertexData(const std::vector<glm::vec3>&);
	void setShaderFiles(std::string VertexPath, std::string FragmentPath);
	void compileShaders();
	void display(GLenum mode, GLint start, GLsizei size);

	void bind() const {
		glBindVertexArray(VertexArrayObject);
	}

	void unbind() const {
		glBindVertexArray(0);
	}

	~Vertex() {
		glDeleteVertexArrays(1, &VertexArrayObject);
		glDeleteBuffers(1, &VertexBufferObject);
	}

};

