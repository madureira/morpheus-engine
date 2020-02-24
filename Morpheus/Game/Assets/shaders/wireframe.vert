#version 330 core

// Vertex attributes for position and color
layout(location = 0) in vec2 in_position;

// uniform will contain the world matrix.
uniform mat3 screenTransform;
uniform float scale;

void main()
{
	//transform the vector
	vec3 transformed = screenTransform * vec3(in_position, 1) * vec3(scale, scale, 1);
	gl_Position = vec4(transformed, 1);
}
