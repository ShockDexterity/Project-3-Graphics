#version 410

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;
layout (location = 3) in vec2 uv;

uniform mat4 mvp;
uniform mat4 mv;

out vec2 fragUV;
out vec4 fragColor;

void main()
{
	gl_Position = mvp * vec4(pos, 1.0);
	fragUV = vec2(uv.x, 1 - uv.y);
	fragColor = vec4(color, 1);
}