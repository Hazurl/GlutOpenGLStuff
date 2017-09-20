#include <glhaz/shader/ShaderProgram.hpp>
#include <fstream>
#include <iostream>

namespace glhaz {

ShaderProgram::ShaderProgram() {
    
}

ShaderProgram::~ShaderProgram() {
    glDetachShader(program, vertex_shader);
    glDeleteShader(vertex_shader);
    glDetachShader(program, fragment_shader);
    glDeleteShader(fragment_shader);
    glDeleteProgram(program);
}

void ShaderProgram::compileShader(const char* vertex_shader_path, const char* fragment_shader_path) {
    GLint res = GL_FALSE;
    char buffer[512];
    
    program = glCreateProgram();
    vertex_shader = loadShader(vertex_shader_path, GL_VERTEX_SHADER);
    fragment_shader = loadShader(fragment_shader_path, GL_FRAGMENT_SHADER);
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    bindAttributes();
    glLinkProgram(program);
    glValidateProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &res);
    glGetProgramInfoLog(program, 500, NULL, buffer);
    std::cout << "Link shader status: " << buffer << std::endl;
    if (!res) 
        exit(1);

    getAllUniformLocations();
}

void ShaderProgram::start() {
    glUseProgram(program);
}

void ShaderProgram::stop() {
    glUseProgram(0);
}

void ShaderProgram::loadFloat(GLint location, float value) {
    glUniform1f(location, value);
}

void ShaderProgram::loadVec(GLint location, float v[3]) {
    glUniform3f(location, v[0], v[1], v[2]);
}

void ShaderProgram::loadBool(GLint location, bool value) {
    float v = value ? 1 : 0;
    glUniform1f(location, v);
}

void ShaderProgram::loadMat(GLint location, float m[4][4]) {
    glUniformMatrix4fv(location, 1, GL_TRUE, m[0]);
}

void ShaderProgram::bindAttribute(GLint attribute, const char* name) {
    glBindAttribLocation(program, attribute, name);
}

GLint ShaderProgram::getUniformLocation(const char* name) {
    return glGetUniformLocation(program, name);
}

GLuint ShaderProgram::loadShader(const char* path, GLuint type) {
    std::ifstream file (path);
    std::string text;
    
    if (!file.is_open()) {
        std::cout << "Can't open file: " << path << std::endl;
        exit(1);
    }

    file.seekg(std::ios::end);
    text.reserve(file.tellg());
    file.seekg(std::ios::beg);
    text.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    const char* c_text = text.c_str();

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &c_text, NULL);
    glCompileShader(shader);
    GLint res = GL_FALSE;
    char buffer[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &res);
    glGetShaderInfoLog(shader, 500, NULL, buffer);
    std::cout << "Compile Shader status for '" << path << "': " << buffer << std::endl;
    if (!res) 
        exit(1);

    return shader;
}

}