#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 offset;

out vec3 fColor;

void main()
{
    gl_Position = vec4(position.x + offset.x, position.y + offset.y, position.z, 1.0f);
    fColor = color;
}
