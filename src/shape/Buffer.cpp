#include <glhaz/shape/Buffer.hpp>

namespace glhaz {

GLuint Buffer::make_VBO(float* vertices, int size) {
	return Buffer::fill_VBO(make_VBO(), vertices, size);
}

GLuint Buffer::make_VBO() {
    GLuint vbo;
    glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

    Buffer::bind_VBO(vbo);
    return vbo;
}

GLuint Buffer::make_IBO(unsigned int* indices, int size) {
	return Buffer::fill_IBO(make_IBO(), indices, size);
}

GLuint Buffer::make_IBO() {
    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    Buffer::bind_IBO(ibo);
    return ibo;
}

GLuint Buffer::make_VAO() {
    GLuint vao;
    glGenVertexArrays(1, &vao);

    Buffer::bind_VAO(vao);
    return vao;
}

GLuint Buffer::fill_VBO(GLuint vbo, float* vertices, int size) {
    Buffer::bind_VBO(vbo);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertices, GL_DYNAMIC_DRAW);
    return vbo;
}

GLuint Buffer::fill_IBO(GLuint ibo, unsigned int* indices, int size) {
    Buffer::bind_IBO(ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(unsigned int), indices, GL_DYNAMIC_DRAW);
    return ibo;
}

void Buffer::bind_VAO(GLuint vao) {
    glBindVertexArray(vao);
}

void Buffer::bind_VBO(GLuint vbo) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void Buffer::bind_IBO(GLuint ibo) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
}

void Buffer::unbind_VAO() {
    glBindVertexArray(0);
}

void Buffer::unbind_VBO() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Buffer::unbind_IBO() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

}