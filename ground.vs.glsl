#version 300 es
// #version 330 core
// #version 130
// #extension GL_ARB_explicit_attrib_location : require
// precision highp float; // Defines precision for float and float-derived (vector/matrix) types.

layout (location = 0) in vec2 vPosition;
layout (location = 1) in vec2 vUV;



uniform vec2 size;
uniform float depth;

out vec2 UV;

void main () {
	gl_Position = vec4 (vPosition, depth, 1);
	UV.x = size.x * vUV.x;
	UV.y = size.y * vUV.y;
	// color = gl_Position+0.5;
}
