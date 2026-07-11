#version 450 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

layout (location = 0) out vec4 color;

in vec4 f_Color;
in vec2 f_TexCoord;
in vec3 f_Normal;
in vec3 f_FragPos;

uniform vec3 u_ObjectColor;
uniform vec3 u_LightColor;

uniform vec3 u_ViewPos;

uniform Material u_Material;
uniform Light u_Light;

void main()
{
    // Ambient
    vec3 ambient = u_Light.ambient * vec3(texture(u_Material.diffuse, f_TexCoord));

    // Diffuse
    vec3 norm = normalize(f_Normal);
    vec3 lightDirection = normalize(u_Light.position - f_FragPos);
    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = u_Light.diffuse * diff * vec3(texture(u_Material.diffuse, f_TexCoord));

    // Specular
    vec3 viewDir = normalize(u_ViewPos - f_FragPos);
    vec3 reflectDir = reflect(-lightDirection, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
    vec3 specular = u_Light.specular * (spec * vec3(texture(u_Material.specular, f_TexCoord)));

    float theta = dot(lightDirection, normalize(-u_Light.direction));
    float epsilon = u_Light.cutOff - u_Light.outerCutOff;
    float intensity = clamp((theta - u_Light.outerCutOff) / epsilon, 0.0, 1.0);

    float dist = length(u_Light.position - f_FragPos);
    float attenuation = 1.0 / (u_Light.constant + u_Light.linear * dist + u_Light.quadratic * (dist * dist));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    diffuse *= intensity;
    specular *= intensity;

    // vec4 texColor = mix(texture(texture1, f_TexCoord), texture(texture2, f_TexCoord), 0.5);
    color = vec4(ambient + diffuse + specular, 1.0);
}
