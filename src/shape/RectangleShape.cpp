#include <glhaz/shape/RectangleShape.hpp>

namespace glhaz {

RectangleShape::RectangleShape(float x, float y, float width, float height) 
    : Shape(), width(width), height(height) {

    float vertices[12] = {
        0, 0, 0,
        width, 0, 0,
        width, height, 0,
        0, height, 0
    };

    unsigned int indices[6] {
        0, 1, 2,
        0, 3, 2
    };

    position({x, y, 0});

    setVertices(vertices, 12);
    setIndices(indices, 6);
}

void RectangleShape::setWidth(float _width) {
    width = _width;
    float vertices[12] = {
        0, 0, 0,
        width, 0, 0,
        width, height, 0,
        0, height, 0
    };

    setVertices(vertices, 12);
}

void RectangleShape::setHeight(float _height) {
    height = _height;
    float vertices[12] = {
        0, 0, 0,
        width, 0, 0,
        width, height, 0,
        0, height, 0
    };

    setVertices(vertices, 12);
}
    
}