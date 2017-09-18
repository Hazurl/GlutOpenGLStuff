#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <iostream>
#include <glhaz/Vec3f.hpp>

struct V3f {
    V3f(float x = 0.5, float y = 0.5, float z = 0.5) : x(x), y(y), z(z) {}
    float x = 0.5, y = 0.5, z = 0.5;

    operator const float*() const
    {
        return &(x);
    }
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

int main(int /* argc */, char** /* argv */) {
    GLFWwindow* window;
    window = init(960, 540, "Test window", error_callback, key_callback);
    if (!window)
        return 1;
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glfwSetWindowPos(window, 480 + 1920, 270);
    glClearColor(0.1, 0.1, 0.1, 0);
/*  ====================  */

    float vertices[] = { 0.f, 0.5f, 0.f, 0.5f, -0.5f, 0.f, -0.5f, -0.5f, 0.f};   
    GLuint vbo;
    glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
/*
    const char* vertex_shader =
    "#version 150\n"
    "in vec3 vp;"
    "void main() {"
    "  gl_Position = vec4(vp, 1.0);"
    "}";
    const char* fragment_shader =
    "#version 150\n"
    "out vec4 frag_colour;"
    "void main() {"
    "  frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
    "}";

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);

    GLuint shader_prgm = glCreateProgram();
    glAttachShader(shader_prgm, fs);
    glAttachShader(shader_prgm, vs);
    glLinkProgram(shader_prgm);
*/    
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glUseProgram(shader_prgm);
        
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);    
            
        glfwPollEvents();    
        glfwSwapBuffers(window);
    }
    glDisableVertexAttribArray(0);
    glfwDestroyWindow(window);

    /*================*/
    glfwTerminate();
    return 0;
}
