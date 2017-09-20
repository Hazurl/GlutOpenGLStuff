#include <glhaz/shader/StaticShader.hpp>
#include <iostream>

namespace glhaz {

StaticShader::StaticShader() : ShaderProgram() {
    compileShader(vertex_shader_path, fragment_shader_path);

}

StaticShader::~StaticShader() {

}

void StaticShader::bindAttributes() {
    bindAttribute(0, "position");
}

void StaticShader::getAllUniformLocations() {
    location_tf_mat = getUniformLocation("tf_mat");   
}

void StaticShader::loadTranformMatrix(Mat4f& tf) {
    loadMat(location_tf_mat, (float(&)[4][4])tf[0][0]);
}

}