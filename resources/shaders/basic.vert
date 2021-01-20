#version 430 core

layout(location = 0) in vec2 a_Position;

void main(void)
{
    // la position 4D (NDC) du sommet
    gl_Position = vec4(a_Position, 0.0, 1.0);
}