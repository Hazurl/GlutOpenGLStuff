#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glhaz/shader/ShaderProgram.hpp>

namespace glhaz {

class StaticShader : public ShaderProgram {
public:

    StaticShader();
    ~StaticShader();

    void loadTranformMatrix(Mat4f& tf);

private:

    void bindAttributes() override;
    void getAllUniformLocations() override;

    GLint location_tf_mat;

    const char* vertex_shader_path = "src/shader/static_vertex_shader.vert";
    const char* fragment_shader_path = "src/shader/static_fragment_shader.frag";

};

}