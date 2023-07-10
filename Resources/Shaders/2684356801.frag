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
    sampler2D specularTex;
    sampler2D normalTex;
    sampler2D transparencyTex;
};

const int MAX_MATERIALS = 25;
uniform Material materials[MAX_MATERIALS];

out vec4 FragColor;

void main()
{
    // Ambient lighting
    vec3 ambientColor = materials[matIndex].ambient * texture(materials[matIndex].diffuseTex, fragUV).rgb;

    // Diffuse lighting
    vec3 normal =  texture(materials[matIndex].normalTex, fragUV).rgb;
    vec3 lightDir = normalize(vec3(0.0, 1.0, 0.0));  // Example: light direction from above
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuseColor = materials[matIndex].diffuse * diff * texture(materials[matIndex].diffuseTex, fragUV).rgb;

    // Specular lighting
    vec3 viewDir = normalize(vec3(0.0, 0.0, 1.0));  // Example: view direction along the positive z-axis
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);  // Example: specular power of 32
    vec3 specularColor = materials[matIndex].specular * spec * texture(materials[matIndex].specularTex, fragUV).rgb;

    // Emissive color
    vec3 emissiveColor = materials[matIndex].emissive;

    // Transparency
    float transparency = texture(materials[matIndex].transparencyTex, fragUV).r;

    // Final color calculation
    vec3 finalColor = ambientColor + diffuseColor + specularColor + emissiveColor;
    FragColor = vec4(finalColor, transparency);
}