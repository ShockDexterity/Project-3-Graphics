#version 410

in vec3 fragNormal;
in vec2 fragUV;

out vec4 outColor;

void main()
{
	vec3 norm = normalize(fragNormal);
	outColor = vec4(norm * 0.5 + vec3(0.5), 1.0);
}