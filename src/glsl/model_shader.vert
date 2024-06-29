#version 330 core

layout (location = 0) in vec3 input_pos;
layout (location = 1) in vec3 input_normal;
layout (location = 2) in vec4 input_color;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 normal;
out vec4 color;

void main() {
    normal = mat3(transpose(inverse(model))) * input_normal;
    color = input_color;
    gl_Position = projection * view * model * vec4(input_pos, 1.0);
}
