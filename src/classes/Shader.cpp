#include "Shader.h"

void Shader::readShader(const std::string pathToFile) {
    std::string content;
    std::ifstream file(pathToFile);
    if (!file) return;

    file.ignore(std::numeric_limits<std::streamsize>::max());
    auto size = file.gcount();

    if (size > 0x10000) return;

    file.clear();
    file.seekg(0, std::ios_base::beg);

    std::stringstream sstr;
    sstr << file.rdbuf();
    file.close();
    shaderCode = sstr.str();
}


void Shader::compileShader() {
    source = glCreateShader(shaderType);
    const char* code = shaderCode.c_str();
    glShaderSource(source, 1, &code, NULL);
    glCompileShader(source);
    GLint success;
    glGetShaderiv(source, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetShaderInfoLog(source, 512, NULL, infoLog);
        std::cerr << "Error Compiling the shader : \n\n" << infoLog << std::endl;
        return;
    }
}