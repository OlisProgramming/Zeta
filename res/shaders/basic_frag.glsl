#version 330 core

layout (location = 0) out vec4 col;
uniform vec2 lightPos;

in DATA {
	vec4 pos;
} data;

void main() {
	float intensity = 1.0 / (length(data.pos.xy - lightPos) / 70.0);
	col = vec4(1.0, 0.1, 0.6, 1.0) * intensity;
}