#version 420 core

in vec3 FragPos;
in vec3 fragNormal;
in vec2 fragUV;
flat in uint matIndex;
in mat3 TBN;

const int MAX_MATERIALS = 10;

layout (std140, binding = 0) uniform MaterialBlock
{
    float transparency;
    float shininess;
    float reflectivity;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 emissive;
} materials[MAX_MATERIALS];

uniform vec3 viewPos;

out vec4 FragColor;

void main()
{
    // Vector Calculations
    vec3 lightPos = vec3(0.0, 100.0, 0.0); 
    vec3 lightDir = normalize(lightPos - FragPos);   // Example: light direction from above
    vec3 lightColor = vec3(1.0, 1.0, 1.0); // White Light Example
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    // Calculate the tangent space normal from the normal map
    vec3 normal = fragNormal;

    // Diffuse lighting
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuseColor = fragColor;
    vec3 diffuseTerm = materials[matIndex].diffuse * diff;

    // Ambient Lighting
    vec3 ambientTerm = materials[matIndex].ambient * diffuseColor;

    // Specular Lighting
    float shininess_exponent = materials[matIndex].shininess;
    float spec = pow(max(dot(normal, halfwayDir), 0.0), shininess_exponent);
    vec3 specularTerm = lightColor * spec;

    // Emissive color
    vec3 emissiveColor = diffuseColor;
    vec3 emissiveTerm = materials[matIndex].emissive * emissiveColor;

    // Transparency
    float transparency = (1-materials[matIndex].transparency);

    // Final color calculation
    vec3 finalColor = ambientTerm + diffuseTerm + specularTerm + emissiveTerm;
    FragColor = vec4(finalColor, transparency);
}