#include "Vertex.h"

void Vertex::setVertexData(const std::vector<glm::vec3>& vertices) {

	glGenVertexArrays(1, &VertexArrayObject);
	glGenBuffers(1, &VertexBufferObject);

	glBindVertexArray(VertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Vertex::setShaderFiles(std::string VertexPath, std::string FragmentPath) {
	if (VertexPath != "") VertexShader->readShader(VertexPath);
	if (FragmentPath != "") FragmentShader->readShader(FragmentPath);
}

void Vertex::compileShaders() {
	VertexShader->compileShader();
	FragmentShader->compileShader();

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, *VertexShader->getSource());
	glAttachShader(shaderProgram, *FragmentShader->getSource());
	glLinkProgram(shaderProgram);
	ShaderPogram = &shaderProgram;

	GLint success;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		GLchar infoLog[512];
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cerr << "Error linking shaders:\n" << infoLog << std::endl;
	}
	glDeleteShader(*VertexShader->getSource());
	glDeleteShader(*FragmentShader->getSource());

	glUseProgram(shaderProgram);

}

void Vertex::display(GLenum mode, GLint start, GLsizei size) {
	glBindVertexArray(VertexArrayObject);
	glDrawArrays(mode, start, size);
	glBindVertexArray(0);
}