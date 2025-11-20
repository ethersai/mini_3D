#version 460 core
layout (location = 0) in vec3 aPos;

out vec4 out_color;

layout (std140, binding = 0) uniform uBlockMatrices {
    mat4 view;
    mat4 projection;
};

uniform vec4 u_color;

void main() {
    gl_Position = projection * view * vec4(aPos, 1.0);
    out_color = u_color;
}