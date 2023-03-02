#version 410

in vec2 fragUV;
in vec4 fragColor;

out vec4 outColor;

void main()
{
	outColor = fragColor;
}