#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec4 f_Color;
out vec2 f_TexCoord;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * vec4(aPos, 1.0f);
    f_Color = aColor;
    f_TexCoord = aTexCoord;
}
