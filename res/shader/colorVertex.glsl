#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec4 f_Color;
out vec2 f_TexCoord;
out vec3 f_Normal;
out vec3 f_FragPos;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;

void main()
{
    mat4 MVP = u_Proj * u_View * u_Model;
    gl_Position = MVP * vec4(aPos, 1.0f);
    f_FragPos = vec3(u_Model * vec4(aPos, 1.0));
    f_TexCoord = aTexCoord;
    f_Normal = mat3(transpose(inverse(u_Model))) * aNormal;
}
