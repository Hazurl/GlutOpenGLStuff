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
    location_world_tf_mat = getUniformLocation("world_tf_mat");   
}

void StaticShader::loadWorldTranformMatrix(Mat4f const& tf) {
    loadMat(location_world_tf_mat, (float(&)[4][4])tf[0][0]);
}

void StaticShader::loadTranformMatrix(Mat4f const& tf) {
    loadMat(location_tf_mat, (float(&)[4][4])tf[0][0]);
}

}