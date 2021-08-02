#version 460 core


layout (location =0) in vec3 pos;
layout (location =1) in vec3 color;
layout (location =2) in vec3 norm;
layout (location =3) in vec2 uv;
layout (location =4) in vec4 lightSpacePos;


out vec4 FragColor;
out int entID;


struct Material {
    vec3 albedo;
    float roughness;
    float metallic;
    float ao;

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

    float radius;

};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};

#define NR_POINT_LIGHTS 32
#define NR_SPOT_LIGHTS  1

uniform sampler2D diffuse0;
uniform sampler2D specular0;

uniform vec3 un_camPosition;

uniform DirLight un_dirLight;
uniform PointLight un_pointLights[NR_POINT_LIGHTS];
uniform SpotLight un_spotLights[NR_SPOT_LIGHTS];

uniform Material un_material;

uniform int un_entityID;
uniform int un_pointLightIndex;


const float PI = 3.14159265359;
// ----------------------------------------------------------------------------
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / max(denom, 0.0000001); // prevent divide by zero for roughness=0.0 and NdotH=1.0
}
// ----------------------------------------------------------------------------
float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}
// ----------------------------------------------------------------------------
vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(max(1.0 - cosTheta, 0.0), 5.0);
}
// ----------------------------------------------------------------------------
void main()
{		
    vec3 N = normalize(norm);
    vec3 V = normalize(un_camPosition - pos);

    // calculate reflectance at normal incidence; if dia-electric (like plastic) use F0 
    // of 0.04 and if it's a metal, use the albedo color as F0 (metallic workflow)    
    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, un_material.albedo, un_material.metallic) ;

    // reflectance equation
    vec3 Lo = vec3(0.0);
    for(int i = 0; i < un_pointLightIndex; ++i) 
    {
        // calculate per-light radiance
        vec3 L = normalize(un_pointLights[i].position - pos);
        vec3 H = normalize(V + L);
        float distance = length(un_pointLights[i].position - pos);
//        float attenuation = 1.0 / ((distance /un_pointLights[i].radius) + 1)  * ((distance /un_pointLights[i].radius) + 1);
        float attenuation = (un_pointLights[i].radius - distance )  / un_pointLights[i].radius;
        vec3 radiance = (un_pointLights[i].ambient  * texture(diffuse0, uv).xyz) * attenuation ;

        // Cook-Torrance BRDF
        float NDF = DistributionGGX(N, H, un_material.roughness);   
        float G   = GeometrySmith(N, V, L, un_material.roughness);      
        vec3 F    = fresnelSchlick(clamp(dot(H, V), 0.0, 1.0), F0);
           
        vec3 numerator    = NDF * G * F; 
        float denominator = 4 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0);
        vec3 specular = numerator / max(denominator, 0.001); // prevent divide by zero for NdotV=0.0 or NdotL=0.0
        
        // kS is equal to Fresnel
        vec3 kS = F;
        // for energy conservation, the diffuse and specular light can't
        // be above 1.0 (unless the surface emits light); to preserve this
        // relationship the diffuse component (kD) should equal 1.0 - kS.
        vec3 kD = vec3(1.0) - kS;
        // multiply kD by the inverse metalness such that only non-metals 
        // have diffuse lighting, or a linear blend if partly metal (pure metals
        // have no diffuse light).
        kD *= 1.0 - un_material.metallic;	  

        // scale light by NdotL
        float NdotL = max(dot(N, L), 0.0);        

        // add to outgoing radiance Lo
        Lo += (kD * un_material.albedo / PI + specular) * radiance * NdotL;  // note that we already multiplied the BRDF by the Fresnel (kS) so we won't multiply by kS again
    }   
    
    // ambient lighting (note that the next IBL tutorial will replace 
    // this ambient lighting with environment lighting).
    vec3 ambient = vec3(0.03) * un_material.albedo * un_material.ao * texture(diffuse0, uv).xyz ;

    vec3 color = ambient + Lo;

    // HDR tonemapping
    color = color / (color + vec3(1.0));
    // gamma correct
    color = pow(color, vec3(1.0/2.2)); 

    FragColor = vec4(color, 1.0);
    entID = un_entityID;
}
//
//// function prototypes
//vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
//vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
//vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
//
//void main()
//{    
//    // properties
//    vec3 _norm = normalize(norm);
//    vec3 viewDir = normalize(un_camPosition - pos);
//
//    // == =====================================================
//    // Our lighting is set up in 3 phases: directional, point lights and an optional flashlight
//    // For each phase, a calculate function is defined that calculates the corresponding color
//    // per lamp. In the main() function we take all the calculated colors and sum them up for
//    // this fragment's final color.
//    // == =====================================================
//    // phase 1: directional lighting
//
//    vec3 result = CalcDirLight(un_dirLight, _norm, viewDir);
//    // phase 2: point lights
//    for(int i = 0; i < un_pointLightIndex; i++){
//        result += CalcPointLight(un_pointLights[i], _norm, pos, viewDir);    
//    }
//    // phase 3: spot light
//    for(int i = 1; i < NR_SPOT_LIGHTS; i++)
//        result += CalcSpotLight(un_spotLights[i], _norm, pos, viewDir);    
//    
//    
//    float gamma = 2.2;
//    vec3 gamma_corrected = pow(result, vec3(gamma));
//
//    FragColor = vec4(gamma_corrected, 1.0);
//    entID = un_entityID;
//
//}
//
//// calculates the color when using a directional light.
//vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
//{
//    vec3 lightDir = normalize(-light.direction);
//    // diffuse shading
//    float diff = max(dot(normal, lightDir), 0.0);
//    // specular shading
//    vec3 reflectDir = reflect(-lightDir, normal);
//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), un_material.shininess * 128);
//    // combine results
//
//    vec3 ambient = light.ambient * vec3(texture(diffuse0, uv)) * un_material.ambient;
//    vec3 diffuse = light.diffuse * diff * vec3(texture(diffuse0, uv))* un_material.diffuse;
//    vec3 specular = light.specular * spec * vec3(texture(specular0, uv));
//    float shadow = ShadowCalculation(vec4(pos,1.0));
//    return (ambient + (1.0 - shadow) *  (diffuse + specular));
//}
//
//// calculates the color when using a point light.
//vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
//{
//    vec3 lightDir = normalize(light.position - fragPos);
//    // diffuse shading
//    float diff = max(dot(normal, lightDir), 0.0);
//    // specular shading
//    vec3 reflectDir = reflect(-lightDir, normal);
//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), un_material.shininess * 128);
//    // attenuation
//    float distance = length(light.position - fragPos);
//    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
//    // combine results
//    vec3 ambient = light.ambient * vec3(texture(diffuse0, uv)) * un_material.ambient;
//    vec3 diffuse = light.diffuse * diff * vec3(texture(diffuse0, uv)) * un_material.diffuse;
//    vec3 specular = light.specular * spec * vec3(texture(specular0, uv));
//    ambient *= attenuation;
//    diffuse *= attenuation;
//    specular *= attenuation;
//    float shadow = ShadowCalculation(vec4(pos,1.0));
//
//    return (ambient + (1.0 - shadow) *  (diffuse + specular));
//
//}
//
//// calculates the color when using a spot light.
//vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
//{
//    vec3 lightDir = normalize(light.position - fragPos);
//    // diffuse shading
//    float diff = max(dot(normal, lightDir), 0.0);
//    // specular shading
//    vec3 reflectDir = reflect(-lightDir, normal);
//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), un_material.shininess * 128);
//    // attenuation
//    float distance = length(light.position - fragPos);
//    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
//    // spotlight intensity
//    float theta = dot(lightDir, normalize(-light.direction)); 
//    float epsilon = light.cutOff - light.outerCutOff;
//    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
//    // combine results
//    vec3 ambient = light.ambient * vec3(texture(diffuse0, uv))* un_material.ambient;
//    vec3 diffuse = light.diffuse * diff * vec3(texture(diffuse0, uv))* un_material.diffuse;
//    vec3 specular = light.specular * spec * vec3(texture(specular0, uv));
//    ambient *= attenuation * intensity;
//    diffuse *= attenuation * intensity;
//    specular *= attenuation * intensity;
//    float shadow = ShadowCalculation(vec4(pos,1.0));
//
//    return (ambient + (1.0 - shadow) *  (diffuse + specular));
//
//}