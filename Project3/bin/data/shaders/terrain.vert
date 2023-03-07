#version 410

layout (location = 0) in vec3 pos;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec2 uv;

uniform mat4 mvp;
uniform mat4 mv;

out vec3 fragNormal;
out vec2 fragUV;

uniform mat3 normalMatrix;

void main()
{
	gl_Position = mvp * vec4(pos, 1.0);
	fragNormal = normalMatrix * normal;
	fragUV = vec2(uv.x, 1 - uv.y);
}