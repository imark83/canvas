#version 300 es
// #version 330 core
// #version 130
// #extension GL_ARB_explicit_attrib_location : require
// precision highp float; // Defines precision for float and float-derived (vector/matrix) types.

layout (location = 0) in vec2 vPosition;
uniform mat4 model;

out vec4 color;

void main () {
	gl_Position = model*vec4 (vPosition, 0, 1);
	color = vec4 (1.0, 1.0, 1.0, 1.0);
	// color = gl_Position+0.5;
}
