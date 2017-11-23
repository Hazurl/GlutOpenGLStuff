#include <glhaz/maths/maths.hpp>

namespace glhaz {
    
Mat4f translationMatrix(float x, float y, float z) {
    Mat4f m = matIdentity<float, 4>();
    m.at(0, 3) = x;
    m.at(1, 3) = y;
    m.at(2, 3) = z;
    return m;
}

Mat4f scaledMatrix(float x, float y, float z) {
    Mat4f m = matIdentity<float, 4>();
    m.at(0, 0) = x;
    m.at(1, 1) = y;
    m.at(2, 2) = z;
    return m;
}

Mat4f rotationMatrix(float x, float y, float z) {
    Mat4f mx = matIdentity<float, 4>();
    Mat4f my = matIdentity<float, 4>();
    Mat4f mz = matIdentity<float, 4>();
    
    float cx = std::cos(x / 180 * M_PI);
    float sx = std::sin(x / 180 * M_PI);
    mx.at(1, 1) = cx;
    mx.at(1, 2) = -sx;
    mx.at(2, 1) = sx;
    mx.at(2, 2) = cx;

    float cy = std::cos(y / 180 * M_PI);
    float sy = std::sin(y / 180 * M_PI);
    mx.at(0, 0) = cy;
    mx.at(0, 2) = -sy;
    mx.at(2, 0) = sy;
    mx.at(2, 2) = cy;

    float cz = std::cos(z / 180 * M_PI);
    float sz = std::sin(z / 180 * M_PI);
    mx.at(0, 0) = cz;
    mx.at(0, 1) = -sz;
    mx.at(1, 0) = sz;
    mx.at(1, 1) = cz;

    return mz * my * mx;
}

Mat4f transformationMatrix(float dx, float dy, float dz, float rx, float ry, float rz, float sx, float sy, float sz) {
    return translationMatrix(dx, dy, dz) * scaledMatrix(sx, sy, sz) * rotationMatrix(rx, ry, rz);
}

}