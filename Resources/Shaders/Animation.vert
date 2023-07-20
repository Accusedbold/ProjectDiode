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


const uint MAX_BONES = 206u;
const uint MAX_BONE_INFLUENCE = 4u;
uniform mat4  finalBonesMatrices[MAX_BONES];


void main()
{
    vec4 totalPosition = vec4(0.0f);
    vec4 totalNormal = vec4(0.0f);
    vec4 totalTan = vec4(0.0f);
    vec4 totalBiTan = vec4(0.0f);
    for(uint i = 0u ; i < MAX_BONE_INFLUENCE ; ++i)
    {
        if(boneIndices[i] >= MAX_BONES)
        {
            totalPosition = position;
            break;
        }
        vec4 localPosition = finalBonesMatrices[boneIndices[i]] * position;
        vec4 localNormal = finalBonesMatrices[boneIndices[i]] * normal;
        vec4 localTan = finalBonesMatrices[boneIndices[i]] * tangent;
        vec4 localBiTan = finalBonesMatrices[boneIndices[i]] * bitangent;
        totalPosition += localPosition * boneWeights[i];
        totalNormal += localNormal * boneWeights[i];
        totalTan += localTan * boneWeights[i];
        totalBiTan += localBiTan * boneWeights[i];
    }

    gl_Position = transformmatrix * totalPosition;
    fragPos = gl_Position.xyz;
    fragNormal = normalize((transformmatrix * totalNormal).xyz);
    fragTan = normalize((transformmatrix * totalTan).xyz);
    fragBiTan = normalize((transformmatrix * totalBiTan).xyz);
    fragColor = color.xyz;
    fragUV = vec2(uv.x, 1-uv.y);
    matIndex = matIndices;
    TBN = mat3(normalize(fragTan), normalize(fragBiTan), normalize(fragNormal));
}