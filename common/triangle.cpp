#include <triangle.hpp>

void Triangle::initBuffers () {
	GLuint vao, buffer[2];
	glGenVertexArrays (1, &vao);
	glGenBuffers (1, buffer);
	glBindVertexArray (vao);
	glBindBuffer (GL_ARRAY_BUFFER, buffer[0]);
	glBufferData (GL_ARRAY_BUFFER, sizeof (p), p, GL_STATIC_DRAW);
	glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, 0, (const void*) 0);
	glEnableVertexAttribArray (0);

	setVao (vao); setBuffer (buffer[0]);
}
void Triangle::render () const {
	glBindVertexArray (getVao());
	glBindBuffer (GL_ARRAY_BUFFER, getBuffer());
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
