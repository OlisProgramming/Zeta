#version 330 core

layout (location = 0) in vec4 pos;
uniform mat4 matProj = mat4(1.0);
uniform mat4 matView = mat4(1.0);
uniform mat4 matModl = mat4(1.0);

out DATA {
	vec4 pos;
} data;

void main() {
	gl_Position = matModl * matView * matProj * pos;
	data.pos = pos;
}