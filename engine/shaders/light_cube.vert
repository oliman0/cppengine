#version 430

layout (location = 0) in vec3 aPos;

out vec4 lcolour;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 colour;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);

    lcolour = colour;
}