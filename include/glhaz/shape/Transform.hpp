#pragma once

#include <glhaz/maths/Vec3.hpp>
#include <glhaz/maths/Mat.hpp>
#include <glhaz/maths/maths.hpp>

namespace glhaz {

class Transform {
public:

    Transform(Vec3f const& position = Vec3f::zero(), Vec3f const& rotation = Vec3f::zero(), Vec3f const& scale = Vec3f::units());

    Mat4f asMatrix() const;

    Vec3f position, rotation, scale;

};

}