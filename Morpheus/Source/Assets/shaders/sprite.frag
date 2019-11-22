#version 330 core

in vec2 uv;
in vec4 color;

uniform sampler2D tex;

void main()
{
	// texelFetch gets a pixel by its index in the texture instead of 0-1 spacing
	//gl_FragColor = texelFetch(tex, ivec2(uv), 0) * color;
	gl_FragColor = texelFetch(tex, ivec2(uv), 0);
}
