#version 330 core

#define PI 3.1415926535897932384626433832795028841971

in vec3 pos;

out vec4 color;

uniform float roughness;
uniform samplerCube environment_map;

float radical_inverse_vdc(uint bits) // what
{
	bits = (bits << 16u) | (bits >> 16u);
	bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xAAAAAAAAu) >> 1u);
	bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xCCCCCCCCu) >> 2u);
	bits = ((bits & 0x0F0F0F0Fu) << 4u) | ((bits & 0xF0F0F0F0u) >> 4u);
	bits = ((bits & 0x00FF00FFu) << 8u) | ((bits & 0xFF00FF00u) >> 8u);

	return float(bits) * 2.3283064365386963e-10;
}

vec2 hammersley(uint i, uint n)
{
	return vec2(float(i) / float(n), radical_inverse_vdc(i));
}

vec3 importance_sample_ggx(vec2 X_i, float roughness, vec3 n)
{
	float a = roughness * roughness;

	float phi = 2 * PI * X_i.x;
	float cos_theta = sqrt((1 - X_i.y) / (1 + (a*a - 1) * X_i.y));
	float sin_theta = sqrt(1 - cos_theta*cos_theta);

	vec3 h = vec3(sin_theta * cos(phi), sin_theta * sin(phi), cos_theta);

	vec3 up = abs(n.z) < 0.999 ? vec3(0.0, 0.0, 1.0) : vec3(1.0, 0.0, 0.0);
	vec3 tangent = normalize(cross(up, n));
	vec3 bitangent = cross(n, tangent);

	return normalize(tangent * h.x + bitangent * h.y + n * h.z);
}

void main()
{
	vec3 n = normalize(pos);
	vec3 r = n;
	vec3 v = r;

	const uint SAMPLES = 4096u;
	float total_weight = 0.0;
	vec3 pref_color = vec3(0.0);

	for (uint i = 0u; i < SAMPLES; i++) {
		vec2 X_i = hammersley(i, SAMPLES);
		vec3 h = importance_sample_ggx(X_i, roughness, n);
		vec3 l = normalize(2.0 * dot(v , h) * h - v);

		float ndotl = max(0.0, dot(n, l));

		if (ndotl > 0.0) {
			pref_color += texture(environment_map, l).rgb * ndotl;
			total_weight += ndotl;
		}
	}

	pref_color /= total_weight;

	color = vec4(pref_color, 1.0);
}

