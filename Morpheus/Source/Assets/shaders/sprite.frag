#version 330 core

in vec2 vTexCoord;
in vec4 vColor;

uniform sampler2D u_texture;
uniform sampler2D u_normals;

//values used for shading algorithm...
uniform vec2 Resolution;      //resolution of screen
uniform vec3 LightPos;        //light position, normalized
uniform vec4 LightColor;      //light RGBA -- alpha is intensity
uniform vec3 LightFalloff;    //attenuation coefficients
uniform vec4 AmbientColor;    //ambient RGBA -- alpha is intensity 

out vec4 FragColor;

void main()
{
	// texelFetch gets a pixel by its index in the texture instead of 0-1 spacing
	vec4 DiffuseColor = texelFetch(u_texture, ivec2(vTexCoord), 0);

	//RGB of our normal map
	vec3 NormalMap = texelFetch(u_normals, ivec2(vTexCoord), 0).rgb;
	//NormalMap.g = 1.0 - NormalMap.g;
	
	//The delta position of light
	vec3 LightDir = vec3(LightPos.xy - (gl_FragCoord.xy / Resolution.xy), LightPos.z);
	
	//Correct for aspect ratio
	LightDir.x *= Resolution.x / Resolution.y;
	
	//Determine distance (used for attenuation) BEFORE we normalize our LightDir
	float D = length(LightDir);
	
	//normalize our vectors
	vec3 N = normalize(NormalMap * 2.0 - 1.0);
	vec3 L = normalize(LightDir);
	
	//Pre-multiply light color with intensity
	//Then perform "N dot L" to determine our diffuse term
	vec3 Diffuse = (LightColor.rgb * LightColor.a) * max(dot(N, L), 0.0);

	//pre-multiply ambient color with intensity
	vec3 Ambient = AmbientColor.rgb * AmbientColor.a;
	
	//calculate attenuation
	float Attenuation = 1.0 / ( LightFalloff.x + (LightFalloff.y*D) + (LightFalloff.z*D*D) );
	
	//the calculation which brings it all together
	vec3 Intensity = Ambient + Diffuse * Attenuation;
	vec3 FinalColor = DiffuseColor.rgb * Intensity;

	FragColor = vColor * vec4(FinalColor, DiffuseColor.a);
}
