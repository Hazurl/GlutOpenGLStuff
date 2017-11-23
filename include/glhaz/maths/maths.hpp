#pragma once

#include <glhaz/maths/Mat.hpp>
#include <glhaz/maths/Vec3.hpp>
#include <cmath>

namespace glhaz {

Mat4f translationMatrix(float x, float y, float z);
Mat4f scaledMatrix(float x, float y, float z);
Mat4f rotationMatrix(float x, float y, float z);
Mat4f transformationMatrix(float dx, float dy, float dz, float rx, float ry, float rz, float sx, float sy, float sz);

}