#version 330 core

out vec4 color;

noperspective in vec3 gDist;

const vec4 wire_color = vec4(0.0, 0.5, 0.0, 1.0);
const vec4 fill_color = vec4(1, 1, 1, 0);

void main()
{
	float d = min(gDist[0], min(gDist[1], gDist[2]));
	float i = exp2(-2 * d * d);

	color = i * wire_color + (1.0 - i) * fill_color;
}
