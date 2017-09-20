#version 150

in vec3 position;

uniform mat4 tf_mat;

void main() {
    mat4 m = mat4(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    );
    gl_Position = tf_mat * vec4(position, 1.0);
}