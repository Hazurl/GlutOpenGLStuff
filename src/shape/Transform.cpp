#include <glhaz/shape/Transform.hpp>

namespace glhaz {

Transform::Transform(Vec3f const& position, Vec3f const& rotation, Vec3f const& scale)
    : position(position), rotation(rotation), scale(scale) {}

Mat4f Transform::asMatrix() const {
    return transformationMatrix(
        position.x, position.y, position.z,
        rotation.x, rotation.y, rotation.z,
        scale.x, scale.y, scale.z
    );
}

}