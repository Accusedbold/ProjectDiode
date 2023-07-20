#version 330 core

layout (location = 0) in uint matIndices;
layout (location = 1) in vec4 position;
layout (location = 2) in vec4 normal;
layout (location = 3) in vec4 tangent;
layout (location = 4) in vec4 bitangent;
layout (location = 5) in vec4 color;
layout (location = 6) in vec2 uv;
layout (location = 7) in uvec4 boneIndices;
layout (location = 8) in vec4 boneWeights;
layout (location = 9) in mat4 transformmatrix;

out vec3 fragPos;
out vec3 fragNormal;
out vec3 fragTan;
out vec3 fragBiTan;
out vec3 fragColor;
out vec2 fragUV;
flat out uint matIndex;
out mat3 TBN;

void main()
{
    gl_Position = transformmatrix * position;
    fragPos = gl_Position.xyz;
    fragNormal = (transformmatrix * normal).xyz;
    fragTan = (transformmatrix * tangent).xyz;
    fragBiTan = (transformmatrix * bitangent).xyz;
    fragColor = color.xyz;
    fragUV = vec2(uv.x, 1-uv.y);
    matIndex = matIndices;
    TBN = mat3(normalize(fragTan), normalize(fragBiTan), normalize(fragNormal));
}