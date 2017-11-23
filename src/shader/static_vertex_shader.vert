#version 330

layout(location = 0) in vec3 position;

uniform mat4 tf_mat;
uniform mat4 world_tf_mat;

void main() {
    gl_Position = world_tf_mat * tf_mat * vec4(position, 1.0);
}