#include <glhaz/window/Window.hpp>

namespace glhaz {

Window::~Window() {
    shader->stop();
    delete shader;
    glfwDestroyWindow(window);
}

void Window::beginDraw() {
    glfwMakeContextCurrent(window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::endDraw() {
    glfwPollEvents();
    glfwSwapBuffers(window);
}

void Window::setPosition(unsigned int x, unsigned int y) {
    glfwSetWindowPos(window, x, y);
}

void Window::setClearColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

int Window::getWidth() const {
    return width;
}

int Window::getHeight() const {
    return height;
}

StaticShader& Window::getShader() {
    glfwMakeContextCurrent(window);
    return *shader;
}

const StaticShader& Window::getShader() const {
    glfwMakeContextCurrent(window);
    return *shader;
}

GLFWwindow* Window::getGLFWWindow() {
    return window;
}

const GLFWwindow* Window::getGLFWWindow() const {
    return window;
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(window);
}

void Window::setContext() {
    glfwMakeContextCurrent(window);
}

}