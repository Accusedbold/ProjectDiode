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
};

const int MAX_MATERIALS = 25;
uniform Material materials[MAX_MATERIALS];

out vec4 FragColor;

void main()
{
    // Ambient lighting
    vec3 ambientColor = materials[matIndex].ambient;

    // Diffuse lighting
    vec3 normal = normalize(fragNormal);
    vec3 lightDir = normalize(vec3(0.0, 1.0, 0.0));  // Example: light direction from above
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuseColor = materials[matIndex].diffuse * diff;

    // Specular lighting
    vec3 viewDir = normalize(vec3(0.0, 0.0, 1.0));  // Example: view direction along the positive z-axis

    // Emissive color
    vec3 emissiveColor = materials[matIndex].emissive;

    // Final color calculation
    vec3 finalColor = ambientColor + diffuseColor + emissiveColor;
    FragColor = vec4(finalColor, 1.0f);
}