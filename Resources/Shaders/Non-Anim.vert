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

void main()
{

    vec3 worldNormal = normalize((MW * normal).xyz);
    vec3 worldTan = normalize((MW * tangent).xyz);
    vec3 worldBiTan = cross(worldNormal, worldTan);
    worldTan = cross(worldBiTan, worldNormal);

    gl_Position = MWVP * position;
    fragPos = (MW * position).xyz;
    fragNormal = normalize((MW * normal).xyz);
    fragUV = vec2(uv.x, 1-uv.y);
    matIndex = matIndices;
    TBN = mat3(worldTan, worldBiTan, worldNormal);
}