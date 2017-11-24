#include <glhaz/shape/Shape.hpp>
#include <glhaz/shape/Buffer.hpp>
#include <iostream>

namespace glhaz {

Shape::Shape(float* vertices, int vsize, unsigned int* indices, int isize) 
: vsize(vsize), isize(isize) {
    vao = Buffer::make_VAO();
    vbo = Buffer::make_VBO(vertices, vsize);
    ibo = Buffer::make_IBO(indices, isize);
}

Shape::Shape() {
    vao = Buffer::make_VAO();
    vbo = Buffer::make_VBO();
    ibo = Buffer::make_IBO();
}

void Shape::setVertices(float* vertices, unsigned int size) {
    Buffer::fill_VBO(vbo, vertices, vsize = size);
}

void Shape::setIndices(unsigned int* indices, unsigned int size) {
    Buffer::fill_IBO(ibo, indices, isize = size);
}

void Shape::draw() {
    glEnableVertexAttribArray(0);

    Buffer::bind_VAO(vao);
    Buffer::bind_VBO(vbo);
    Buffer::bind_IBO(ibo);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawElements(GL_TRIANGLES, isize, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
}

Mat4f Shape::getTransform() const {
    return transform.asMatrix();
}

Vec3f Shape::position() const {
    return transform.position;
}

Vec3f Shape::rotation() const {
    return transform.rotation;
}

Vec3f Shape::scale() const {
    return transform.scale;
}

Vec3f Shape::position(Vec3f const& new_position) {
    return transform.position = new_position;
}

Vec3f Shape::rotation(Vec3f const& new_rotation) {
    return transform.rotation = new_rotation;
}

Vec3f Shape::scale(Vec3f const& new_scale) {
    return transform.scale = new_scale;
}


}