#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glhaz/maths/Vec3.hpp>
#include <glhaz/maths/Mat.hpp>

namespace glhaz {

class ShaderProgram {
public:
    ShaderProgram();
    virtual ~ShaderProgram();

    void start();
    void stop();

protected:

    virtual void bindAttributes() = 0;
    virtual void getAllUniformLocations() = 0;

    void compileShader(const char* vertex_shader_path, const char* fragment_shader_path);
    void bindAttribute(GLint attribute, const char* name);
    GLint getUniformLocation(const char* name);

    void loadFloat(GLint location, float value);
    void loadVec(GLint location, float v[3]);
    void loadBool(GLint location, bool value);
    void loadMat(GLint location, float m[4][4]);

private:
    
    GLuint loadShader(const char* path, GLenum type);

    GLuint program;
    GLuint vertex_shader;
    GLuint fragment_shader;    
};

}