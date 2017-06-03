#version 330 core

layout (location = 0) out vec4 col;

in DATA {
	vec4 pos;
	vec2 uv;
} data;

uniform sampler2D tex;

void main() {
	col = texture(tex, data.uv);
}