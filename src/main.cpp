#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

#include <iostream>

#include <glhaz/maths/Vec3.hpp>
#include <glhaz/maths/Mat.hpp>
#include <glhaz/maths/maths.hpp>
#include <glhaz/shader/StaticShader.hpp>

using Vec3 = glhaz::Vec3f;

void error_callback(int error, const char* description) {
    std::cout << "Error " << error << ": " << description << std::endl;
}

void key_callback(GLFWwindow* window, int key, int /* scancode */, int action, int /* mods */) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

template<typename CB_ERR, typename CB_KEY>
GLFWwindow* init(int width, int height, const char* title, CB_ERR* cb_err, CB_KEY* cb_key) {
    glfwSetErrorCallback(cb_err);
    if (!glfwInit()) {
        std::cout << "Error: Failed to init glfw" << std::endl;
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        std::cout << "Error: Failed to create window" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, cb_key);

    glewExperimental = true;

    GLenum res = glewInit();
    if (res != GLEW_OK) {
        std::cout << "Error: Failed to init glew: " << glewGetErrorString(res) << std::endl;
        return nullptr;
    }

    return window;
}

void createTriangle(GLuint& vbo, GLuint& vao) {
    float vertices[] = { -0.5f, 0.5f, 0.f, 
                         0.5f, 0.5f, 0.f, 
                         0.5f, -0.5f, 0.f,
                         -0.5f, 0.5f, 0.f, 
                         0.5f, -0.5f, 0.f,
                         -0.5f, -0.5f, 0.f};   
    glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

int main(int /* argc */, char** /* argv */) {
    GLFWwindow* window;
    window = init(960, 540, "Test window", error_callback, key_callback);
    if (!window)
        return 1;
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glfwSetWindowPos(window, 480 + 1920, 270);
    glClearColor(0.1, 0.1, 0.1, 0);

    GLuint vbo, vao;
    createTriangle(vbo, vao);
    
    glhaz::StaticShader shader;

    shader.start();
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        auto tf_matrix = glhaz::transformationMatrix(0, 0, 0, 0, 0, 0, 500.f / 960, 500.f / 540, 1);
        shader.loadTranformMatrix(tf_matrix);
        
        glEnableVertexAttribArray(0);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);    
        glDisableVertexAttribArray(0);
        
        glfwPollEvents();    
        glfwSwapBuffers(window);
    }
    shader.stop();
    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}
