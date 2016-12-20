#version 300 es
// #version 330 core
// #version 130
precision highp float; // Defines precision for float and float-derived (vector/matrix) types.


out vec4 fColor;
in vec4 color;

void main () {
	fColor = color; 
}