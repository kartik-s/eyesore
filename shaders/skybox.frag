#version 330 core

in vec3 pos;

out vec4 color;

uniform samplerCube environment_map;

void main()
{
	vec3 env_color = texture(environment_map, normalize(pos)).rgb;

	env_color = env_color / (env_color + vec3(1.0f));
	env_color = pow(env_color, vec3(1.0f/2.2f));

	color = vec4(env_color, 1.0f);
}

