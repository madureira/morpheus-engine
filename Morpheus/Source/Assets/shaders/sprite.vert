/*
Title: Sprite Batching
File Name: vertex.glsl
Copyright ? 2016
Author: David Erbelding
Written under the supervision of David I. Schwartz, Ph.D., and
supported by a professional development seed grant from the B. Thomas
Golisano College of Computing & Information Sciences
(https://www.rit.edu/gccis) at the Rochester Institute of Technology.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#version 400 core

// Vertex attributes for position and color
layout(location = 0) in vec2 in_position;
layout(location = 1) in vec2 in_uv;
layout(location = 2) in vec4 in_color;

// uniform will contain the world matrix.
uniform mat3 screenTransform;

// output variables
out vec2 uv;
out vec4 color;

void main(void)
{
	//transform the vector
	vec3 transformed = screenTransform * vec3(in_position, 1);
	gl_Position = vec4(transformed, 1);
	
	// pass through uv and color
	uv = in_uv;
	color = in_color;
}
