#version 450 core

layout (location = 0) out vec4 color;

in vec4 f_Color;
in vec2 f_TexCoord;

uniform vec3 objectColor;
uniform vec3 lightColor;

// uniform sampler2D texture1;
// uniform sampler2D texture2;

void main()
{
    // vec4 texColor = mix(texture(texture1, f_TexCoord), texture(texture2, f_TexCoord), 0.5);
    color = vec4(1.0f);
}
