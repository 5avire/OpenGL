#version 450 core

struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;

    sampler2D texture_diffuse2;
    sampler2D texture_specular2;

    sampler2D texture_diffuse3;
    sampler2D texture_specular3;

    float shininess;
};

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
#define NR_POINT_LIGHTS 4

struct SpotLight {
    vec3 position;
    vec3 direction;

    float innerCutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

// Input / Outputs
layout (location = 0) out vec4 color;

in vec4 f_Color;
in vec2 f_TexCoord;
in vec3 f_Normal;
in vec3 f_FragPos;

// Uniforms
uniform vec3 u_ObjectColor;
uniform vec3 u_LightColor;

uniform vec3 u_ViewPos;

uniform Material u_Material;
uniform DirLight u_DirLight;
uniform SpotLight u_SpotLight;
uniform PointLight u_PointLight[NR_POINT_LIGHTS];


// Function Define
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);


void main()
{
    // Properties
    vec3 norm = normalize(f_Normal);
    vec3 viewDir = normalize(u_ViewPos - f_FragPos);

    // Directional
    vec3 result = CalcDirLight(u_DirLight, norm, viewDir);

    // Point Lights
    for (int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(u_PointLight[i], norm, f_FragPos, viewDir);

    // Spot Light
    result += CalcSpotLight(u_SpotLight, norm, f_FragPos, viewDir);

    color = vec4(result, 1.0);
}


vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    // Diffuse Shading
    float diff = max(dot(normal, lightDir), 0.0);

    // Specular Lighting
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);

    // Result
    vec3 ambient = light.ambient * vec3(texture(u_Material.texture_diffuse1, f_TexCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(u_Material.texture_diffuse1, f_TexCoord));
    vec3 specular = light.specular * spec * vec3(texture(u_Material.texture_specular1, f_TexCoord));

    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    // Diffuse Shading
    float diff = max(dot(normal, lightDir), 0.0);

    // Specular Lighting
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);

    // Attenuation
    float dist = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * dist * dist);

    // Result
    vec3 ambient = light.ambient * vec3(texture(u_Material.texture_diffuse1, f_TexCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(u_Material.texture_diffuse1, f_TexCoord));
    vec3 specular = light.specular * spec * vec3(texture(u_Material.texture_specular1, f_TexCoord));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0);

    // Specular Lighting
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);

    // Attenuation
    float dist = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * dist * dist);

    // Spotlight Intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.innerCutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    // Result
    vec3 ambient = light.ambient * vec3(texture(u_Material.texture_diffuse1, f_TexCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(u_Material.texture_diffuse1, f_TexCoord));
    vec3 specular = light.specular * spec * vec3(texture(u_Material.texture_specular1, f_TexCoord));

    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return (ambient + diffuse + specular);
}
