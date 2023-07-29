#version 330 core


layout (location = 1) in vec4 position;

out vec3 TexCoords;
uniform mat4  MWVP;

void main()
{
    TexCoords = position.xyz;
    vec4 pos = MWVP * position;
    gl_Position = vec4(pos.xy, pos.w-.00001f, pos.w);
}