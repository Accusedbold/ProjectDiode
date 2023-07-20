#version 420 core

in vec3 FragPos;
in vec3 fragNormal;
in vec3 fragTan;
in vec3 fragBiTan;
in vec3 fragColor;
in vec2 fragUV;
flat in uint matIndex;
in mat3 TBN;

const int MAX_MATERIALS = 10;

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

uniform vec3 viewPos;

out vec4 FragColor;

void main()
{
    vec3 lightDir = vec3(0.0, 1.0, 0.0);   // Example: light direction from above
    vec3 viewDir = normalize(viewPos - FragPos);
    // Get the normal
    vec3 normal = fragNormal;

    // Diffuse lighting
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuseColor = fragColor;
    vec3 diffuseTerm = materials[matIndex].diffuse * diffuseColor * max(dot(normal, viewDir), 0.0);

    // Ambient Lighting
    vec3 ambientTerm = materials[matIndex].ambient * diffuseColor;

    // Emissive color
    vec3 emissiveColor = diffuseColor;
    vec3 emissiveTerm = materials[matIndex].emissive * emissiveColor;

    // Transparency
    float transparency = (1-materials[matIndex].transparency);

    // Final color calculation
    vec3 finalColor = ambientTerm + diffuseTerm + emissiveTerm;
    FragColor = vec4(finalColor, transparency);
}