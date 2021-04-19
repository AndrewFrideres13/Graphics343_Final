#version 410

layout (location = 0) in vec3 position;
layout (location = 3) in vec2 uv;

uniform mat4 mvp;

out vec2 fragUV;

void main()
{
	gl_Position = mvp * vec4(position, 1.0);
	fragUV = vec2(uv.x, 1 - uv.y);
}