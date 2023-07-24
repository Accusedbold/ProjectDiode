#version 330 core

layout (location = 0) in uint matIndices;
layout (location = 1) in vec4 position;
layout (location = 2) in vec4 normal;
layout (location = 3) in vec4 tangent;
layout (location = 4) in vec2 uv;
layout (location = 5) in uvec4 boneIndices;
layout (location = 6) in vec4 boneWeights;
layout (location = 7) in mat4 MWVP;
layout (location = 11) in mat4 MW;

out vec3 fragPos;
out vec3 fragNormal;
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
        totalPosition += localPosition * boneWeights[i];
        totalNormal += localNormal * boneWeights[i];
        totalTan += localTan * boneWeights[i];
    }

    vec3 worldNormal = normalize((MW * totalNormal).xyz);
    vec3 worldTan = normalize((MW * totalTan).xyz);
    vec3 worldBiTan = cross(worldNormal, worldTan);
    worldTan = cross(worldBiTan, worldNormal);

    gl_Position = MWVP * totalPosition;
    fragPos = (MW * totalPosition).xyz;
    fragNormal = worldNormal;
    fragUV = vec2(uv.x, 1-uv.y);
    matIndex = matIndices;
    TBN = mat3(worldTan, worldBiTan, worldNormal);
}