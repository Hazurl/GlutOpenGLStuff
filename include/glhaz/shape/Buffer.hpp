#pragma once

#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

namespace glhaz {

class Buffer {
public:

    static GLuint make_VBO(float* vertices, int size);
    static GLuint make_VBO();
    static GLuint make_IBO(unsigned int* indices, int size);
    static GLuint make_IBO();
    static GLuint make_VAO();

    static GLuint fill_VBO(GLuint vbo, float* vertices, int size);
    static GLuint fill_IBO(GLuint ibo, unsigned int* indices, int size);

    static void bind_VBO(GLuint vbo);
    static void bind_IBO(GLuint vbo);
    static void bind_VAO(GLuint vbo);

    static void unbind_VBO();
    static void unbind_IBO();
    static void unbind_VAO();

};

}