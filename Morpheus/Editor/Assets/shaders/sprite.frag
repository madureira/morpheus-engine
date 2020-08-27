#version 330 core

#define MAX_LIGHT_SOURCES 128

in vec2 vTexCoord;
in vec4 vColor;
in float fScale;

uniform sampler2D u_texture;
uniform sampler2D u_normal;
uniform sampler2D u_specular;

uniform bool u_enableNormal;
uniform bool u_enableSpecular;

//values used for shading algorithm...
uniform int TotalSpotLights;                    // total of defined light sources
uniform vec2 Resolution;                        // resolution of screen
uniform vec3 LightPos[MAX_LIGHT_SOURCES];       // light position, normalized
uniform vec4 LightColor[MAX_LIGHT_SOURCES];     // light RGBA -- alpha is intensity
uniform vec3 LightFalloff[MAX_LIGHT_SOURCES];   // attenuation coefficients
uniform vec4 AmbientColor;                      // ambient RGBA -- alpha is intensity

out vec4 FragColor;

void main()
{
    // texelFetch gets a pixel by its index in the texture instead of 0-1 spacing
    vec4 DiffuseMap = texelFetch(u_texture, ivec2(vTexCoord), 0);

    //RGB of our normal map
    vec3 NormalMap = texelFetch(u_normal, ivec2(vTexCoord), 0).rgb;
    //NormalMap.g = 1.0 - NormalMap.g;

    //RGB of our specular map
    vec3 SpecularMap = texelFetch(u_specular, ivec2(vTexCoord), 0).rgb;

    vec3 LightsSum = vec3(0.0);

    for(int i = 0; i < TotalSpotLights; i++)
    {
        //The delta position of light
        vec3 LightDir = vec3(LightPos[i].xy - (gl_FragCoord.xy / Resolution.xy), LightPos[i].z);

        //Correct for aspect ratio
        LightDir.x *= Resolution.x / Resolution.y;

        //Determine distance (used for attenuation) BEFORE we normalize our LightDir
        float D = length(LightDir);

        float specularPower = 2.0;

        //normalize our vectors
        vec3 N = normalize(NormalMap * 2 - 1.0);
        vec3 S = normalize(SpecularMap * specularPower);
        vec3 L = normalize(LightDir);

        //Pre-multiply light color with intensity
        //Then perform "N dot L" to determine our diffuse term
        vec3 Diffuse = (LightColor[i].rgb * LightColor[i].a) * max(dot(N, L), 0.0);

        float shininess = 0.1;
        vec3 viewDir = vec3(0.0, 1.0, 1.0);

        // get the specular amount
        float specular = max(dot(S, normalize(viewDir)), 0.0);
        vec3 SpecIntensity = (pow(specular, shininess) * SpecularMap);

        //pre-multiply ambient color with intensity
        vec3 Ambient = AmbientColor.rgb * AmbientColor.a;

        //calculate attenuation
        float Attenuation = 1.0 / ( LightFalloff[i].x + (LightFalloff[i].y*D) + (LightFalloff[i].z*D*D) );

        //the calculation which brings it all together
        //vec3 Intensity = Ambient * Attenuation;
        //if (u_enableNormal)
        //{
        //    Intensity = Ambient + Diffuse * Attenuation;
        //}

        vec3 Intensity = Ambient + Attenuation;
        if (u_enableNormal)
        {
            Intensity = Ambient + Diffuse * Attenuation;
        }

        vec3 FinalColor = DiffuseMap.rgb * Intensity;

        if (u_enableSpecular)
        {
            FinalColor *=  SpecIntensity;
        }

        LightsSum += FinalColor;
    }

    if (TotalSpotLights == 0)
    {
        FragColor = vColor * DiffuseMap;
    }
    else {
        FragColor = vColor * vec4(LightsSum, DiffuseMap.a);
    }
}
