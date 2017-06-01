#version 330 core

layout (location = 0) out vec4 col;

in DATA {
	vec4 pos;
} data;

void main() {
	col = vec4(1.0, 0.1, 0.6, 1.0);
}