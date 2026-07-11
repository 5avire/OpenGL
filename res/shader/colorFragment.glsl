#version 450 core

layout (location = 0) out vec4 color;

in vec4 f_Color;
in vec2 f_TexCoord;
in vec3 f_Normal;
in vec3 f_FragPos;

uniform vec3 u_ObjectColor;
uniform vec3 u_LightColor;

uniform vec3 u_LightPos;
uniform vec3 u_ViewPos;

// uniform sampler2D texture1;
// uniform sampler2D texture2;

void main()
{
    float ambientStrength = 0.105;
    vec3 ambient = ambientStrength * u_LightColor;

    vec3 norm = normalize(f_Normal);
    vec3 lightDirection = normalize(u_LightPos - f_FragPos);
    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = diff * u_LightColor;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(u_ViewPos - f_FragPos);
    vec3 reflectDir = reflect(-lightDirection, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * u_LightColor;

    // vec4 texColor = mix(texture(texture1, f_TexCoord), texture(texture2, f_TexCoord), 0.5);
    vec3 result = (ambient + diffuse + specular) * u_ObjectColor;
    color = vec4(result, 1.0);
}
