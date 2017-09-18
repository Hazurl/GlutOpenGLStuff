#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glhaz/Vec3f.hpp>

struct V3f {
    V3f(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
    float x, y, z;
};

using Vec3 = V3f;

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

    GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        std::cout << "Error: Failed to creat window" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, cb_key);

    GLenum res = glewInit();
    if (res != GLEW_OK) {
        std::cout << "Error: Faile to init glew: " << glewGetErrorString(res) << std::endl;
        return nullptr;
    }

    return window;
}

void CreateVertexBuffer(GLuint& VBO) {
    Vec3 vertices[1];
    vertices[0] = Vec3(0.5f, 0, 0.f);
//    vertices[1] = Vec3(1, -1, 0);
//    vertices[2] = Vec3(0, 1, 0);
     
    glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void drawVBO(GLuint& VBO, int nb_point) {
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_POINTS, 0, nb_point);    
    glDisableVertexAttribArray(1);
}

int main(int /* argc */, char** /* argv */) {
    GLFWwindow* window;
    GLuint VBO;

    window = init(960, 540, "Test window", error_callback, key_callback);
    if (!window)
        return 1;
    glfwSetWindowPos(window, 480 + 1920, 270);
    glClearColor(0.1, 0.1, 0.1, 0);

    CreateVertexBuffer(VBO);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glDrawArrays(GL_POINTS, 0, 1);    
        glDisableVertexAttribArray(1);
            
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
