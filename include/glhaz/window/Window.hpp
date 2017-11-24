#pragma once

#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

#include <glhaz/shader/StaticShader.hpp>
#include <glhaz/maths/Vec3.hpp>

#include <stdexcept>

namespace glhaz {

class Window {
public:

    template<typename CB_ERR, typename CB_KEY>
    Window(int width, int height, const char* title, CB_ERR* cb_err, CB_KEY* cb_key) {
        glfwSetErrorCallback(cb_err);
        if (!glfwInit()) {
            std::cout << "Error: Failed to init glfw" << std::endl;
            throw std::runtime_error("Failed to init glfw");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!window) {
            std::cout << "Error: Failed to create window" << std::endl;
            glfwTerminate();
            throw std::runtime_error("Failed to create window");
        }

        glfwMakeContextCurrent(window);
        glfwSetKeyCallback(window, cb_key);

        glewExperimental = true;

        GLenum res = glewInit();
        if (res != GLEW_OK) {
            std::cout << "Error: Failed to init glew: " << glewGetErrorString(res) << std::endl;
            throw std::runtime_error("Failed to init glew");
        }

        glfwMakeContextCurrent(window);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        setPosition(100, 0);
        setClearColor(0, 0, 0, 0);

        if (!window) {
            throw std::runtime_error("the window has not been created");
        }

        shader = new StaticShader();
        shader->start();
    }

    ~Window();

    void beginDraw();
    void endDraw();

    void setPosition(unsigned int x, unsigned int y);
    void setClearColor(float r, float g, float b, float a = 0);

    int getWidth() const;
    int getHeight() const;

    StaticShader& getShader();
    const StaticShader& getShader() const;

    GLFWwindow* getGLFWWindow();
    const GLFWwindow* getGLFWWindow() const;

    bool shouldClose() const;

    void setContext();

private:

    GLFWwindow* window;
    int width, height;
    StaticShader* shader;

};

}