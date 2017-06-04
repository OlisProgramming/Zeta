#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uv;
layout (location = 2) in float texID;
layout (location = 3) in vec4 col;

uniform mat4 matProj = mat4(1.0);
uniform mat4 matView = mat4(1.0);
uniform mat4 matModl = mat4(1.0);

out DATA {
	vec4 pos;
	vec2 uv;
	float texID;
	vec4 col;
} data;

void main() {
	vec4 pos4 = vec4(pos,1.0);
	gl_Position = matProj * matView * matModl * pos4;
	data.pos = matModl * pos4;
	data.uv = uv;
	data.texID = texID;
	data.col = col;
}