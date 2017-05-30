#version 330 core

#define PI 3.1415926535897932384626433832795028841971

in vec3 pos;
in vec3 norm;
in vec2 tex;

out vec4 color;

uniform vec3 p;

uniform sampler2D albedo_map;
uniform sampler2D normal_map;
uniform sampler2D metallic_map;
uniform sampler2D roughness_map;
uniform sampler2D ao;

uniform samplerCube irradiance_map;
uniform samplerCube prefilter_map;
uniform sampler2D brdf_lut;

vec3 fresnel_schlick_roughness(float cos_theta, vec3 F_0, float roughness)
{
	return F_0 + (max(vec3(1.0 - roughness), F_0) - F_0) * pow(1.0 - cos_theta, 5.0);
}

void main()
{
	vec3 n = norm;
	vec3 v = normalize(p - pos);
	vec3 r = reflect(-v, n);

	vec3 albedo = texture(albedo_map, tex).rgb;
	float metallic = texture(metallic_map, tex).r;
	float roughness = texture(roughness_map, tex).r;

	vec3 F_0 = vec3(0.04);
	
	F_0 = mix(F_0, albedo, metallic);

	vec3 F = fresnel_schlick_roughness(max(0.0, dot(n, v)), F_0, roughness);

	vec3 k_S = F;
	vec3 k_D = 1.0 - k_S;
	
	k_D *= 1.0 - metallic;

	vec3 irradiance = texture(irradiance_map, n).rgb;
	vec3 diffuse = irradiance * albedo;

	const float MAX_REFLECTION_LOD = 4.0;

	vec3 pref_color = textureLod(prefilter_map, r, roughness * MAX_REFLECTION_LOD).rgb;
	vec2 brdf = texture(brdf_lut, vec2(max(0.0, dot(n, v)), roughness)).rg;
	vec3 specular = pref_color * (F * brdf.x + brdf.y);

	vec3 ambient = (k_D * diffuse + specular);

	ambient = ambient / (ambient + vec3(1.0));
	ambient = pow(ambient, vec3(1.0/2.2));

	color = vec4(ambient, 1.0);
}

