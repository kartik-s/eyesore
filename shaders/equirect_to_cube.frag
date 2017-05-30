#version 330 core

in vec3 pos;

out vec4 color;

uniform sampler2D equirectangular_map;

vec2 spherical_sample(vec3 v)
{
	return 0.5f + (vec2(0.1591, 0.3183) * vec2(atan(v.z, v.x), asin(v.y)));
}

void main()
{
	vec2 uv = spherical_sample(normalize(pos));

	color = vec4(texture(equirectangular_map, uv).rgb, 1.0f);
}

