#version 300 es
// #version 330 core
// #version 130
precision highp float; // Defines precision for float and float-derived (vector/matrix) types.

in vec2 UV;

uniform sampler2D texSampler;

out vec4 fColor;

void main () {
	fColor = texture(texSampler, UV).rgba;
	// fColor = vec4(0, UV.g ,0, 1);
}
