#version 330 core

#define PI 3.1415926535897932384626433832795028841971f

in vec3 pos;

out vec4 color;

uniform samplerCube environment_map;

void main()
{
	vec3 normal = normalize(pos);
	vec3 irradiance = vec3(0.0f);

	vec3 up = vec3(0.0f, 1.0f, 0.0f);
	vec3 right = cross(up, normal);
	up = cross(normal, right);

	float delta = 0.02f;
	float samples = 0.0f;

	for (float phi = 0.0f; phi < 2.0f * PI; phi += delta)
		for (float theta = 0.0f; theta < 0.5f * PI; theta += delta) {
			vec3 s = vec3(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));
			vec3 v = s.x * right + s.y * up + s.z * normal; 

			irradiance += texture(environment_map, v).rgb * cos(theta) * sin(theta);
			samples++;
		}

	irradiance *= PI;
	irradiance /= float(samples);

	color = vec4(irradiance, 1.0f);
}

