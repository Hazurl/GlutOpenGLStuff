#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

#include <iostream>

#include <glhaz/maths/Vec3.hpp>
#include <glhaz/maths/Mat.hpp>
#include <glhaz/maths/maths.hpp>
#include <glhaz/shader/StaticShader.hpp>
#include <glhaz/shape/Shape.hpp>
#include <glhaz/shape/RectangleShape.hpp>
#include <glhaz/window/Window.hpp>

using Vec3 = glhaz::Vec3f;

void error_callback(int error, const char* description) {
    std::cout << "Error " << error << ": " << description << std::endl;
}

void key_callback(GLFWwindow* window, int key, int /* scancode */, int action, int /* mods */) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(int /* argc */, char** /* argv */) {
    try {
        glhaz::Window window(360, 360, "Test window", error_callback, key_callback);
        window.setClearColor(0.1, 0.1, 0.1);
        window.setPosition(100, 100);

        glhaz::Window window2(360, 360, "Second window", error_callback, key_callback);
        window.setClearColor(0.1, 0.1, 0.1);
        window.setPosition(460, 100);

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
        
        window2.setContext();
        //glhaz::Shape square(vertices_square, sizeof(vertices_square) / sizeof(float), indexes_square,  sizeof(indexes_square) / sizeof(unsigned int));
        glhaz::RectangleShape square(0, 0, 1, 1);

        unsigned int indexes_triangle[] = {
            0, 2, 1
        };

        window.setContext();
        glhaz::Shape triangle(vertices_square, sizeof(vertices_square) / sizeof(float) - 1, indexes_triangle,  sizeof(indexes_triangle) / sizeof(unsigned int));

        int step = 0;
        auto world = glhaz::transformationMatrix(0, 0, 0, 0, 0, 0, 360 / 360.f, 1, 1);

        window.getShader().loadWorldTranformMatrix(world);
        window2.getShader().loadWorldTranformMatrix(world);

        square.scale({0.5, 0.5, 0.5});
        triangle.scale({0.5, 0.5, 0.5});

        while (!window.shouldClose() && !window2.shouldClose()) {
            step++;
            window.beginDraw();
    
            triangle.position({0, -std::sin(step / 20.f) / 2, 0});
            window.getShader().loadTranformMatrix(triangle.getTransform());
            triangle.draw();

            window.endDraw();

            window2.beginDraw();

            square.position({-0.25, std::sin(step / 20.f) / 2 - 0.25, 0});
            square.setWidth(1 + std::sin(step / 20.f) / 2);
            square.setHeight(1 + std::sin(step / 20.f) / 2);
            window2.getShader().loadTranformMatrix(square.getTransform());
            square.draw();

            window2.endDraw();

        }
    } catch(...) {
        std::cout << "Exception !" << std::endl;
    }
    glfwTerminate();
    return 0;
}
