#version 330 core

in vec3 FragPos;
in vec3 fragNormal;
in vec3 fragTan;
in vec3 fragBiTan;
in vec3 fragColor;
in vec2 fragUV;
flat in uint matIndex;

const int MAX_MATERIALS = 4;

layout (std140, binding = 0) uniform MaterialBlock
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 emissive;
    float transparency;
    float shininess;
    float reflectivity;
} materials[MAX_MATERIALS];

uniform sampler2D diffuseTex[MAX_MATERIALS];
uniform sampler2D emissiveTex[MAX_MATERIALS];
uniform sampler2D normalTex[MAX_MATERIALS];
uniform sampler2D reflectionTex[MAX_MATERIALS];

out vec4 fragColor;

void main()
{
    // Diffuse lighting
    vec3 normal = texture(normalTex[matIndex], fragUV).rgb;
    vec3 lightDir = normalize(vec3(0.0, 1.0, 0.0));  // Example: light direction from above
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuseColor = materials[matIndex].diffuse * diff * texture(diffuseTex[matIndex], fragUV).rgb;

    // Retrieve the texture samples
    vec3 emissiveColor = texture(emissiveTex[matIndex], fragUV).rgb;
    vec3 reflection = texture(reflectionTex[matIndex], fragUV).rgb;

    // Calculate the lighting terms
    vec3 ambientTerm = materials[matIndex].ambient * diffuseColor;
    vec3 diffuseTerm = materials[matIndex].diffuse * diffuseColor * max(dot(normalize(fragNormal), normalize(vec3(0.0, 0.0, -1.0))), 0.0);
    vec3 specularTerm = materials[matIndex].specular * pow(max(dot(reflect(-normalize(fragPos), normalize(fragNormal)), normalize(vec3(0.0, 0.0, -1.0))), 0.0), 32.0);
    vec3 emissiveTerm = materials[matIndex].emissive * emissiveColor;
    
    // Combine the lighting terms
    vec3 finalColor = ambientTerm + diffuseTerm + specularTerm + emissiveTerm;

    FragColor = vec4(1.0,1.0,1.0,1.0);
}