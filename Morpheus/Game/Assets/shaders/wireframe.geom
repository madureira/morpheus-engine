#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

out vec3 gDist;

void main()
{
	vec2 res = vec2(800, 600);
	vec2 p0 = res * gl_in[0].gl_Position.xy / gl_in[0].gl_Position.w;
	vec2 p1 = res * gl_in[1].gl_Position.xy / gl_in[0].gl_Position.w;
	vec2 p2 = res * gl_in[2].gl_Position.xy / gl_in[0].gl_Position.w;

	vec2 v0 = p2 - p1;
	vec2 v1 = p2 - p0;
	vec2 v2 = p1 - p2;
	float area = abs(v1.x * v2.y - v1.y * v2.x);

	gDist = vec3(area / length(v0), 0, 0);
	gl_Position = gl_in[0].gl_Position;
	EmitVertex();

	gDist = vec3(0, area / length(v1), 0);
	gl_Position = gl_in[1].gl_Position;
	EmitVertex();

	gDist = vec3(0, 0, area / length(v2));
	gl_Position = gl_in[2].gl_Position;
	EmitVertex();

	EndPrimitive();
}
