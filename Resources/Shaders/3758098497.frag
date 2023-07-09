#version 330 core

in vec3 FragPos;
in vec3 fragNormal;
in vec3 fragTan;
in vec3 fragBiTan;
in vec3 fragColor;
in vec2 fragUV;
flat in uint matIndex;

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 emissive;
    sampler2D diffuseTex;
    sampler2D emissiveTex;
    sampler2D normalTex;
    sampler2D reflectionTex;
}

const int MAX_MATERIALS = 25;
uniform Material materials[MAX_MATERIALS];

out vec4 fragColor;

void main()
{
    // Retrieve the texture samples
    vec3 diffuseColor = texture(materials[matIndex].diffuseTex, fragUV).rgb;
    vec3 emissiveColor = texture(materials[matIndex].emissiveTex, fragUV).rgb;
    vec3 normal = texture(materials[matIndex].normalTex, fragUV).rgb;
    vec3 reflection = texture(materials[matIndex].reflectionTex, fragUV).rgb;

    // Calculate the lighting terms
    vec3 ambientTerm = materials[matIndex].ambient * diffuseColor;
    vec3 diffuseTerm = materials[matIndex].diffuse * diffuseColor * max(dot(normalize(fragNormal), normalize(vec3(0.0, 0.0, -1.0))), 0.0);
    vec3 specularTerm = materials[matIndex].specular * pow(max(dot(reflect(-normalize(fragPos), normalize(fragNormal)), normalize(vec3(0.0, 0.0, -1.0))), 0.0), 32.0);
    vec3 emissiveTerm = materials[matIndex].emissive * emissiveColor;
    
    // Combine the lighting terms
    vec3 finalColor = ambientTerm + diffuseTerm + specularTerm + emissiveTerm;

    fragColor = vec4(finalColor, 1.0);
}