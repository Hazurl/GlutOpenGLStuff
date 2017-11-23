#pragma once

#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

#include <glhaz/shape/Transform.hpp>

namespace glhaz {

class Shape {
public:

    Shape(float* vertices, int vsize, unsigned int* indices, int isize);

    void draw();
    Mat4f getTransform() const;

    Vec3f position() const;
    Vec3f rotation() const;
    Vec3f scale() const;

    Vec3f position(Vec3f const& new_position);
    Vec3f rotation(Vec3f const& new_rotation);
    Vec3f scale(Vec3f const& new_scale);

private:

    unsigned int isize;
    GLuint vbo, vao, ibo;

    Transform transform;

};

}