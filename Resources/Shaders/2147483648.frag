#version 420 core

in vec3 FragPos;
in vec3 fragNormal;
in vec3 fragTan;
in vec3 fragBiTan;
in vec3 fragColor;
in vec2 fragUV;
flat in uint matIndex;

const int MAX_MATERIALS = 5;

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

out vec4 FragColor;

void main()
{
    // Ambient lighting
    vec3 ambientColor = materials[matIndex].ambient * fragColor;

    // Diffuse lighting
    vec3 normal =  fragNormal;
    vec3 lightDir = normalize(vec3(0.0, 1.0, 0.0));  // Example: light direction from above
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuseColor = fragColor;

    // Specular lighting
    vec3 viewDir = normalize(vec3(0.0, 0.0, 1.0));  // Example: view direction along the positive z-axis
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), materials[matIndex].shininess);
    vec3 specularColor = materials[matIndex].specular * spec;

    // Emissive color
    vec3 emissiveColor = materials[matIndex].emissive * fragColor;

    // Final color calculation
    vec3 finalColor = ambientColor + diffuseColor + specularColor + emissiveColor;
    FragColor = vec4(diffuseColor,1.0);
}