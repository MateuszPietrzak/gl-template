#version 330 core

in vec3 normal;
in vec4 color;

uniform vec3 light_direction;

out vec4 frag_color;

void main() {
    float ambient_strength = 0.3;
    vec3 ambient = color.xyz * ambient_strength;

    float diffuse_light = max(dot(normal, light_direction), 0.0);
    vec3 diffuse = diffuse_light * color.xyz;

    frag_color = vec4(ambient + diffuse, 1.0);

}
