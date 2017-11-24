#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

#include <iostream>

#include <glhaz/maths/Vec3.hpp>
#include <glhaz/maths/Mat.hpp>
#include <glhaz/maths/maths.hpp>
#include <glhaz/shader/StaticShader.hpp>
#include <glhaz/shape/Shape.hpp>

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

void createTriangle(GLuint& vbo, GLuint& vao, GLuint& elem) {
    float vertices[] = { -0.5f, 0.5f, 0.f, 
                         0.5f, 0.5f, 0.f, 
                         0.5f, -0.5f, 0.f,
                         -0.5f, 0.5f, 0.f, 
                         0.5f, -0.5f, 0.f,
                         -0.5f, -0.5f, 0.f};
/*
    float vertices[] = {
        -0.5, 0.5, 0,
        -0.5, -0.5, 0,
        0.5, -0.5, 0,
        0.5, 0.5, 0
    };

    float indexes[] = {
        0, 1, 2,
        1, 2, 3
    };
*/
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
    GLFWwindow* window = init(960, 540, "Test window", error_callback, key_callback);
    if (!window)
        return 1;
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glfwSetWindowPos(window, 480, 270);
    glClearColor(0.1, 0.1, 0.1, 0);

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;

    float vertices_square[] = {
        -0.5f, 0.5f, 0.f,
        -0.5f, -0.5f, 0.f,
        0.5f, -0.5f, 0.f,
        0.5f, 0.5f, 0.f
    };

    unsigned int indexes_square[] = {
        0, 2, 1,
        0, 3, 2
    };

    glhaz::Shape square(vertices_square, sizeof(vertices_square) / sizeof(float), indexes_square,  sizeof(indexes_square) / sizeof(unsigned int));

    unsigned int indexes_triangle[] = {
        0, 2, 1
    };

    glhaz::Shape triangle(vertices_square, sizeof(vertices_square) / sizeof(float) - 1, indexes_triangle,  sizeof(indexes_triangle) / sizeof(unsigned int));
    
    glhaz::StaticShader shader;

    shader.start();

    int step = 0;
    auto world = glhaz::transformationMatrix(0, 0, 0, 0, 0, 0, 540 / 960., 1, 1);
    shader.loadWorldTranformMatrix(world);

    square.scale({0.5, 0.5, 0.5});
    triangle.scale({0.5, 0.5, 0.5});

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        step++;
        square.position({-1, std::sin(step / 200.) / 2, 0});
        shader.loadTranformMatrix(square.getTransform());
        square.draw();

        triangle.position({1, -std::sin(step / 200.) / 2, 0});
        shader.loadTranformMatrix(triangle.getTransform());
        triangle.draw();
        
        glfwPollEvents();    
        glfwSwapBuffers(window);
    }

    shader.stop();
    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}
