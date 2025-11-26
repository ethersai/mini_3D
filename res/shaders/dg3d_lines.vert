#version 460 core
layout (location = 0) in vec3 aPos;

out vec4 out_color;

layout (std140, binding = 0) uniform uBlockMatrices {
    mat4 view;
    mat4 projection;
};

uniform vec4 u_color;
uniform mat4 u_model;

void main() {
    gl_Position = projection * view * u_model * vec4(aPos, 1.0);
    out_color = u_color;
}