#version 330 core

layout (location = 0) out vec4 col;

in DATA {
	vec4 pos;
	vec2 uv;
	float texID;
} data;

uniform sampler2D textures[32];

void main() {
	vec4 texcol = vec4(1.0, 1.0, 1.0, 1.0);
	if (data.texID > 0.0) {
		texcol = texture(textures[int(data.texID - 0.1)], data.uv);   // 0.1 for floating-point precision errors
	}
	if (data.texID == 1.0) {
		col = vec4(1, 1, 1, texcol.r);
	}
	else {
		col = texcol;
	}
}