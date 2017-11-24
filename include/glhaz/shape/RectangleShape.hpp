#pragma once

#include <glhaz/shape/Shape.hpp>

namespace glhaz {

class RectangleShape : public Shape {
public:

    RectangleShape(float x, float y, float width, float height);

    void setWidth(float _width);
    void setHeight(float _height);

private:

    float width, height;    

};

}